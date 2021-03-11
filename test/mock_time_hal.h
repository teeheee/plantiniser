#ifndef _MOCK_TIME_HAL_
#define _MOCK_TIME_HAL_

#include "gmock/gmock.h"
#include "time_hal.h"

class mock_hal_time : public hal_time{
    void init(){};
    bool is_valid(){return true;};
    int get_hours(){return 0;};
    int get_minutes(){return 0;};
    int get_day(){return 0;};
    std::string get_formated(){return std::string("");};
    void process(){};
};

#endif
