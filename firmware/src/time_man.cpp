#include "time_man.h"
#include <NTPClient.h>
#include <WiFiUdp.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

void time_init()
{
    timeClient.begin(); 
}

void time_process()
{
    timeClient.update();
}

int time_get_hours()
{
    return timeClient.getDay();
}

int time_get_minutes()
{
    return timeClient.getMinutes();
}

int time_get_day()
{
    return timeClient.getDay();
}

String time_get_formated()
{
    return timeClient.getFormattedTime();
}
