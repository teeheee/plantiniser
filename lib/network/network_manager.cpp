#include "network_manager.h"

network_manager::network_manager(ConfigManage* p_config, hal_mqtt* amqtt, hal_ota* aota, hal_time* artc)
{
    mqtt = amqtt;
    ota = aota;
    rtc = artc;
    config_manage = p_config;
}

void network_manager::process()
{
    if(mqtt->is_initalized())
    {
        ota->check_update();
        mqtt->process();
        rtc->process();
    }
    else
    {
        std::string ssid = config_manage->get_wifi_ssid();
        std::string passkey = config_manage->get_wifi_passkey();
        std::string server = config_manage->get_server_address();
        mqtt->init(ssid, passkey, server);
        if( mqtt->is_initalized()
            && mqtt->is_connected())
        {
            rtc->init();
            ota->init();
        }
    }
}

bool network_manager::is_wifi_connected()
{
    return mqtt->is_initalized();
}

bool network_manager::is_mqtt_server_active()
{
    return mqtt->is_initalized();
}

bool network_manager::is_time_synced()
{
    return rtc->is_valid();
}

bool network_manager::is_ota_up_to_date()
{
    return true; //todo not implemented
}