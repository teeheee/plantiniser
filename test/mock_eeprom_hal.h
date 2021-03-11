#ifndef _MOCK_EEPROM_HAL_
#define _MOCK_EEPROM_HAL_

#include "eeprom_hal.h"
#include "gmock/gmock.h"

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

#endif