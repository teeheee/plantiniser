#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "config_items.h"
#include "config_base_item.h"
#include "config.h"

#include "eeprom_hal.h"
#include "ui_hal.h"

#include <string>
#include <queue>
#include <string.h>

#define EEPROM_SIZE 1024

class mock_hal_eeprom : public hal_eeprom
{
  private:
    uint8_t _temp_memory[EEPROM_SIZE];
  public:
    uint8_t memory[EEPROM_SIZE];
    void init()
    {
      memcpy(_temp_memory, memory, EEPROM_SIZE);
    }
    void update()
    {
      memcpy(memory, _temp_memory, EEPROM_SIZE);
    }
    void put(uint8_t* byte, int length, int address)
    {
      memcpy(&_temp_memory[address], byte, length);
    }
    void get(uint8_t* byte, int length, int address)
    {
      memcpy(byte, &_temp_memory[address], length);
    }
    void clear()
    {
      memset(memory,0xff,EEPROM_SIZE);
      memset(_temp_memory,0xff,EEPROM_SIZE);
    }
};

mock_hal_eeprom eeprom;


uint8_t calc_checksum(uint8_t* data, int datasize)
{
    uint8_t checksum = 0;
    for(int i = 0; i < datasize; i++)
        checksum ^= data[i];
    return checksum;
}

TEST(StringItem, Initilaization_Fail)
{  
  eeprom.clear();

  eeprom.init(); 
  StringItem wlan_ssid = StringItem(&eeprom, 0, 20, "WLAN SSID");
  
  EXPECT_EQ(wlan_ssid.is_data_valid(), false);
}

TEST(StringItem, Initilaization_Pass)
{
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
  eeprom.clear();
  std::string passkey = std::string("1234");

  eeprom.init();
  StringItem wlan_ssid = StringItem(&eeprom, 0, 20, "WLAN SSID");
  wlan_ssid.write_data(passkey);
  std::string text = wlan_ssid.read_data();
  EXPECT_TRUE( text == passkey );
}


int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
