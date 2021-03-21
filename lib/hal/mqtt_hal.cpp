#ifndef __TEST__

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "mqtt_hal.h"
#include "logging.h"

#define MAX_TOPICS 100

WiFiClient mqtt_client;
PubSubClient client(mqtt_client);

char server_name[100];

int topic_index = 0;
char* topiclist[MAX_TOPICS]; 
mqtt_sub_callback_t callback_list[MAX_TOPICS];

void callback(char* topic, byte* payload, unsigned int length) 
{
    //TODO
}



bool hal_mqtt_impl::init(std::string server)
{
    topic_index = 0;
    lastReconnectAttempt = 0;
    randomSeed(micros());
    LOG("setup mqtt server:");
    LOG(server.c_str());
    memcpy(server_name,server.c_str(),server.length());
    client.setServer(server_name, 1883);
    client.setCallback(callback);
    is_initialized_flag = true;
    return true;
}

bool hal_mqtt_impl::pub(std::string topic, std::string payload)
{
    if(topic.back() == '\n')
        topic = topic.substr(0, topic.size()-1);
    if(client.publish(topic.c_str(), payload.c_str()))
    {
        return true;
    }
    else
    {
        LOG("mqtt_hal client.publish failed");
        return false;
    }
}

bool hal_mqtt_impl::sub(std::string topic, mqtt_sub_callback_t callback)
{
    if(topic.back() == '\n')
        topic = topic.substr(0, topic.size()-1);
    if(topic_index < MAX_TOPICS)
    {
        client.subscribe(topic.c_str());
        callback_list[topic_index] = callback;
        topiclist[topic_index++] = (char*)topic.c_str();
    }
    else
    {
        return false;
    }
    return true;
}

void hal_mqtt_impl::process()
{
    if (!client.connected()) 
    {
        String clientId = "ESP8266Client-";
        clientId += String(random(0xffff), HEX);
        if (client.connect(clientId.c_str())) {
        } else {
            delay(5000);
        }
    }
    else
    {
        client.loop();
    }
}


bool hal_mqtt_impl::is_initalized()
{
    return is_initialized_flag;
}

bool hal_mqtt_impl::is_connected()
{
    return client.connected();
}

#endif
