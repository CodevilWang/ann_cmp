#ifndef  __DATA_LOADER_H_
#define  __DATA_LOADER_H_
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <boost/algorithm/string.hpp>
#include "glog/logging.h" 
namespace ann_cmp {
class DataLoader {
public:
    DataLoader() {
        _data = std::make_shared<std::vector<float>>();
        _width = 0;
    }
    ~DataLoader() {}
    bool load(const std::string& fn) {
        std::ifstream ifs(fn);
        if (!ifs.is_open()) {
            LOG(WARNING) << "open data file " << fn << " failed";
            return false;
        }
        std::string aline;
        std::vector<float> all_data;
        uint32_t line_cnt = 0;
        while (std::getline(ifs, aline)) {
            std::vector<std::string> pieces;
            boost::algorithm::split(pieces, aline, boost::is_any_of(","));
            for (auto& i : pieces) {
                _data->push_back(std::stof(i));
            }
            if (_width == 0) {
                _width = pieces.size();
            }
            ++line_cnt;
        }
        LOG(INFO) << "loaded [" << _data->size() << "] floats & [" << line_cnt << "] lines";
        return true;
    }
    std::shared_ptr<std::vector<float>> get_data() {
        return _data;
    }
    uint32_t get_width() {
        return _width;
    }
private:
    std::shared_ptr<std::vector<float>> _data;
    uint32_t _width;
}; 
};

#endif  //__DATA_LOADER_H_
