#ifndef _MOCK_OTA_HAL_
#define _MOCK_OTA_HAL_

#include "gmock/gmock.h"
#include "ota_hal.h"

class mock_hal_ota : public hal_ota{
    public:
        void init(){};
        void check_update(){};
};

#endif