#include "main.h"

void taskloop(void)
{
  static u32 system_10ms=0;
  system_10ms++;

  Duty_10ms();
  if(system_10ms%2==0)
    Duty_20ms();
  if(system_10ms%5==0)
    Duty_50ms();
  if(system_10ms%10==0)
    Duty_100ms();
  if(system_10ms%50==0)
    Duty_500ms();
  if(system_10ms%100==0)
    Duty_1000ms();
}

void Duty_10ms(void)
{
  DatatransferTask();
}

void Duty_20ms(void)
{
  Navigate();
}

void Duty_50ms(void)
{
  if(GetCarInfo())
  {
    update_info();
    if(turn_flag)
    {
      FSMflag=TURN_FLAG;
    }
  }
}

void Duty_100ms(void)
{

}

void Duty_500ms(void)
{
  Pos_ControlEncoder();
}

void Duty_1000ms(void)
{
  //Angle_AdjustRight();
}
