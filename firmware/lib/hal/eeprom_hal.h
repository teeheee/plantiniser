#ifndef _CONFIG_HAL_H_
#define _CONFIG_HAL_H_

#include <stdint.h>

#define EEPROM_MEMSIZE 500

class hal_eeprom {
public:
    virtual void init() = 0;
    virtual void update() = 0;
    virtual void put(uint8_t* byte, int length, int address) = 0;
    virtual void get(uint8_t* byte, int length, int address) = 0;
};

class hal_eeprom_impl : public hal_eeprom{
    void init();
    void update();
    void put(uint8_t* byte, int length, int address);
    void get(uint8_t* byte, int length, int address);
};

#endif
