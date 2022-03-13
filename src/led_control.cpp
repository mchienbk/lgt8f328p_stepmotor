/**
 * @file  led_control.cpp
 * @date  14.03.2022
 * @author Daze
 */
#include <header.h>

void Turn_On_LED()
{
  digitalWrite(LED_BUILTIN, HIGH);
}

void Turn_Off_LED()
{
  digitalWrite(LED_BUILTIN, LOW);
}

void Led_blink(int times, int period)
{
  int i = 0;
  for (i = 0; i < times; i++)
  {
    Turn_On_LED();
    delay(period);
    Turn_Off_LED();
    delay(period);
  }
}
