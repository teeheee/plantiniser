//#include "EEPROM.h"
#include "config_base_item.h"
#include "config_hal.h"
#include <string.h>
#include <stdlib.h>

int address_counter = 0;

ConfigBaseItem::ConfigBaseItem(int a_datasize, const char* a_description)
{
    data_size = a_datasize;
    description = a_description;
    uint8_t checksum;
    eeprom_get(&checksum, 1, address_counter);
    address_counter += 1;
    data_pointer = (uint8_t*)malloc(data_size);
    eeprom_get(data_pointer, 1, address_counter);
    uint8_t real_checksum = calc_checksum(data_pointer, data_size);
    if(real_checksum != checksum)
    {
        memset(data_pointer, 0, data_size);
        valid_data = false;
    }
    else
    {
        valid_data = true;
    }
    
}


uint8_t ConfigBaseItem::calc_checksum(uint8_t* data, int datasize)
{
    uint8_t checksum = 0;
    for(int i = 0; i < datasize; i++)
        checksum ^= data[i];
}

bool ConfigBaseItem::is_data_valid()
{
    return valid_data;
}

const char*  ConfigBaseItem::get_description()
{
    return description;
}
