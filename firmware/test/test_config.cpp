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

class mock_hal_ui : public hal_ui{
  public:
    std::queue<encoder_event_t> envent_list;
    void add_event(encoder_event_t event)
    {
      envent_list.push(event);
    }
    void init()
    {
      while(envent_list.size() > 0)
        envent_list.pop();
    }
    void print(const char* text){}
    void print(int text){}
    void print_at(int line, const char* text){}
    void clear(){}
    encoder_event_t get_event()
    {
      if(envent_list.size() > 0)
      {
        encoder_event_t tmp = envent_list.front();
        envent_list.pop();
        return tmp;
      }
      else
      {
        return ENC_NO_EVENT;  
      }
    }
    void process(){}
};

mock_hal_ui ui;

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

TEST(ConfigManage, SetSSID)
{
  eeprom.clear();
  ui.init();
  for(int i = 0; i < 20; i++)
    ui.add_event(ENC_SHORT_PRESS);

  eeprom.init();
  ConfigManage manage(&eeprom);
  manage.process(&ui);
}


int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
