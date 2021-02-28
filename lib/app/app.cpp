#include "app.h"


app::app()
{
  eeprom = new hal_eeprom_impl(); 
  mqtt = new hal_mqtt_impl(); 
  power = new hal_power_impl(); 
  rtc = new hal_time_impl(); 
  ui = new hal_ui_impl(); 
  ota = new hal_ota_impl();
  
  ui->init();
  eeprom->init();
  power->init();

  config_manage = new ConfigManage(eeprom);
  if( ! config_manage->all_valid())
  {
    config_manage->process(ui);
  }
}


void app::minute_tick(int minute, int hour)
{
  if(minute == config_manage->get_water_valve_on_minute() 
  && hour == config_manage->get_water_valve_on_hour())
  {
    g_pump_timeout = config_manage->get_water_valve_on_duration();
  }
  if(g_pump_timeout)
  {
    power->set(0,true);
    g_pump_timeout--;
  }
  else
  {
    power->set(0,false);
  }
  ui->clear();
  ui->print_at(1,"Plantiniser");
  ui->print_at(2,"active");
  std::string current_time = rtc->get_formated();
  ui->print_at(3,current_time.c_str());
}

void app::process()
{
  if(mqtt->is_initalized())
  {
    ota->check_update();
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

    encoder_event_t event = ui->get_event();
    switch(event)
    {
      case ENC_NO_EVENT:
        break;
      case ENC_ROTATE_MINUS:
        break;
      case ENC_ROTATE_PLUS:
        break;
      case ENC_SHORT_PRESS:
        g_pump_timeout = 2;
        ui->print_at(4, "triggered pump event");
        break;
      case ENC_LONG_PRESS:
        config_manage->process(ui);
        break;
    }
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
    if(mqtt->is_initalized()
      && mqtt->is_connected())
    {
      ui->print_at(3,"read rtc server...");
      rtc->init();
    }
    else
    {
      ui->print_at(3,"could not connect ");
      ui->print_at(4,"retry...");
    }
  }
}