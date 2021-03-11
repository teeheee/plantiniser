#ifndef _MOCK_UI_HAL_
#define _MOCK_UI_HAL_

#include "gmock/gmock.h"
#include "ui_hal.h"

class mock_hal_ui : public hal_ui{
public:
    void init(){};
    void print(const char* text){};
    void print(int text){};
    void print_at(int line, const char* text){};
    void clear(){};
    encoder_event_t get_event(){return ENC_NO_EVENT;};
    void process(){};
};

#endif