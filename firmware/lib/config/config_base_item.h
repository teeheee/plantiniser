#ifndef _CONFIG_BASE_ITEM_
#define _CONFIG_BASE_ITEM_

#include <stdint.h>

class ConfigBaseItem{
public:
    ConfigBaseItem(int a_datasize, const char* a_description);
    ~ConfigBaseItem(){};
    bool is_data_valid();
    const char*  get_description();
    virtual void* read_data() = 0;
    virtual void write_data(void* pointer) = 0;
    virtual void manage_config() = 0;
    uint8_t calc_checksum(uint8_t* data, int datasize);
    uint8_t* data_pointer = 0;
    int data_size = 0;
    bool valid_data = false;
    const char* description;
};

#endif