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
  if(system_25ms%40==0)
    Duty_1000ms();
}

void Duty_25ms(void)
{
  DatatransferTask();
  //Pos_ControlLeft();
  //MotorRight(52);
  //MotorLeft(53);
  // AngleAdjust_L();
  //FindRoom(1);
}

void Duty_50ms(void)
{
  
}

void Duty_100ms(void)
{

}

void Duty_500ms(void)
{
  //AngleAdjust_L();
}

void Duty_1000ms(void)
{
}
