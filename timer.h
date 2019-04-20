#ifndef  __TIMER_H_
#define  __TIMER_H_
#include <sys/time.h>
#include <glog/logging.h>
namespace ann_cmp {
class Timer {
public:
    Timer(const std::string& str) : _prefix(str) {
        gettimeofday(&_start, NULL);
    }
    ~Timer() {
        gettimeofday(&_end, NULL);
        uint32_t time_in_us = _end.tv_usec - _start.tv_usec \
                     + (_end.tv_sec - _start.tv_sec) * 1000000; 
        LOG(INFO) << _prefix << time_in_us / 1000; 
    }
private:
    timeval _start;
    timeval _end;
    std::string _prefix;
};
}

#endif  //__TIMER_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
