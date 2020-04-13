#ifndef _TEST_

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
  Serial.begin(115200);
  Serial.println("start main");
  delay(10);

  eeprom = new hal_eeprom_impl(); 
  mqtt = new hal_mqtt_impl(); 
  power = new hal_power_impl(); 
  rtc = new hal_time_impl(); 
  ui = new hal_ui_impl(); 
  
  ui->init();
  Serial.println("ui init");
  eeprom->init();
  Serial.println("eeprom init");
  power->init();
  Serial.println("power init");

  config_manage = new ConfigManage(eeprom);
  if( ! config_manage->all_valid())
  {
    Serial.println("config invalid start configuration...");
    config_manage->process(ui);
  }
}

void minute_tick(int minute, int hour)
{
  if(minute == 1)
  {
    power->set(0,true);
  }
  if(minute == 2)
  {
    power->set(0,false);
  }
  ui->clear();
  ui->print_at(1,"Plantiniser");
  ui->print_at(2,"active");
  std::string current_time = rtc->get_formated();
  ui->print_at(3,current_time.c_str());
}

void loop() 
{
  if(mqtt->is_initalized())
  {
    static int last_minute = 0;
    int current_minute = rtc->get_minutes();
    if(last_minute != current_minute)
    {
      minute_tick(rtc->get_minutes(), rtc->get_hours());
      last_minute = current_minute;
    }
    mqtt->process();
    rtc->process();
    ui->process();
  }
  else
  {
    ui->clear();
    ui->print_at(1,"Plantiniser");

    std::string ssid = config_manage->get_wifi_ssid();
    std::string passkey = config_manage->get_wifi_passkey();
    std::string server = config_manage->get_server_address();

    ui->print_at(2,"connecting...");
    mqtt->init(ssid, passkey, server);
    if(mqtt->is_initalized())
    {
      rtc->init();
    }
    else
    {
      ui->clear();
      ui->print_at(1,"Plantiniser");
      ui->print_at(2,"could not connect");
      delay(1000);
      Serial.println("config invalid start configuration...");
      config_manage->process(ui);
    }
  }
}

#endif

