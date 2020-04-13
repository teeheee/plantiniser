#ifdef _TEST_

#include <ESP8266WiFi.h>

#include "ui_hal.h"
#include "eeprom_hal.h"

hal_ui_impl ui;
hal_eeprom_impl eeprom;

void setup() 
{
  Serial.begin(115200);
  Serial.println("start");
  ui.init();
  ui.print("start");
  Serial.println("ui init");
  eeprom.init();
  Serial.println("eeprom init");
  eeprom.update();
  uint8_t x = 42;
  //eeprom.put(&x, 1, 0);
  eeprom.update();
  uint8_t y = 3;
  eeprom.get(&y, 1, 0);
  Serial.println(y);
}

void loop() 
{
    static uint8_t change = 0;
    static uint8_t count = 42;
    ui.process();
    if(change)
    {
        Serial.println("change");
        change = 0;
        ui.clear();
        ui.print("hello world\n");
        ui.print(count);
    }
    switch(ui.get_event())
    {
        case ENC_ROTATE_PLUS:
            count++;
            change = 1;
            break;
        case ENC_ROTATE_MINUS:
            count--;
            change = 1;
            break;
        case ENC_SHORT_PRESS:
            count = 0;
            change = 1;
            break;
        case ENC_LONG_PRESS:
            count = 100;
            change = 1;
            break;
        default:
            break;
    }
}

#endif
