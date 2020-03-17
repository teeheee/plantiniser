#include "display.h"
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <U8g2lib.h>

#define U8LOG_WIDTH 32
#define U8LOG_HEIGHT 10
uint8_t u8log_buffer[U8LOG_WIDTH*U8LOG_HEIGHT];

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);
U8G2LOG u8g2log;

void display_init()
{   
    Wire.begin();
    u8g2.begin();
    u8g2.setFont(u8g2_font_tom_thumb_4x6_mf);	// set the font for the terminal window
    u8g2log.begin(u8g2, U8LOG_WIDTH, U8LOG_HEIGHT, u8log_buffer);
    u8g2log.setLineHeightOffset(0);	// set extra space between lines in pixel, this can be negative
    u8g2log.setRedrawMode(0);	
}

void display_print(const char* text)
{
    u8g2log.print(text);
    Serial.print("LCD: ");
    Serial.println(text);
}

void display_print(int text)
{
    u8g2log.print(text);
    Serial.print("LCD: ");
    Serial.println(text);
}

void display_print_at(int line, const char* text)
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

void display_clear()
{
    u8g2log.print("\f");
}
