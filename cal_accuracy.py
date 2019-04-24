#!/usr/bin/env python
import sys
data = {} 
naive_res_fn = sys.argv[1]
res_fn = sys.argv[2]
with open(naive_res_fn) as f:
    for aline in f:
        fields = aline.split("\t")
        data[int(fields[0])] = [int(x) for x in fields[1::2]]
all_cnt = 0 
right_cnt = 0
top1_cnt = 0
all_res = 0
total_fail = 0
with open(res_fn) as f:
    for aline in f:
        all_res += 1
        fields = aline.split("\t")
        res_idx = [int(x.split()[0]) for x in fields[1:]]
        naive_res = data[int(fields[0])]
        all_cnt += len(naive_res)
        # right_cnt += len(set(res_idx).intersection(set(naive_res)))
        inter_set = set(res_idx).intersection(set(naive_res))
        print "{}\t{}".format(fields[0], inter_set) 
        right_cnt += len(inter_set)
        if (res_idx[0] == naive_res[0]):
            top1_cnt += 1
        if (len(inter_set) == 0):
            total_fail += 1 

print "{}\t{}\t{}".format(right_cnt, all_cnt, float(right_cnt) / float(all_cnt))
print "{}\t{}".format(top1_cnt, float(top1_cnt) / float(all_res))
print "{}\t{}".format(total_fail, float(total_fail) / float(all_res))
