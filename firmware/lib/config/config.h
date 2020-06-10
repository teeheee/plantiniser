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
            server_address(eeprom, 80, 25, "MQTT Server Address")
        {
            list_of_config_items.push_back(&wifi_ssid);
            list_of_config_items.push_back(&wifi_passkey);
            list_of_config_items.push_back(&server_address);
        }
        void process(hal_ui* ui);
        std::string get_wifi_ssid();
        std::string get_wifi_passkey();
        std::string get_server_address();
        bool all_valid();
    private:
        StringItem wifi_ssid;
        StringItem wifi_passkey;
        StringItem server_address;
        std::list<ConfigBaseItem*> list_of_config_items;
};

#endif