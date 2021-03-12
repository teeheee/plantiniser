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
    Serial.println(radio.init(1, 6, 7)); // Set radio to Id = 0, along with its CE and CSN pins
    Serial.println("init");
}

uint8_t calc_checksum(uint8_t* data, int data_length)
{
  uint8_t sum =0;
  for(int i = 0; i < data_length; i++)
      sum ^= data[i];
  return sum;
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
    uint8_t checksum = calc_checksum(data,length);
    data[length] = checksum;
    length++;
    Serial.println("send");
    Serial.println(topic);
    Serial.println(content);
    Serial.println(checksum);
    radio.send(0, data, length);
    delay(1000);
}
