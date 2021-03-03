#include "config.h"
#include <string>


std::string ConfigManage::get_wifi_ssid()
{
    if(wifi_ssid.is_data_valid())
        return wifi_ssid.read_data();
    else
        return std::string("");
}

std::string ConfigManage::get_wifi_passkey()
{
    if(wifi_passkey.is_data_valid())
        return wifi_passkey.read_data();
    else
        return std::string("");
}

std::string ConfigManage::get_server_address()
{
    if(server_address.is_data_valid())
        return server_address.read_data();
    else
        return std::string("");
}

int ConfigManage::get_water_valve_on_hour()
{
    if(water_valve_on_hour.is_data_valid())
        return water_valve_on_hour.read_data();
    else
        return 0;
}

int ConfigManage::get_water_valve_on_minute()
{
    if(water_valve_on_minute.is_data_valid())
        return water_valve_on_minute.read_data();
    else
        return 0;
}

int ConfigManage::get_water_valve_on_duration()
{
    if(water_valve_on_duration.is_data_valid())
        return water_valve_on_duration.read_data();
    else
        return 0;
}

bool ConfigManage::all_valid()
{
    for(auto const& config_item : list_of_config_items)
    {
        if(config_item->is_data_valid() == false)
            return false;
    }
    return true;
}


std::list<ConfigBaseItem*>* ConfigManage::get_config_item_list()
{
    return &list_of_config_items;
}