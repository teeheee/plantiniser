#ifndef _CONFIG_ITEMS_
#define _CONFIG_ITEMS_

#include "config_base_item.h"
#include "eeprom_hal.h"
#include "ui_hal.h"

#include <string>
#include <string.h>

class StringItem : public ConfigBaseItem_Template<std::string>{
public:
    StringItem() : ConfigBaseItem_Template() {}

    StringItem(hal_eeprom *eeprom_pointer, int a_address, int a_datasize, const char* a_description) 
    : ConfigBaseItem_Template(eeprom_pointer, a_address, a_datasize, a_description)
    {

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

    void config_user_interface(hal_ui* ui)
    {
        ui->clear();
        int position = 0;
        uint8_t change = 1;
        while(1)
        {
            if(change)
            {
                change = 0;
                ui->print_at(0, (const char*)description);
                ui->print_at(1, (const char*)data_pointer);
                if(data_pointer[position] == 0)
                {
                    ui->print_at(2, "submit?");
                }
            }
            switch(ui->get_event())
            {
                case ENC_ROTATE_PLUS:
                    data_pointer[position]++;
                    change = 1;
                    break;
                case ENC_ROTATE_MINUS:
                    data_pointer[position]--;
                    change = 1;
                    break;
                case ENC_SHORT_PRESS:
                    position++;
                    change = 1;
                    break;
                default:
                    break;
            }
        }
    }
};

#endif
