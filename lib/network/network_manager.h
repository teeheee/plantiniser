#ifndef _NETWORK_MANAGER_H_
#define _NETWORK_MANAGER_H_

#include "mqtt_hal.h"
#include "ota_hal.h"
#include "nrf24_hal.h"
#include "time_hal.h"
#include "config.h"
#include <list>

typedef struct {
    std::string topic;
    std::string content;
} message_type;

class network_manager{
    private:
        hal_mqtt* mqtt;
        hal_ota* ota;
        hal_time* rtc;
        hal_nrf24* nrf24;
        ConfigManage* config_manage;
        std::list<message_type> message_queue;
        bool test_checksum(hal_nrf24_package_type* package);
        void process_nrf24_package(hal_nrf24_package_type* package);
        void manage_nrf24();
        void manage_mqtt();
    public:
        network_manager(ConfigManage* p_config, hal_mqtt* mqtt, hal_ota* ota, hal_time* rtc, hal_nrf24* nrf24);
        void process();
        bool is_wifi_connected();
        bool is_mqtt_server_active();
        bool is_time_synced();
        bool is_ota_up_to_date();
};

#endif
