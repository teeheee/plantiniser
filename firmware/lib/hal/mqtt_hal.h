#ifndef _MQTT_HAL_H_
#define _MQTT_HAL_H_

#include <string>

class hal_mqtt {
public:
    virtual void init(std::string ssid, std::string pass, std::string server) = 0;
    virtual void pub(std::string topic, std::string payload) = 0;
    virtual void sub(std::string topic, mqtt_sub_callback_t callback) = 0;
    virtual void process();
};

class hal_mqtt_impl : public hal_mqtt{
};

#endif
