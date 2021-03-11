#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "config.h"
#include "network_manager.h"

#include "mock_nrf24_hal.h"
#include "mock_mqtt_hal.h"
#include "mock_ota_hal.h"
#include "mock_time_hal.h"
#include "mock_eeprom_hal.h"


TEST(network_manager, process_not_connecting_wifi)
{
  mock_hal_nrf24 nrf24;
  mock_hal_mqtt mqtt;
  mock_hal_ota ota;
  mock_hal_time rtc;
  mock_hal_eeprom eeprom;
  ConfigManage config(&eeprom);
  network_manager nm(&config, &mqtt, &ota, &rtc, &nrf24);
}

