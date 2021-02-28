#ifndef _CONFIG_ITEMS_
#define _CONFIG_ITEMS_

#include "config_base_item.h"
#include "eeprom_hal.h"
#include "ui_hal.h"

#include <sstream>
#include <string>

/**
 * @brief this is a fix for the arm gcc toolchain not supporting tostring even if std=c11 is enabled
 */
template<class T>
std::string toString(const T &value) {
    std::ostringstream os;
    os << value;
    return os.str();
}

#define VALID_CHAR_LIST_LENGTH 83
const char valid_character_list[] = "\0abcdefghijklmnopqrstuvwxyz0123456789!§$%&/()=?*+#-_.:,;ABCDEFGHIJKLMNOPQRSTUVWXYZ ";


class StringItem : public ConfigBaseItem_Template<std::string>{
private:
    int get_valid_char_index(char to_search)
    {
        for(int i = 0; i < VALID_CHAR_LIST_LENGTH; i++)
        {
            if(valid_character_list[i] == to_search)
                return i;
        }
        return 0;
    }
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
        unsigned int position = 0;
        int character_index[data_size];
        std::string current_value = read_data();
        for(unsigned int i = current_value.length(); i < data_size; i++)
        {
            current_value += '\0';
        }
        character_index[0] = 0;
        uint8_t change = 1;
        while(1)
        {
            ui->process();
            if(change)
            {
                change = 0;
                ui->clear();
                ui->print_at(1, (const char*)description);
                ui->print_at(2, (const char*)current_value.c_str());
                if(current_value[position] == 0)
                {
                    ui->print_at(3, "submit?");
                }
            }
            switch(ui->get_event())
            {
                case ENC_ROTATE_PLUS:
                    character_index[position] += 1;
                    character_index[position] %= VALID_CHAR_LIST_LENGTH;
                    current_value[position] = valid_character_list[character_index[position]];
                    change = 1;
                    break;
                case ENC_ROTATE_MINUS:
                    character_index[position] += VALID_CHAR_LIST_LENGTH-1;
                    character_index[position] %= VALID_CHAR_LIST_LENGTH;
                    current_value[position] = valid_character_list[character_index[position]];
                    change = 1;
                    break;
                case ENC_SHORT_PRESS:
                    if(character_index[position] == 0 || position+1 == data_size)
                    {
                        write_data(current_value);
                        return;
                    }
                    position++;
                    character_index[position] = get_valid_char_index(current_value[position]); 
                    change = 1;
                    break;
                default:
                    break;
            }
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

    void config_user_interface(hal_ui* ui)
    {
        ui->clear();
        int current_value = read_data();
        uint8_t change = 1;
        while(1)
        {
            ui->process();
            if(change)
            {
                change = 0;
                ui->clear();
                ui->print_at(1, (const char*)description);
                std::string text = toString(current_value);
                ui->print_at(2, text.c_str());
                ui->print_at(3, "submit?");
            }
            switch(ui->get_event())
            {
                case ENC_ROTATE_PLUS:
                    current_value++;
                    change = 1;
                    break;
                case ENC_ROTATE_MINUS:
                    current_value--;
                    change = 1;
                    break;
                case ENC_SHORT_PRESS:
                    write_data(current_value);
                    return;
                default:
                    break;
            }
        }
    }
};

#endif
