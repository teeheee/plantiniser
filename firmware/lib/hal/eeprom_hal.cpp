#ifndef __TEST__

#include "eeprom_hal.h"
#include "EEPROM.h"

void hal_eeprom_impl::init()
{
    EEPROM.begin(EEPROM_MEMSIZE);
}

void hal_eeprom_impl::update()
{
    EEPROM.commit();
}

void hal_eeprom_impl::put(uint8_t* byte, int length, int address)
{
    for(int i = 0; i < length; i++)
    {
        EEPROM.put(address+i, byte[i]);
    }
}

void hal_eeprom_impl::get(uint8_t* byte, int length, int address)
{
    for(int i = 0; i < length; i++)
    {
        EEPROM.get(address+i, byte[i]);
    }
}

#endif
