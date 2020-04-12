#ifndef __TEST__

#include "time_hal.h"
#include <NTPClient.h>
#include <WiFiUdp.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

void hal_time_impl::init()
{
    timeClient.begin(); 
}

void hal_time_impl::process()
{
    timeClient.update();
}

int hal_time_impl::get_hours()
{
    return timeClient.getDay();
}

int hal_time_impl::get_minutes()
{
    return timeClient.getMinutes();
}

int hal_time_impl::get_day()
{
    return timeClient.getDay();
}

std::string hal_time_impl::get_formated()
{
    String formatted = timeClient.getFormattedTime();
    return std::string(formatted.c_str());
}

#endif
