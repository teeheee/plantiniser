#include "ui_serial.h"
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

ui_serial::ui_serial(hal_serial* p_serial, ConfigManage* p_config, network_manager* p_network)
{
    item_list = p_config->get_config_item_list();
    config_iterator = item_list->begin();
    serial = p_serial;
    network = p_network;
    state = START_SCREEN;
    first_run = 1;
}

void ui_serial::process_start_screen()
{
    serial->write(std::string("plantiniser"));
    if(network->is_wifi_connected())
        serial->write(std::string("wifi connected"));
    else
        serial->write(std::string("no wifi"));
    
    if(network->is_time_synced())
        serial->write(std::string("time synced"));
    else
        serial->write(std::string("no time"));
    
    std::string text = serial->read();
    if(text.length() > 0)
    {
        state = CONFIG_MENU;
    }    
}

void ui_serial::process_config_menu()
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
        serial->write(std::string("end"));
        config_iterator = item_list->begin();
        state = START_SCREEN;
    }
}


void ui_serial::process_config_string_item(StringItem* item)
{
    if(first_run)
    {
        std::string description = std::string(item->get_description());
        serial->write(description);
        serial->write(item->read_data());
        first_run = 0;
    }
    std::string new_value = serial->read();
    if(new_value.length() > 1)
    {
        item->write_data(new_value);
        serial->write(std::string("saved"));
        first_run = 1;
        config_iterator++;
    }    
    else if(new_value.length() > 0)
    {
        serial->write(std::string("skipped"));
        first_run = 1;
        config_iterator++;
    }
}

void ui_serial::process_config_number_item(NumberItem* item)
{
    if(first_run)
    {
        std::string description = std::string(item->get_description());
        serial->write(description);
        int current_value = item->read_data();
        serial->write(toString(current_value));
        first_run = 0;
    }
    std::string new_value = serial->read();
    if(new_value.length() > 1)
    {
        int new_value_int = atoi(new_value.c_str());
        item->write_data(new_value_int);
        config_iterator++;
        serial->write(std::string("saved"));
        first_run = 1;
    }    
    else if(new_value.length() > 0)
    {
        config_iterator++;
        serial->write(std::string("skipped"));
        first_run = 1;
    }
}

void ui_serial::process()
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