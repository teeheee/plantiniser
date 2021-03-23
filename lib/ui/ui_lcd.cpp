#include "ui_lcd.h"
#include <sstream>
#include <string>

template<typename Base, typename T>
inline bool instanceof(const T *ptr) {
    return dynamic_cast<const Base*>(ptr) != nullptr;
}

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


ui_lcd::ui_lcd(hal_ui* p_ui, ConfigManage* p_config, network_manager* p_network, TimerManager* p_timemanage)
{
    config = p_config;
    ui = p_ui;
    network = p_network;
    time_manage = p_timemanage;
    item_list = config->get_config_item_list();
    config_iterator = item_list->begin();
    state = START_SCREEN;
    fist_run = 1;
}

void ui_lcd::process_start_screen()
{
    if(time_manage->get_tick() || fist_run)
    {
        fist_run=0;
        ui->clear();
        ui->print_at(1, std::string("plantiniser").c_str());
        if(network->is_wifi_connected())
        {
            ui->print_at(2, std::string("wifi connected").c_str());
        }
        else
        {
            ui->print_at(2, std::string("wifi not connected").c_str()); 
        }   
        if(network->is_time_synced())
        {
            ui->print_at(3, (std::string("time: ") + time_manage->get_current_time()).c_str());
        }
        else
        {
            ui->print_at(3, std::string("time: none").c_str());
        }
        ui->print_at(4, (std::string("Version: ") + toString(VERSION)).c_str());
    }
}

void ui_lcd::process_config_menu()
{
    ConfigBaseItem* item;
    item = *config_iterator;
    if(item->type == ConfigBaseItem::CONFIG_STRING_TYPE)
    {
        process_config_string_item((StringItem*)item);
    }
    else if(item->type == ConfigBaseItem::CONFIG_NUMBER_TYPE)
    {
        process_config_number_item((NumberItem*)item); 
    }
    if(config_iterator == item_list->end())
    { 
        config_iterator = item_list->begin();
        state = START_SCREEN;
    }
}


int ui_lcd::get_valid_char_index(char to_search)
{
    for(int i = 0; i < VALID_CHAR_LIST_LENGTH; i++)
    {
        if(valid_character_list[i] == to_search)
            return i;
    }
    return 0;
}

void ui_lcd::process_config_string_item(StringItem* item)
{
    if(fist_run)
    {
        ui->clear();
        position = 0;
        std::string current_value = item->read_data();
        for(unsigned int i = current_value.length(); i < item->get_data_size(); i++)
        {
            current_value += '\0';
        }
        character_index = 0;
        change = 1;
    }
        

    ui->process();
    if(change)
    {
        change = 0;
        ui->clear();
        ui->print_at(1, (const char*)item->get_description());
        ui->print_at(2, (const char*)current_string_value.c_str());
        if(current_string_value[position] == 0)
        {
            ui->print_at(3, "submit?");
        }
    }
    switch(ui->get_event())
    {
        case ENC_ROTATE_PLUS:
            character_index += 1;
            character_index %= VALID_CHAR_LIST_LENGTH;
            current_string_value[position] = valid_character_list[character_index];
            change = 1;
            break;
        case ENC_ROTATE_MINUS:
            character_index += VALID_CHAR_LIST_LENGTH-1;
            character_index %= VALID_CHAR_LIST_LENGTH;
            current_string_value[position] = valid_character_list[character_index];
            change = 1;
            break;
        case ENC_SHORT_PRESS:
            if(character_index == 0 || position+1 == item->get_data_size())
            {
                item->write_data(current_string_value);
                return;
            }
            position++;
            character_index = get_valid_char_index(current_string_value[position]); 
            change = 1;
            break;
        default:
            break;
    }
}

void ui_lcd::process_config_number_item(NumberItem* item)
{
    if(fist_run)
    {
        current_number_value = item->read_data();
        change = 1;
        fist_run = 0;
        ui->clear();
    }
    ui->process();
    if(change)
    {
        change = 0;
        ui->clear();
        ui->print_at(1, (const char*)item->get_description());
        std::string text = toString(current_number_value);
        ui->print_at(2, text.c_str());
        ui->print_at(3, "submit?");
    }
    switch(ui->get_event())
    {
        case ENC_ROTATE_PLUS:
            current_number_value++;
            change = 1;
            break;
        case ENC_ROTATE_MINUS:
            current_number_value--;
            change = 1;
            break;
        case ENC_SHORT_PRESS:
            item->write_data(current_number_value);
            config_iterator++;
            fist_run = 1;
            return;
        default:
            break;
    }
}

void ui_lcd::process()
{   
    switch(state) 
    {
        case START_SCREEN:
            process_start_screen();
            break;
        case CONFIG_MENU:
            process_config_menu();
            break;
    }
}