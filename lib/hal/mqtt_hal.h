#ifndef _MQTT_HAL_H_
#define _MQTT_HAL_H_

#include <string>

typedef void (*mqtt_sub_callback_t)(std::string payload);

class hal_mqtt {
public:
    virtual bool init(std::string ssid, std::string pass, std::string server) = 0;
    virtual void pub(std::string topic, std::string payload) = 0;
    virtual void sub(std::string topic, mqtt_sub_callback_t callback) = 0;
    virtual void process() = 0;
    virtual bool is_initalized() = 0;
    virtual bool is_connected() = 0;
};

class hal_mqtt_impl : public hal_mqtt{
private:
    bool is_initialized_flag = false;
public:
    bool init(std::string ssid, std::string pass, std::string server);
    void pub(std::string topic, std::string payload);
    void sub(std::string topic, mqtt_sub_callback_t callback);
    void process();
    bool is_initalized();
    bool is_connected();
};

#endif
