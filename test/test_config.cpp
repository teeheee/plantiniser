#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "config_items.h"
#include "config_base_item.h"
#include "config.h"

#include "mock_eeprom_hal.h"

#include <string>
#include <queue>
#include <string.h>


uint8_t calc_checksum(uint8_t* data, int datasize)
{
    uint8_t checksum = 0;
    for(int i = 0; i < datasize; i++)
        checksum ^= data[i];
    return checksum;
}

TEST(StringItem, Initilaization_Fail)
{  
  mock_hal_eeprom eeprom;
  eeprom.clear();

  eeprom.init(); 
  StringItem wlan_ssid = StringItem(&eeprom, 0, 20, "WLAN SSID");
  
  EXPECT_EQ(wlan_ssid.is_data_valid(), false);
}

TEST(StringItem, Initilaization_Pass)
{
  mock_hal_eeprom eeprom;
  eeprom.clear();
  std::string teststring = std::string("1234");
  eeprom.memory[0] = calc_checksum((uint8_t*)teststring.data(), teststring.size());
  memcpy(&eeprom.memory[1], teststring.data(), teststring.size());

  eeprom.init();
  StringItem wlan_ssid = StringItem(&eeprom, 0, 20, "WLAN SSID");
  
  EXPECT_EQ(wlan_ssid.is_data_valid(), true);
}

TEST(StringItem, read_write)
{
  mock_hal_eeprom eeprom;
  eeprom.clear();
  std::string passkey = std::string("1234");

  eeprom.init();
  StringItem wlan_ssid = StringItem(&eeprom, 0, 20, "WLAN SSID");
  wlan_ssid.write_data(passkey);
  std::string text = wlan_ssid.read_data();
  EXPECT_TRUE( text == passkey );
}

