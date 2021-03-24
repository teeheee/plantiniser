#ifndef __TEST__

#include "ui_hal.h"
#include "logging.h"
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <U8g2lib.h>
#include <sstream>
#include <string>

/**
 * @brief this is a fix for the arm gcc toolchain not supporting tostring even if std=c11 is enabled
 */
template<class T>
std::string toString(const T &value) {
    std::ostringstream os;
    os << value;
    return os.str();
}

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
  if(value > 700)
  {
    return 1;
  }
  else if(value > 600)
  {
    return 2;
  }
  else if(value > 500)
  {
    return 3;
  }
  else if(value > 300)
  {
    return 4;
  }
  else if(value > 200)
  {
    return 5;
  }
  else
  {
    LOG(toString(value).c_str());
    return 6;
  }
}

uint8_t decode_encoder(uint8_t state)
{
  const int crement_sequence_length = 5;
  const int increment_sequence[] = {1,2,5,4,1};
  const int decrement_sequence[] = {1,4,5,2,1};
  const int push_sequence_length = 3;
  const int push_sequence[] = {1,3,1};

  static int buffer[crement_sequence_length] = {0};
  static int buffer_index = 0;
  buffer[buffer_index] = state;
  buffer_index = (buffer_index+1)%crement_sequence_length;

  static int buffer2[push_sequence_length] = {0};
  static int buffer2_index = 0;
  buffer2[buffer2_index] = state;
  buffer2_index = (buffer2_index+1)%push_sequence_length;

  int match_increment = 1;
  int match_decrement = 1;
  int match_push = 1;

  for(int i = 0; i < crement_sequence_length; i++)
  {
    if(buffer[i] != increment_sequence[i])
      match_increment = 0;
    if(buffer[i] != decrement_sequence[i])
      match_decrement = 0;
  }

  for(int i = 0; i < push_sequence_length; i++)
  {
    if(buffer2[i] != push_sequence[i])
      match_push = 0;
  }

  if(match_increment)
    return 1;
  else if(match_decrement)
    return 2;
  else if(match_push)
    return 3;
  else
    return 0;
}

void hal_ui_impl::process()
{
  static long taskTime = 0;
  if( millis() < taskTime)
    return;
  taskTime = millis()+2;
  static int last_enc_state = 0;
  int enc_state = encoder_state();
  if(enc_state && last_enc_state != enc_state)
  {
    int event = decode_encoder(enc_state);
    if(event==1)
    {
      last_event = ENC_ROTATE_PLUS;
      LOG("ENC_ROTATE_PLUS");
    }
    else if(event==2)
    {
      last_event = ENC_ROTATE_MINUS;
      LOG("ENC_ROTATE_MINUS");
    }
    else if(event==3)
    {
      last_event = ENC_SHORT_PRESS;
      LOG("ENC_SHORT_PRESS");
    }
    last_enc_state = enc_state;
  }
}

#endif
