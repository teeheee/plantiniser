#ifndef _LOGGING_H_
#define _LOGGING_H_

#ifdef DEBUG
#include <ESP8266WiFi.h>
#define LOG(x) Serial.println(x)
#else
#define LOG(x)
#endif

#endif