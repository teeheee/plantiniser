#include "timer_manager.h"
#include "logging.h"


TimerManager::TimerManager(ConfigManage* p_config, hal_power* p_power, hal_time* p_rtc)
{
    config = p_config;
    power = p_power;
    rtc = p_rtc;
    tick_flag = true;
    power->set(0,false);
    last_minute = rtc->get_minutes();
}

void TimerManager::minute_tick(int minute, int hour)
{
  if(minute == config->get_water_valve_on_minute() 
  && hour == config->get_water_valve_on_hour())
  {
    pump_timeout = config->get_water_valve_on_duration();
  }
  if(pump_timeout)
  {
    power->set(0,true);
    pump_timeout--;
  }
  else
  {
    power->set(0,false);
  }
}

void TimerManager::process()
{
    if(rtc->is_valid())
    {
        int current_minute = rtc->get_minutes();
        if(last_minute != current_minute)
        {
          minute_tick(current_minute, rtc->get_hours());
          last_minute = current_minute;
          tick_flag = true;
          LOG("TM: minute tick");
        }
    }
}

std::string TimerManager::get_current_time()
{
  return rtc->get_formated();
}

bool TimerManager::get_tick()
{
  if(tick_flag)
  {
    tick_flag = false;
    return true;
  }
  else
  {
    return false;
  }
}