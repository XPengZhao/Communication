#include "main.h"

void Pos_Control(void)
{

}

void Speed_Control(void)
{
  static int16_t speed=100,speed_flag=0;
  if(speed_flag==0)
    speed--;
  else
    speed++;

  if(speed==0)
    speed_flag=1;
  else if(speed==100)
    speed_flag=0;

  LED_TOGGLE();
  MotorRight(speed);
  MotorLeft(speed);
}
