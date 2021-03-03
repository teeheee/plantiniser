#ifndef _UI_LCD_H_
#define _UI_LCD_H_

#include "ui_hal.h"
#include "config.h"
#include "network_manager.h"

class ui_lcd{
private:
    hal_ui* ui;
    ConfigManage* config;
    network_manager* network;
    enum state_type{
        START_SCREEN,
        CONFIG_MENU,
    };
    state_type state;
    std::list<ConfigBaseItem*>* item_list;
    std::list<ConfigBaseItem*>::iterator config_iterator;

    void process_start_screen();
    
    int fist_run;
    int change;

    int current_number_value;

    unsigned int position;
    unsigned int character_index;
    std::string current_string_value;

    void process_config_menu();
    int get_valid_char_index(char to_search);
    void process_config_string_item(StringItem* item);
    void process_config_number_item(NumberItem* item);
public:
    ui_lcd(hal_ui* p_ui, ConfigManage* p_config, network_manager* p_network);
    void process();
};

#endif
