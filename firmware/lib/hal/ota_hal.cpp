#ifndef __TEST__

#include "ota_hal.h"
#include "EasyOta.h"

void hal_ota_impl::init()
{
    EasyOta.setup();
}

void hal_ota_impl::check_update()
{
    EasyOta.checkForUpload();
}

#endif
