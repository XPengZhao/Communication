#include "main.h"

void taskloop(void)
{
  static u32 system_25ms=0;
  system_25ms++;

  Duty_25ms();
  if(system_25ms%2==0)
    Duty_50ms();
  if(system_25ms%4==0)
    Duty_100ms();
  if(system_25ms%20==0)
    Duty_500ms();
}

void Duty_25ms(void)
{
  //MotorLeft(100);
  //MotorRight(100);
  delay_ms(1000);
  turn_right_withdelay();
  delay_ms(1000);
  //turn_right_withdelay();
}

void Duty_50ms(void)
{

}

void Duty_100ms(void)
{

}

void Duty_500ms(void)
{
}
