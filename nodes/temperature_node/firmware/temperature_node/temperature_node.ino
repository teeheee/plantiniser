#include <SPI.h>
#include <NRFLite.h>
#include "DHT.h"     
#include "LowPower.h" 
     
#define DHTPIN 8         
#define DHTTYPE DHT22 

DHT dht(DHTPIN, DHTTYPE);
NRFLite radio;

#define MAX_DATA 32
uint8_t data[MAX_DATA];
#define TOPIC_SIZE 8
const char* topic = "plt/temp";

void setup()
{
    pinMode(5,OUTPUT);
    digitalWrite(5,LOW);
    dht.begin();
    delay(2000);  
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
    radio.init(1, 9, 10);
    //measure
    float h = dht.readHumidity();    // Lesen der Luftfeuchtigkeit und speichern in die Variable h
    float t = dht.readTemperature(); // Lesen der Temperatur in °C und speichern in die Variable t
    if (isnan(h) || isnan(t)) {       
      Serial.println("Fehler beim auslesen des Sensors!");
      delay(1000);
      return;
    }
    
    //prepare package
    int topic_size = TOPIC_SIZE;
    for(int i = 0; i < topic_size; i++)
      data[i] = topic[i];
    data[topic_size] = '\n';
    char content[20];
    int content_size = sprintf(content, "%d,%d", int(t*10), int(h*10));
    for(int i = 0; i < content_size; i++)
      data[topic_size+1+i] = content[i];
    int length = topic_size+1+content_size;
    uint8_t checksum = calc_checksum(data,length);
    data[length] = checksum;
    length++;
    radio.send(0, data, length);
    digitalWrite(5,HIGH);
    radio.powerDown();
    for(int i = 0; i < 60; i++)
      LowPower.powerDown(SLEEP_1S, ADC_OFF, BOD_OFF);
    digitalWrite(5,LOW);
}
