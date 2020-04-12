#ifndef _CONFIG_BASE_ITEM_
#define _CONFIG_BASE_ITEM_

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "eeprom_hal.h"
#include "ui_hal.h"

class ConfigBaseItem
{
    public:
        virtual void config_user_interface(hal_ui* user_interface) = 0;
        virtual bool is_data_valid() = 0;
};

template <class T> class ConfigBaseItem_Template : public ConfigBaseItem{
public:
    ConfigBaseItem_Template()
    {

    }

    ConfigBaseItem_Template(hal_eeprom* a_eeprom_ptr, int a_address, int a_datasize, const char* a_description)
    {
        eeprom_ptr = a_eeprom_ptr;
        data_size = a_datasize;
        description = a_description;
        address = a_address;
        
        int address_counter = address;
        uint8_t checksum;
        eeprom_ptr->get(&checksum, 1, address_counter);
        address_counter += 1;
        data_pointer = (uint8_t*)malloc(data_size);
        memset(data_pointer, 0, data_size);
        eeprom_ptr->get(data_pointer, data_size, address_counter);
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
    
    ~ConfigBaseItem_Template(){
        if(data_pointer)
            free(data_pointer);
    };

    bool is_data_valid()
    {
        return valid_data;
    }
    const char* get_description()
    {
        return description;
    }

    virtual T read_data() = 0;
    virtual void write_data(T) = 0;
protected:
    void update()
    {
        uint8_t checksum = calc_checksum(data_pointer, data_size);
        eeprom_ptr->put(&checksum, 1, address);
        eeprom_ptr->put(data_pointer, data_size, address+1);
        eeprom_ptr->update();
        valid_data = true;
    }

    uint8_t calc_checksum(uint8_t* data, int datasize)
    {
        uint8_t checksum = 0;
        for(int i = 0; i < datasize; i++)
            checksum ^= data[i];
        return checksum;
    }

    uint8_t* data_pointer;
    unsigned int data_size;
    unsigned int address;
    bool valid_data;
    const char* description;
    hal_eeprom* eeprom_ptr;
};

#endif