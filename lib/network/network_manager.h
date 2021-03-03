#ifndef _NETWORK_MANAGER_H_
#define _NETWORK_MANAGER_H_

#include "mqtt_hal.h"
#include "ota_hal.h"
#include "time_hal.h"
#include "config.h"

class network_manager{
    private:
        hal_mqtt* mqtt;
        hal_ota* ota;
        hal_time* rtc;
        ConfigManage* config_manage;
    public:
        network_manager(ConfigManage* p_config, hal_mqtt* mqtt, hal_ota* ota, hal_time* rtc);
        void process();
        bool is_wifi_connected();
        bool is_mqtt_server_active();
        bool is_time_synced();
        bool is_ota_up_to_date();
};

#endif
