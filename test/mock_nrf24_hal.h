#ifndef _MOCK_NRF24_HAL_
#define _MOCK_NRF24_HAL_

#include "gmock/gmock.h"
#include "nrf24_hal.h"

class mock_hal_nrf24 : public hal_nrf24{
    public:
        void init(){};
        hal_nrf24_package_type* recv(){return 0;};
        void send(hal_nrf24_package_type* data){};
};

#endif