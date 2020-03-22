#include <config_hal.h>

#ifdef UNIT_TEST

#include <string.h>

uint8_t mock_memory[EEPROM_MEMSIZE];

void eeprom_init()
{
    memset(mock_memory, 0, EEPROM_MEMSIZE);
}

void eeprom_update()
{
}

void eeprom_put(uint8_t* byte, int length, int address)
{
    memcpy((void*)&mock_memory[address], (void*)byte, length);
}

void eeprom_get(uint8_t* byte, int length, int address)
{
    memcpy((void*)byte, (void*)&mock_memory[address], length);
}

#else

#include "EEPROM.h"

void eeprom_init()
{
    EEPROM.begin(EEPROM_MEMSIZE);
}

void eeprom_update()
{
    EEPROM.commit();
}

void eeprom_put(uint8_t* byte, int length, int address)
{
    for(int i = 0; i < length; i++)
    {
        EEPROM.put(address+i, byte[i]);
    }
}

void eeprom_get(uint8_t* byte, int length, int address)
{
    for(int i = 0; i < length; i++)
    {
        EEPROM.put(address+i, byte[i]);
    }
}

#endif