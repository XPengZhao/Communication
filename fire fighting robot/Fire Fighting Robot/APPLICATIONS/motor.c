#include "main.h"

/**
  * @brief 调节右电机PWM波
  * @param speed，范围从-100~+100
  * @retval None
  * details -100反转最大速度，0停转，+100正转最大速度
  *         PWM占空比由TIM4配置得出
  */
void MotorRight(int16_t speed)
{
  if(speed>100)  speed=100;
  if(speed<-100) speed=-100;
  __Motordata.motor_right=speed;
  speed=750-speed;
  TIM_SetCompare1(TIM4,speed);
}

/**
  * @brief 调节右电机PWM波
  * @param speed，范围从-100~+100
  * @retval None
  * details -100反转最大速度，0停转，+100正转最大速度
  *         PWM占空比由TIM4配置得出
  */
void MotorLeft(int16_t speed)
{
  if(speed>100)  speed=100;
  if(speed<-100) speed=-100;
  __Motordata.motor_left=speed;
  speed=750+speed;
  TIM_SetCompare2(TIM4,speed);
}
