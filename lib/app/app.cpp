#include "app.h"

app::app()
{
  eeprom = new hal_eeprom_impl(); 
  mqtt = new hal_mqtt_impl(); 
  power = new hal_power_impl(); 
  rtc = new hal_time_impl(); 
  ui = new hal_ui_impl(); 
  ota = new hal_ota_impl();
  serial = new hal_serial_impl();
  nrf24 = new hal_nrf24_impl();
  wifi = new hal_wifi_impl();

  ui->init();
  serial->init();
  eeprom->init();
  power->init();
  nrf24->init();

  config_manage = new ConfigManage(eeprom);
  network_manage = new network_manager(config_manage, mqtt, ota, rtc, nrf24, wifi);
  time_manage = new TimerManager(config_manage, power, rtc);
  ui_lcd_object = new ui_lcd(ui, config_manage, network_manage, time_manage);
  ui_serial_object = new ui_serial(serial, config_manage, network_manage, time_manage);
}

void app::process()
{
  ui_lcd_object->process();
  ui_serial_object->process(); // this function should not be blocking
  network_manage->process();
  time_manage->process();
}