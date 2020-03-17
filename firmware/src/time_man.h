#ifndef _TIME_MAN_H_
#define _TIME_MAN_H_

#include <ESP8266WiFi.h>

void time_init();
void time_process();
int time_get_hours();
int time_get_minutes();
int time_get_day();
String time_get_formated();

#endif