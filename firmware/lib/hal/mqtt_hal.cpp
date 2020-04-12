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

void hal_mqtt_impl::init(std::string ssid, std::string pass, std::string server)
{
    delay(10);
    topic_index = 0;
    WiFi.begin(ssid.c_str(), pass.c_str());
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
    randomSeed(micros());
    IPAddress ip = WiFi.localIP();
    client.setServer(server.c_str(), 1883);
    client.setCallback(callback);
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

#endif
