#include <SPI.h>
#include <NRFLite.h>

#define MAX_DATA 32

NRFLite radio;

uint8_t data[MAX_DATA];

#define TOPIC_SIZE 8
const char* topic = "plt/temp";
#define CONTENT_SIZE 2
const char* content = "10";

void setup()
{
    Serial.begin(115200);
    Serial.println("start");
    Serial.println(radio.init(0, 6, 7)); // Set radio to Id = 0, along with its CE and CSN pins
    Serial.println("init");
}

void loop()
{
    int topic_size = TOPIC_SIZE;
    int content_size = CONTENT_SIZE;
    for(int i = 0; i < topic_size; i++)
      data[i] = topic[i];
    data[topic_size] = '\n';
    for(int i = 0; i < content_size; i++)
      data[TOPIC_SIZE+1+i] = content[i];
    int length = TOPIC_SIZE+1+CONTENT_SIZE;
    Serial.println("send");
    Serial.println(topic);
    Serial.println(content);
    radio.send(0, data, length);
    delay(1000);
}
