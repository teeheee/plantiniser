#ifndef _UI_SERIAL_H_
#define _UI_SERIAL_H_

#include "serial_hal.h"
#include "config.h"
#include "network_manager.h"

class ui_serial{
private:
    hal_serial* serial;
    ConfigManage* config;
    network_manager* network;
    enum state_type{
        START_SCREEN,
        CONFIG_MENU,
    };
    state_type state;
    std::list<ConfigBaseItem*>* item_list;
    std::list<ConfigBaseItem*>::iterator config_iterator;
    int first_run;

    void process_start_screen();
    void process_config_menu();
    void process_config_string_item(StringItem* item);
    void process_config_number_item(NumberItem* item);
public:
    ui_serial(hal_serial* serial, ConfigManage* p_config, network_manager* p_network);
    void process();
};

#endif
