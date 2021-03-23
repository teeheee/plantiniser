#ifndef _MOCK_WIFI_HAL_
#define _MOCK_WIFI_HAL_

#include "gmock/gmock.h"
#include "wifi_hal.h"

class mock_hal_wifi : public hal_wifi{
    public:   
        bool init(std::string ssid, std::string pass){return true;};
        bool is_initalized(){return true;};
        bool is_connected(){return true;};
};

#endif