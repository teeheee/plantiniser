#include "config.h"
#include <string>

void ConfigManage::proccess(hal_ui* ui)
{
    for(auto const& config_item : list_of_config_items)
    {
        config_item->config_user_interface(ui);
    }
}

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
