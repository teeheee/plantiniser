#ifndef _MOCK_POWER_HAL_
#define _MOCK_POWER_HAL_

#include "gmock/gmock.h"
#include "power_hal.h"

class mock_hal_power : public hal_power{
    void init(){};
    void set(int pin, bool state){};
};

#endif