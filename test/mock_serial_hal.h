#ifndef _MOCK_SERIAL_HAL_
#define _MOCK_SERIAL_HAL_

#include "gmock/gmock.h"
#include "serial_hal.h"

class mock_hal_serial : public hal_serial{
    public:
        void init(){};
        std::string read(){return std::string("")};
        void write(std::string data){};
};

#endif