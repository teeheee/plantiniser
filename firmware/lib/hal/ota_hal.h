#ifndef _OTA_HAL_H_
#define _OTA_HAL_H_

#include <stdint.h>

class hal_ota {
    public:
        virtual void init() = 0;
        virtual void check_update() = 0;
};

class hal_ota_impl : public hal_ota{
    public:
        void init();
        void check_update();
};

#endif