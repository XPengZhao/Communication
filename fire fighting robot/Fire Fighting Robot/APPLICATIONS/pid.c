#include "main.h"

//  float P,I,D,FF,MaxError
static PIDParams pos_pidparam={0.4,0,0,0,50};

//  float Error,Target;
static PIDState  pos_pidstate={0,200};

/*
now_dis 本次测量的距离    last_dis 上次测量的距离
now_diff 本次误差信号量    last_diff 上次误差信号量
*/
void Pos_Control(void)
{
    float e=0,de=0,ctrl_signal=0;
    Get_Distance_Front();
    e=pos_pidstate.Target-distance.front;
    de=(e-pos_pidstate.Error);
    pos_pidstate.Error=e;
    ctrl_signal=pos_pidparam.P*(e+pos_pidparam.D*de);
    if(ctrl_signal>pos_pidparam.MaxError)
    {
      ctrl_signal=pos_pidparam.MaxError;
    }
    else if(ctrl_signal<-pos_pidparam.MaxError)
    {
      ctrl_signal=-pos_pidparam.MaxError;
    }
    if(e>-15&&e<15)
    {
      MotorRight(100);
      MotorLeft(80);
    }
    else if(e>15)
    {
      MotorLeft(80-ctrl_signal);
      MotorRight(100);
    }
    else
    {
      MotorLeft(100);
      MotorRight(100+ctrl_signal);
    }

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
