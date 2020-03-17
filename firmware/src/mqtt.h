#ifndef _MQTT_H_
#define _MQTT_H_

#include <stdint.h>

typedef void (*mqtt_sub_callback_t)(uint8_t* payload, unsigned int length);

void mqtt_init(const char* ssid, const char* pass, const char* server);
void mqtt_pub(char* topic, uint8_t* payload, unsigned int length);
void mqtt_sub(char* topic, mqtt_sub_callback_t callback);
void mqtt_process();

#endif
