#include "network_manager.h"
#include "logging.h"


network_manager::network_manager(ConfigManage* p_config, hal_mqtt* amqtt, hal_ota* aota, hal_time* artc, hal_nrf24* anrf24)
{
    nrf24 = anrf24;
    mqtt = amqtt;
    ota = aota;
    rtc = artc;
    config_manage = p_config;
}

bool network_manager::test_checksum(hal_nrf24_package_type* package)
{
    uint8_t sum = 0;
    uint8_t checksum = package->data[package->length-1];
    for(int i = 0; i < package->length-1; i++)
    {
        sum ^= package->data[i];
    }
    if( checksum == sum)
        return true;
    else
        return false;
}

void network_manager::process_nrf24_package(hal_nrf24_package_type* package)
{
    message_type message;
    bool is_topic = true;
    for(int i = 0; i < package->length-1; i++)
    {
        char byte = (char)package->data[i];
        if(is_topic)
        {
            message.topic += byte;
        }
        else
        {
            message.content += byte;
        }
        if(byte == '\n')
        {
            is_topic = false;
        }
    }
    LOG("push message in queue:");
    LOG(message.topic.c_str());
    LOG(message.content.c_str());
    message_queue.push_back(message);
}

void network_manager::manage_nrf24()
{
    hal_nrf24_package_type* package = nrf24->recv();
    if(package)
    {
        LOG("got some package");
        if(test_checksum(package))
        {
            LOG("package is valid");
            process_nrf24_package(package);
        }
    }
}

void network_manager::manage_mqtt()
{
    if(message_queue.size() > 0)
    {
        message_type message = message_queue.front();
        mqtt->pub(message.topic, message.content);
        message_queue.pop_front();
        LOG("pop message from queue:");
        LOG(message.topic.c_str());
        LOG(message.content.c_str());
    }
}

void network_manager::process()
{
    if(mqtt->is_initalized())
    {  
        mqtt->process();
        rtc->process();
        manage_nrf24();
        manage_mqtt();
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
    ota->check_update();
    return true; //todo not implemented
}