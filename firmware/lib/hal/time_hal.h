#ifndef _TIME_HAL_H_
#define _TIME_HAL_H_

class hal_time {
public:
    virtual void init() = 0;
    virtual int get_hours() = 0;
    virtual int get_minutes() = 0;
    virtual int get_day() = 0;
    virtual String get_formated() = 0;
    virtual void process() = 0;
};

class hal_time_impl : public hal_time{
};

#endif
