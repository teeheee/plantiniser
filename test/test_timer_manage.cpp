#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "config.h"
#include "timer_manager.h"

#include "mock_time_hal.h"
#include "mock_power_hal.h"
#include "mock_eeprom_hal.h"

TEST(timer_manage, time_is_invalid_on_start)
{
  mock_hal_power power;
  mock_hal_time time;
  mock_hal_eeprom eeprom;
  ConfigManage config(&eeprom);
  TimerManager tm(&config, &power, &time);
}

