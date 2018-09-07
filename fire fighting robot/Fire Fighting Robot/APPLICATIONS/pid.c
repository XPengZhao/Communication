#include "main.h"

void Pos_Control(void)
{

}

void Speed_Control(void)
{
  static int16_t speed_right=700,speed_left=800,left_flag=1,right_flag=0;
  if(right_flag==0)
    speed_right++;
  else
    speed_right--;
  
  if(speed_right==750)
    right_flag=1;
  else if(speed_right==700)
    right_flag=0;

  if(left_flag==1)
    speed_left--;
  else
    speed_left++;
  
  if(speed_left==750)
    left_flag=0;
  else if(speed_left==800)
    left_flag=1;
  LED_TOGGLE();
  MotorRight(TIM4,speed_right);
  MotorLeft(TIM4,speed_left);
  ANO_DT_Send_MotoPWM(speed_right,speed_left,0,0,0,0,0,0);
}
