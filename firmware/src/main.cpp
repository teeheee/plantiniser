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
hal_time* rtc;
hal_ui* ui;

ConfigManage* config_manage;

void setup() 
{
  delay(10);
  Serial.begin(115200);
  Serial.println("\nstart");

  hal_eeprom* eeprom = new hal_eeprom_impl(); 
  hal_mqtt* mqtt = new hal_mqtt_impl(); 
  hal_power* power = new hal_power_impl(); 
  hal_time* rtc = new hal_time_impl(); 
  hal_ui* ui = new hal_ui_impl(); 
  
  ui->init();
  eeprom->init();

  config_manage = new ConfigManage(eeprom);
  if( ! config_manage->all_valid())
  {
    config_manage->process(ui);
  }

/*
  mqtt->init();
  power->init();
  time->init();
  */
}

void loop() 
{
}

