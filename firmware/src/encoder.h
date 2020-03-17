#ifndef _ENCODER_H_
#define _ENCODER_H_

#include <stdint.h>

typedef enum{
    ENC_NO_EVENT,
    ENC_ROTATE_PLUS,
    ENC_ROTATE_MINUS,
    ENC_SHORT_PRESS,
    ENC_LONG_PRESS,
} encoder_event_t;

void encoder_init();
encoder_event_t encoder_get_event();
void encoder_process();

#endif
