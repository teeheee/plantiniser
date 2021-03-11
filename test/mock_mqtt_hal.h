#ifndef _MOCK_MQTT_HAL_
#define _MOCK_MQTT_HAL_

#include "gmock/gmock.h"
#include "mqtt_hal.h"

class mock_hal_mqtt : public hal_mqtt{
public:
    bool init(std::string ssid, std::string pass, std::string server){return true;};
    void pub(std::string topic, std::string payload){};
    void sub(std::string topic, mqtt_sub_callback_t callback){};
    void process(){};
    bool is_initalized(){return true;};
    bool is_connected(){return true;};
};

#endif