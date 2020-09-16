#ifdef _TEST_

#include <ESP8266WiFi.h>
#include <time_hal.h>
#include <mqtt_hal.h>
#include <scheduler_hal.h>

hal_mqtt* mqtt; 
hal_time* rtc;
hal_scheduler* scheduler;

void show_time_task()
{
    if(rtc->is_valid())
    {
        Serial.println(rtc->get_formated().c_str());
    }
}

void rtc_process()
{
    rtc->process();
}

void mqtt_process()
{
    mqtt->process();
}

void setup() 
{
    mqtt = new hal_mqtt_impl(); 
    rtc = new hal_time_impl(); 
    scheduler = new hal_scheduler_impl();
    Serial.begin(115200);
    mqtt->init("Karl-Marx-Stadt", "penisrofelcopter88", "oberjoch-ulbrich.de");
    scheduler->init();
    rtc->init();
    scheduler->run_task(1000, rtc_process, 2);
    scheduler->run_task(801, show_time_task, 3);
    scheduler->run_task(7, mqtt_process, 1);
}

void loop() 
{
    scheduler->process();
}

#endif
