#ifndef _APP_H_
#define _APP_H_

#include "eeprom_hal.h"
#include "mqtt_hal.h"
#include "wifi_hal.h"
#include "power_hal.h"
#include "ota_hal.h"
#include "time_hal.h"
#include "nrf24_hal.h"
#include "ui_hal.h"
#include "serial_hal.h"
#include "ui_lcd.h"
#include "ui_serial.h"
#include "timer_manager.h"
#include "config.h"

class app{
    private:
        hal_eeprom* eeprom; 
        hal_mqtt* mqtt; 
        hal_power* power; 
        hal_time* rtc;
        hal_ui* ui;
        hal_ota* ota;
        hal_serial* serial;
        hal_nrf24* nrf24;
        hal_wifi* wifi;

        ConfigManage* config_manage;
        TimerManager* time_manage;
        network_manager* network_manage;
        ui_lcd* ui_lcd_object;
        ui_serial* ui_serial_object;

        int g_pump_timeout = 0;

        void minute_tick(int minute, int hour);
    public:
        app();
        void process();    
};

#endif
