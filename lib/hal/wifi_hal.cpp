#ifndef __TEST__

#include <ESP8266WiFi.h>
#include "wifi_hal.h"


bool hal_wifi_impl::init(std::string ssid, std::string pass)
{
    delay(10); //TODO delete me
    WiFi.begin(ssid.c_str(), pass.c_str());
    is_initialized_flag = true;
    return true;
}

bool hal_wifi_impl::is_initalized()
{
    return is_initialized_flag;
}

bool hal_wifi_impl::is_connected()
{
    if(WiFi.status() == WL_CONNECTED)
        return true;
    else
        return false;
}

#endif
