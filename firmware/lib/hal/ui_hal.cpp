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
    u8g2log.setRedrawMode(1);	
}

void hal_ui_impl::print(const char* text)
{
    u8g2log.print(text);
}

void hal_ui_impl::print(int text)
{
    u8g2log.print(text);
}

void hal_ui_impl::print_at(int line, const char* text)
{
    u8g2.setFont(u8g2_font_ncenB08_tf);
    u8g2.drawStr(0, 10*line, text);
    u8g2.nextPage();
}

void hal_ui_impl::clear()
{
    u8g2.clear();
    u8g2log.print("\f");
}

encoder_event_t hal_ui_impl::get_event()
{
    encoder_event_t tmp = last_event;
    last_event = ENC_NO_EVENT;
    return tmp;
}

int encoder_state()
{
  uint16_t value = analogRead(A0);
  if(value < 320)
  {
    return 1;
  }
  else if(value < 400)
  {
    return 2;
  }
  else if(value < 1000)
  {
    return 3;
  }
  else
  {
    return 0;
  }
}

void hal_ui_impl::process()
{
  static int rot = 0;
  static int last_enc_state = 0;
  static int was_pressed = 0;
  if(! digitalRead(D0) && was_pressed == 0)
  {
    last_event = ENC_SHORT_PRESS;
    was_pressed = 1;
  }
  else if(digitalRead(D0) && was_pressed == 1)
  {
    was_pressed = 0;
  }
  
  int enc_state = encoder_state();
  if(enc_state && last_enc_state != enc_state)
  {
    /*Serial.print(" ");
    Serial.print(enc_state);
    Serial.print(" ");
    Serial.println(rot);*/
    if(enc_state == 2 && rot == 0)
    {
      rot++;
    }
    else if(enc_state == 3 && rot == 0)
    {
      rot--;
    }
    else if(enc_state == 1 && (rot == 1 || rot == -1))
    {
      rot += rot;
    }
    else if(enc_state == 3 && rot == 2)
    {
      //Serial.println("ENC_ROTATE_PLUS");
      last_event = ENC_ROTATE_PLUS;
      rot = 0;
    }
    else if(enc_state == 2 && rot == -2)
    {
      //Serial.println("ENC_ROTATE_MINUS");
      last_event = ENC_ROTATE_MINUS;
      rot = 0;
    }
    else
    {
      rot = 0;
    }
    last_enc_state = enc_state;
  }
}

#endif
