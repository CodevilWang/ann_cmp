/**
 * Copyright (c) 2015-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD+Patents license found in the
 * LICENSE file in the root directory of this source tree.
 */

// Copyright 2004-present Facebook. All Rights Reserved.
// -*- c -*-

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "glog/logging.h"
#include "gflags/gflags.h"
#include "data_loader.h"
#include "timer.h"

#include "error_c.h"
#include "index_io_c.h"
#include "Index_c.h"
#include "IndexFlat_c.h"
#include "AutoTune_c.h"

#define FAISS_TRY(C)                                       \
    {                                                      \
        if (C) {                                           \
            LOG(WARNING) << faiss_get_last_error();        \
            exit(-1);                                      \
        }                                                  \
    }
DEFINE_string(data_file, "data/KDD/p.txt", "");
DEFINE_string(query_file, "data/KDD/q.txt", "");
using DataLoader = ann_cmp::DataLoader;
int main(int argc, char** argv) {
    // google::InitGoogleLogging(argv[0]);
    google::ParseCommandLineFlags(&argc, &argv, true);
    DataLoader raw_data_loader;
    if (!raw_data_loader.load(FLAGS_data_file)) {
        LOG(WARNING) << "load " << FLAGS_data_file << " failed.";
        return 1;
    }
    DataLoader query_data_loader;
    if (!query_data_loader.load(FLAGS_query_file)) {
        LOG(WARNING) << "load " << FLAGS_query_file << " failed.";
        return 1;
    }

    std::shared_ptr<std::vector<float>> data = raw_data_loader.get_data();
    std::shared_ptr<std::vector<float>> query = query_data_loader.get_data();
    assert(raw_data_loader.get_width() == query_data_loader.get_width());
    uint32_t width = raw_data_loader.get_width();
    uint32_t data_length = data->size() / width;
    LOG(INFO) << "Building index ...";
    FaissIndex* index = NULL;
    FAISS_TRY(faiss_index_factory(&index, width, "HNSW5_PQ5", METRIC_INNER_PRODUCT));  // use factory to create index
    FAISS_TRY(faiss_Index_train(index, data_length, data->data()));
    LOG(INFO) << "is_trained = " <<  faiss_Index_is_trained(index) ? "true" : "false";
    {
        ann_cmp::Timer t("build_idx_rt=");
        FAISS_TRY(faiss_Index_add(index, data_length, data->data()));                     // add vectors to the index
    }
    LOG(INFO) << "ntotal = " << faiss_Index_ntotal(index);

    LOG(INFO) << "Searching...\n";
    int k = 5;
    {       // search xq
        long *I = (long*)malloc(k * query->size() * sizeof(long));
        float *D = (float*)malloc(k * query->size() * sizeof(float));
        {
            ann_cmp::Timer t("search_rt=");
            FAISS_TRY(faiss_Index_search(index, 5, query->data(), k, D, I));
        }
        printf("I=\n");
        for(int i = 0; i < 5; i++) {
            for(int j = 0; j < k; j++) printf("%5ld (d=%2.3f)  ", I[i * k + j], D[i * k + j]);
            printf("\n");
        }
        free(I);
        free(D);
    }

    LOG(INFO) << "Saving index to disk...";
    FAISS_TRY(faiss_write_index_fname(index, "example.index"));
    LOG(INFO) << "Freeing index...";
    faiss_Index_free(index);
    LOG(INFO) << "Done";
    return 0;
}
