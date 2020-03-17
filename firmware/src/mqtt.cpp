#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "mqtt.h"
#include "display.h"

#define PRINT_WRAPPER(text) Serial.print(text)
#define PRINT_WRAPPERLN(text) Serial.println(text);

#define MAX_TOPICS 100

WiFiClient espClient;
PubSubClient client(espClient);

int topic_index = 0;
char* topiclist[MAX_TOPICS]; 
mqtt_sub_callback_t callback_list[MAX_TOPICS];

void callback(char* topic, byte* payload, unsigned int length) 
{
  PRINT_WRAPPER("Message arrived [");
  PRINT_WRAPPER(topic);
  PRINT_WRAPPER("] ");
}

void mqtt_init(const char* ssid,const char* password,const char* server)
{
    delay(10);
    topic_index = 0;
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        PRINT_WRAPPER(".");
    }
    randomSeed(micros());
    PRINT_WRAPPERLN("");
    PRINT_WRAPPERLN("WiFi connected");
    PRINT_WRAPPERLN("IP address: ");
    IPAddress ip = WiFi.localIP();
    PRINT_WRAPPERLN(ip.toString().c_str());
    client.setServer(server, 1883);
    client.setCallback(callback);
}

void mqtt_pub(char* topic, uint8_t* payload, unsigned int length)
{
    client.publish(topic, (const char*)payload);
}

void mqtt_sub(char* topic, mqtt_sub_callback_t callback)
{
    if(topic_index < MAX_TOPICS)
    {
        client.subscribe(topic);
        callback_list[topic_index] = callback;
        topiclist[topic_index++] = topic;
    }
    else
    {
        PRINT_WRAPPERLN("ERROR too many topics");
    }
}

void mqtt_process()
{
    if (!client.connected()) 
    {
        // Loop until we're reconnected
        while (!client.connected()) 
        {
            Serial.print("connect to...");
            // Create a random client ID
            String clientId = "ESP8266Client-";
            clientId += String(random(0xffff), HEX);
            // Attempt to connect
            if (client.connect(clientId.c_str())) 
            {
                Serial.println("connected");
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