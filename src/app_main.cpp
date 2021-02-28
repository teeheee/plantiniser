#if !defined(_TEST_) && !defined(OTA_TEST)


#include <ESP8266WiFi.h>
#include "app.h"

app* main_app_obj;

void setup() 
{
  main_app_obj = new app();
}

void loop() 
{
  main_app_obj->process();
}

#endif

