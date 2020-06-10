#ifndef __TEST__

#include "time_hal.h"
#include <ESP8266WiFi.h>


void hal_time_impl::init()
{
    configTime(0, 0, "pool.ntp.org", "time.nist.gov");
    setenv("TZ", "CET-1CEST,M3.5.0,M10.5.0/3", 0);          // 
    while (!time(nullptr))
    {
        delay(100);
    }
}

void hal_time_impl::process()
{
   now = time(nullptr);
}

int hal_time_impl::get_hours()
{
    struct tm * timeinfo;
    timeinfo = localtime (&now);
    return timeinfo->tm_hour;
}

int hal_time_impl::get_minutes()
{
    struct tm * timeinfo;
    timeinfo = localtime (&now);
    return timeinfo->tm_min;
}

int hal_time_impl::get_day()
{
    struct tm * timeinfo;
    timeinfo = localtime (&now);
    return timeinfo->tm_mday;
}

std::string hal_time_impl::get_formated()
{
    struct tm * timeinfo;
    timeinfo = localtime (&now);
    char buffer[26];
    strftime(buffer, 26, "%H:%M:%S", timeinfo);
    return std::string(buffer);
}

#endif
