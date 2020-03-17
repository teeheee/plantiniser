#include "encoder.h"
#include <ESP8266WiFi.h>

encoder_event_t last_event = ENC_NO_EVENT;

void encoder_init()
{
    last_event = ENC_NO_EVENT;
    pinMode(D0, INPUT);
}

encoder_event_t encoder_get_event()
{
    encoder_event_t tmp = last_event;
    last_event = ENC_NO_EVENT;
    return tmp;
}

void encoder_process()
{
  static int state_plus = 0;
  static int state_minus = 0;
  uint16_t value = analogRead(A0);

  if(value < 320 && (state_plus == 0))
  {
    state_plus++;
  }
  else if(value < 400 && (state_plus == 1))
  {
    state_plus++;
  }
  else if(value < 1000 && (state_plus == 2))
  {
    state_plus++;
  }

  if(value >= 1000) //no step
  {
    if(state_plus == 3)
    {
      last_event = ENC_ROTATE_PLUS;
    }
    if(state_minus == 3)
    {
       last_event = ENC_ROTATE_MINUS;
    }
    state_plus = 0;
    state_minus = 0;
  }
}