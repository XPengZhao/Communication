#include "main.h"

void taskloop(void)
{
  static u32 system_5ms=0;
  system_5ms++;

  Duty_5ms();
  if(system_5ms%2==0)
    Duty_10ms();
  if(system_5ms%4==0)
    Duty_20ms();
  if(system_5ms%10==0)
    Duty_50ms();
  if(system_5ms%20==0)
    Duty_100ms();
  if(system_5ms%200==0)
    Duty_1000ms();
}

 
void Duty_5ms(void)
{
}

void Duty_10ms(void)
{
  DatatransferTask();
}

void Duty_20ms(void)
{
  Pos_ControlRight();
  //MotorLeft(100);
  //MotorRight(50);
}

void Duty_50ms(void)
{

}

void Duty_100ms(void)
{

}

void Duty_1000ms(void)
{
}
