#ifndef _POWER_HAL_H_
#define _POWER_HAL_H_

class hal_power {
public:
    virtual void init() = 0;
    virtual void set(int pin, bool state) = 0;
};

class hal_power_impl : public hal_power{
};

#endif
