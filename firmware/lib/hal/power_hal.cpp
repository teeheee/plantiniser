#ifndef __TEST__

#include "power_hal.h"
#include <SPI.h>

#define LATCH_ENABLE D4

int pin_states = 0;

void update_states()
{
  digitalWrite(LATCH_ENABLE, LOW);
  SPI.transfer(pin_states);
  digitalWrite(LATCH_ENABLE, HIGH);
}

void hal_power_impl::init()
{
  pin_states = 0;
  SPI.begin();
  SPI.setFrequency(1000);
  pinMode(LATCH_ENABLE, OUTPUT);
  update_states();
}

void hal_power_impl::set(int pin, bool state)
{
  if(state)
  {
      pin_states |= (1<<pin);
  }
  else
  {
      pin_states &= ~(1<<pin);
  }
  update_states();
}

#endif
