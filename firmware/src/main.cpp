#include <ESP8266WiFi.h>
#include "power.h"
#include "mqtt.h"
#include "encoder.h"
#include "display.h"
#include "time_man.h"

const char* ssid = "Karl-Marx-Stadt";
const char* password = "penisrofelcopter88";
const char* mqtt_server = "doerte";

void power_event(byte* payload, unsigned int length)
{
  Serial.println("power event");
}

void setup() 
{
  delay(10);
  Serial.begin(115200);
  Serial.println("\n\nstart");
  display_init();
  display_print("display init\n");
  display_print("power init\n");
  power_init();
  display_print("encoder init\n");
  encoder_init();
  display_print("time init\n");
  time_init();
  display_print("mqtt init\n");
  mqtt_init(ssid, password, mqtt_server);
  mqtt_sub((char*)"watering/power", &power_event);
}

void loop() 
{
  mqtt_process();
  time_process();
  encoder_process();
  if(encoder_get_event() == ENC_SHORT_PRESS)
  {
    display_clear();
  }
  static uint32_t timestamp = 0;
  if(millis()-timestamp > 2000 || timestamp == 0)
  {
    display_print(time_get_formated().c_str());
    display_print("\n");
    timestamp = millis();
    mqtt_pub("watering/alive",(uint8_t*)"yes",3);
    Serial.println("hello world");
  }
}


/*

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
const char* ssid = "Karl-Marx-Stadt";
const char* password = "penisrofelcopter88";
const char* mqtt_server = "doerte";
WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
void setup() {
  Serial.begin(115200);
  delay(10);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  randomSeed(micros());
  client.setServer(mqtt_server, 1883);
}
void loop() {
  if (!client.connected()) {
    // Loop until we're reconnected
    while (!client.connected()) {
      Serial.print("connect to...");
      // Create a random client ID
      String clientId = "ESP8266Client-";
      clientId += String(random(0xffff), HEX);
      // Attempt to connect
      if (client.connect(clientId.c_str())) {
        Serial.println("connected");
      } else {
        delay(5000);
      }
    }
  }
  client.loop();
  if (millis() - lastMsg > 2000) {
    lastMsg = millis();
    client.publish("outTopic", "hi");
  }
}
*/

/*
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <U8g2lib.h>
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g22(U8G2_R0);
void setup(void) {
  Wire.begin();
  u8g22.begin();
}
void loop(void) {
  u8g22.firstPage();
  do {
    u8g22.setFont(u8g2_font_ncenB14_tr);
    u8g22.drawStr(0,20,"Hello World!");
  } while ( u8g22.nextPage() );
  delay(1000);
}
*/