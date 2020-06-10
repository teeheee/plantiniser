#ifndef _TIME_HAL_H_
#define _TIME_HAL_H_

#include <string>
#include <time.h>

class hal_time {
public:
    virtual void init() = 0;
    virtual int get_hours() = 0;
    virtual int get_minutes() = 0;
    virtual int get_day() = 0;
    virtual std::string get_formated() = 0;
    virtual void process() = 0;
};

class hal_time_impl : public hal_time{
public:
    void init();
    int get_hours();
    int get_minutes();
    int get_day();
    std::string get_formated();
    void process();
private:
    time_t now;
};

#endif
