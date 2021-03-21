#ifndef _TIMER_MANAGER_H_
#define _TIMER_MANAGER_H_

#include "config.h"
#include "power_hal.h"
#include "time_hal.h"

class TimerManager{
private:
    ConfigManage* config;
    hal_power* power;
    hal_time* rtc;

    bool tick_flag;
    int last_minute;
    int pump_timeout;
    void minute_tick(int minute, int hour);
public:
    TimerManager(ConfigManage* config, hal_power* power, hal_time* rtc);
    void process();
    std::string get_current_time();
    bool get_tick();
};

#endif
