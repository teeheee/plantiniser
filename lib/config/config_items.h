#ifndef _CONFIG_ITEMS_
#define _CONFIG_ITEMS_

#include "config_base_item.h"
#include "eeprom_hal.h"
#include "ui_hal.h"



class StringItem : public ConfigBaseItem_Template<std::string>{
public:
    StringItem() : ConfigBaseItem_Template() {}

    StringItem(hal_eeprom *eeprom_pointer, int a_address, int a_datasize, const char* a_description) 
    : ConfigBaseItem_Template(eeprom_pointer, a_address, a_datasize, a_description)
    {
        type = CONFIG_STRING_TYPE;
    }

    std::string read_data()
    {
        if(is_data_valid())
        {
            return std::string((const char*)data_pointer);
        }
        else
        {
            return std::string("");
        }
    }
    
    void write_data(std::string content)
    {
        if(data_size >= content.length())
        {
            memcpy(data_pointer, content.c_str(), content.length());
            memset(&data_pointer[content.length()], 0, data_size-content.length());
            update();
        }
    }
};

class NumberItem : public ConfigBaseItem_Template<int>{
private:

public:
    NumberItem() : ConfigBaseItem_Template() {}

    NumberItem(hal_eeprom *eeprom_pointer, int a_address, const char* a_description) 
    : ConfigBaseItem_Template(eeprom_pointer, a_address, 4, a_description)
    {
        type = CONFIG_NUMBER_TYPE;
    }

    int read_data()
    {
        if(is_data_valid())
        {
            return *((int*)data_pointer);
        }
        else
        {
            return 0;
        }
    }
    
    void write_data(int content)
    {
        memcpy(data_pointer, &content, sizeof(int));
        memset(&data_pointer[sizeof(int)], 0, data_size-sizeof(int));
        update();
    }
};

#endif
