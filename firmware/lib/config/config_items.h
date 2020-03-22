#ifndef _CONFIG_ITEMS_
#define _CONFIG_ITEMS_

#include "config_base_item.h"

class StringItem : public ConfigBaseItem{
public:
    StringItem(int a_datasize, const char* a_description) 
    : ConfigBaseItem(a_datasize, a_description)
    {

    }
    void* read_data(){
    }
    void write_data(void* pointer){
    }
    void manage_config(){

    }
};


#endif