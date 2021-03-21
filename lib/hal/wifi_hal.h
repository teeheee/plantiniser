#ifndef _WIFI_HAL_H_
#define _WIFI_HAL_H_

#include <string>

typedef void (*mqtt_sub_callback_t)(std::string payload);

class hal_wifi {
public:
    virtual bool init(std::string ssid, std::string pass) = 0;
    virtual bool is_initalized() = 0;
    virtual bool is_connected() = 0;
};

class hal_wifi_impl : public hal_wifi{
private:
    bool is_initialized_flag = false;
public:
    bool init(std::string ssid, std::string pass);
    bool is_initalized();
    bool is_connected();
};

#endif
