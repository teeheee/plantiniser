#ifndef _APP_H_
#define _APP_H_

#include "eeprom_hal.h"
#include "mqtt_hal.h"
#include "power_hal.h"
#include "ota_hal.h"
#include "time_hal.h"
#include "ui_hal.h"
#include "config.h"

class app{
    private:
        hal_eeprom* eeprom; 
        hal_mqtt* mqtt; 
        hal_power* power; 
        hal_time* rtc;
        hal_ui* ui;
        hal_ota* ota;

        ConfigManage* config_manage;

        int g_pump_timeout = 0;

        void minute_tick(int minute, int hour);
    public:
        app();
        void process();    
};

#endif
