#ifndef __TEST__

#include "ui_hal.h"
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <U8g2lib.h>

#define U8LOG_WIDTH 32
#define U8LOG_HEIGHT 10
uint8_t u8log_buffer[U8LOG_WIDTH*U8LOG_HEIGHT];

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);
U8G2LOG u8g2log;
encoder_event_t last_event = ENC_NO_EVENT;

void hal_ui_impl::init()
{   
    last_event = ENC_NO_EVENT;
    pinMode(D0, INPUT);
    Wire.begin();
    u8g2.begin();
    u8g2.setFont(u8g2_font_tom_thumb_4x6_mf);	// set the font for the terminal window
    u8g2log.begin(u8g2, U8LOG_WIDTH, U8LOG_HEIGHT, u8log_buffer);
    u8g2log.setLineHeightOffset(0);	// set extra space between lines in pixel, this can be negative
    u8g2log.setRedrawMode(0);	
}

void hal_ui_impl::print(const char* text)
{
    u8g2log.print(text);
    Serial.print("LCD: ");
    Serial.println(text);
}

void hal_ui_impl::print(int text)
{
    u8g2log.print(text);
    Serial.print("LCD: ");
    Serial.println(text);
}

void hal_ui_impl::print_at(int line, const char* text)
{
    u8g2.setFont(u8g2_font_ncenB08_tf);
    u8g2.drawStr(0, 10,"penisrofelcopter88");
    u8g2.drawStr(0, 20,"hello world");
    u8g2.drawStr(0, 30,"hello world");
    u8g2.drawStr(0, 40,"hello world");
    u8g2.nextPage();
    Serial.print("LCD: ");
    Serial.println(text);
}

void hal_ui_impl::clear()
{
    u8g2log.print("\f");
}

encoder_event_t hal_ui_impl::get_event()
{
    encoder_event_t tmp = last_event;
    last_event = ENC_NO_EVENT;
    return tmp;
}

void hal_ui_impl::process()
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

#endif
