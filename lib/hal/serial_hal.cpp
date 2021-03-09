#ifndef __TEST__

#include "serial_hal.h"
#include <ESP8266WiFi.h>

void hal_serial_impl::init()
{
    Serial.begin(115200);
    Serial.setTimeout(30000);
    input_string = std::string("");
}

void hal_serial_impl::write(std::string data)
{
    Serial.println(data.c_str());
}

std::string hal_serial_impl::read()
{
    while(Serial.available() > 0)
    {   
        char input_byte = Serial.read();
        if(input_byte != '\n')
        {
            input_string += input_byte;
        }
        else
        {
            std::string ret = input_string;
            input_string = std::string("");
            return ret;
        }
    }
    return std::string("");
}

#endif