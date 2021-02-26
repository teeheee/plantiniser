#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <string>
#include <list>
#include "config_items.h"
#include "eeprom_hal.h"
#include "ui_hal.h"

class ConfigManage{
    public:
        ConfigManage(hal_eeprom* eeprom): 
            wifi_ssid(eeprom, 0, 25, "WLAN SSID"),
            wifi_passkey(eeprom, 40, 25, "WLAN Passkey"),
            server_address(eeprom, 80, 25, "MQTT Server Address"),
            water_valve_on_hour(eeprom, 90, "water time hour"),
            water_valve_on_minute(eeprom, 100, "water time minute"),
            water_valve_on_duration(eeprom, 110, "water time duration minutes")
        {
            list_of_config_items.push_back(&wifi_ssid);
            list_of_config_items.push_back(&wifi_passkey);
            list_of_config_items.push_back(&server_address);
            list_of_config_items.push_back(&water_valve_on_hour);
            list_of_config_items.push_back(&water_valve_on_minute);
            list_of_config_items.push_back(&water_valve_on_duration);
        }
        void process(hal_ui* ui);
        std::string get_wifi_ssid();
        std::string get_wifi_passkey();
        std::string get_server_address();
        int get_water_valve_on_hour();
        int get_water_valve_on_minute();
        int get_water_valve_on_duration();
        bool all_valid();
    private:
        StringItem wifi_ssid;
        StringItem wifi_passkey;
        StringItem server_address;
        NumberItem water_valve_on_hour;
        NumberItem water_valve_on_minute;
        NumberItem water_valve_on_duration;
        std::list<ConfigBaseItem*> list_of_config_items;
};

#endif