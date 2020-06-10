#ifndef __TEST__

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "mqtt_hal.h"

#define MAX_TOPICS 100

WiFiClient espClient;
PubSubClient client(espClient);

int topic_index = 0;
char* topiclist[MAX_TOPICS]; 
mqtt_sub_callback_t callback_list[MAX_TOPICS];

void callback(char* topic, byte* payload, unsigned int length) 
{
    //TODO
}

bool hal_mqtt_impl::init(std::string ssid, std::string pass, std::string server)
{
    delay(10);
    topic_index = 0;
    WiFi.begin(ssid.c_str(), pass.c_str());
    int timeout_counter = 0;
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        timeout_counter++;
        if(timeout_counter == 10)
        {
            is_initialized_flag = false;
            return false;
        }
    }
    randomSeed(micros());
    client.setServer(server.c_str(), 1883);
    client.setCallback(callback);

    timeout_counter = 0;
    while(!client.connected()) {
        delay(1);
        process();
        timeout_counter++;
        if(timeout_counter == 10000)
        {
            is_initialized_flag = false;
            return false;
        }
    }
    is_initialized_flag = true;

    return true;
}

void hal_mqtt_impl::pub(std::string topic, std::string payload)
{
    client.publish(topic.c_str(), payload.c_str());
}

void hal_mqtt_impl::sub(std::string topic, mqtt_sub_callback_t callback)
{
    if(topic_index < MAX_TOPICS)
    {
        client.subscribe(topic.c_str());
        callback_list[topic_index] = callback;
        topiclist[topic_index++] = (char*)topic.c_str();
    }
    else
    {
        //error handling
    }
}

void hal_mqtt_impl::process()
{
    if (!client.connected()) 
    {
        // Loop until we're reconnected
        while (!client.connected()) 
        {
            //Serial.print("connect to...");
            // Create a random client ID
            String clientId = "ESP8266Client-";
            clientId += String(random(0xffff), HEX);
            // Attempt to connect
            if (client.connect(clientId.c_str())) 
            {
                //Serial.println("connected");
            } 
            else 
            {
                delay(5000);
            }
        }
    }
    client.loop();
    delay(10);
}


bool hal_mqtt_impl::is_initalized()
{
    return is_initialized_flag;
}

bool hal_mqtt_impl::is_connected()
{
    if(is_initialized_flag)
        return client.connected();
    else
        return false;
}

#endif
