#ifndef __TEST__

#include "serial_hal.h"
#include <ESP8266WiFi.h>

void hal_serial_impl::init()
{
    Serial.begin(115200);
    Serial.setTimeout(30000);
}

void hal_serial_impl::write(std::string data)
{
    Serial.println(data.c_str());
}

std::string hal_serial_impl::read()
{
    String str = Serial.readStringUntil('\n');
    return std::string(str.c_str());
}

#endif