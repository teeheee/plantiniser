#ifndef __TEST__

#include "time_hal.h"
#include "logging.h"
#include <ESP8266WiFi.h>
#include <DS1307.h>
#include <Wire.h>


DS1307 hardware_rtc;

void hal_time_impl::init()
{
    LOG("setup time server:");
    configTime(1*3600, 0, "pool.ntp.org", "time.nist.gov");
    //setenv("TZ", "CET-1CEST,M3.5.0,M10.5.0/3", 0); 
    Wire.beginTransmission (0x68);
    if (Wire.endTransmission() == 0) {
        has_rtc = true;
        hardware_rtc.start();
    }
    else
    {
        has_rtc = false;
    }
    now = 0;

}

bool hal_time_impl::is_valid()
{
    if(now)
    {
        return true;
    }
    else
    {
        return false;
    }
}


void hal_time_impl::update_rtc(time_t new_time)
{
    if(has_rtc)
    {
        struct tm * timeinfo;  
        timeinfo = localtime (&new_time);
        //sec, min, hour, day, month, year
        hardware_rtc.set(timeinfo->tm_sec, 
            timeinfo->tm_min, 
            timeinfo->tm_hour, 
            timeinfo->tm_mday, 
            timeinfo->tm_mon, 
            timeinfo->tm_year);
    }
}

time_t hal_time_impl::load_rtc()
{
    struct tm timeinfo;
    hardware_rtc.get(&timeinfo.tm_sec, 
            &timeinfo.tm_min, 
            &timeinfo.tm_hour, 
            &timeinfo.tm_mday, 
            &timeinfo.tm_mon, 
            &timeinfo.tm_year);
    return mktime(&timeinfo);
}

void hal_time_impl::process()
{
    time_t tmp_now = time(nullptr);
    if(tmp_now)
    {
        update_rtc(tmp_now);
        now = tmp_now;
    }
    else if(now)
    {
        if(has_rtc)
            now = load_rtc();
        else
            now = 0;
    }
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
