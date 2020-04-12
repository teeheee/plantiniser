#ifndef _UI_HAL_H_
#define _UI_HAL_H_

typedef enum{
    ENC_NO_EVENT,
    ENC_ROTATE_PLUS,
    ENC_ROTATE_MINUS,
    ENC_SHORT_PRESS,
    ENC_LONG_PRESS,
} encoder_event_t;

class hal_ui {
public:
    virtual void init() = 0;
    virtual void print(const char* text) = 0;
    virtual void print(int text) = 0;
    virtual void print_at(int line, const char* text) = 0;
    virtual void clear() = 0;
    virtual encoder_event_t get_event() = 0;
    virtual void process() = 0;
};

class hal_ui_impl : public hal_ui{
    void init();
    void print(const char* text);
    void print(int text);
    void print_at(int line, const char* text);
    void clear();
    encoder_event_t get_event();
    void process();
};

#endif
