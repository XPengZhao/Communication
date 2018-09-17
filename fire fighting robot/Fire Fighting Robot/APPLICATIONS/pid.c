#include "main.h"

/*
now_dis 本次测量的距离    last_dis 上次测量的距离
now_diff 本次误差信号量    last_diff 上次误差信号量
*/
void Pos_Control(void)
{
    static int16_t now_dis=0,last_dis=STANDARD_DIS,now_diff=0,last_diff=0;
    int16_t ctrl_signal=0;
    Get_Distance_Front();
    now_dis=distance.front;
    now_diff=now_dis-STANDARD_DIS;
    ctrl_signal=kp*now_diff+kd*(last_diff-now_diff);
    if(now_diff>=0)
    {
      MotorRight(100-ctrl_signal);
      MotorLeft(90);
    }
    else
    {
      MotorLeft(90+ctrl_signal);
      MotorRight(100);
    }
    last_diff=now_diff;
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
