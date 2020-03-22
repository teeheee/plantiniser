#ifndef _CONFIG_HAL_H_
#define _CONFIG_HAL_H_

#include <stdint.h>

#define EEPROM_MEMSIZE 500

void eeprom_update();
void eeprom_put(uint8_t* byte, int length, int address);
void eeprom_get(uint8_t* byte, int length, int address);

#endif