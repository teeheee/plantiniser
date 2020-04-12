#include <ESP8266WiFi.h>

#include "eeprom_hal.h"
#include "mqtt_hal.h"
#include "power_hal.h"
#include "time_hal.h"
#include "ui_hal.h"

#include "config.h"

hal_eeprom* eeprom; 
hal_mqtt* mqtt; 
hal_power* power; 
hal_time* time;
hal_ui* ui;

ConfigManage config_manage;

void setup() 
{
  delay(10);
  Serial.begin(115200);
  Serial.println("\nstart");
  hal_eeprom* eeprom = hal_eeprom_impl(); 
  hal_mqtt* mqtt = hal_mqtt_impl(); 
  hal_power* power = hal_power_impl(); 
  hal_time* time = hal_time_impl(); 
  hal_ui* ui = hal_ui_impl(); 
  ui->init();
  eeprom->init();
  mqtt->init();
  power->init();
  time->init();

  config_manage = ConfigManage(eeprom);
  if( ! config_manage.all_valid())
  {
    config_manage.process();
  }
}

void loop() 
{
}

