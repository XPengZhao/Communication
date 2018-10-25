#include "main.h"

/**
  * @brief �����ҵ��PWM��
  * @param speed����Χ��-100~+100
  * @retval None
  * details -100��ת����ٶȣ�0ͣת��+100��ת����ٶ�
  *         PWMռ�ձ���TIM4���õó�
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
  * @brief �����ҵ��PWM��
  * @param speed����Χ��-100~+100
  * @retval None
  * details -100��ת����ٶȣ�0ͣת��+100��ת����ٶ�
  *         PWMռ�ձ���TIM4���õó�
  */
void MotorLeft(int16_t speed)
{
  if(speed>100)  speed=100;
  if(speed<-100) speed=-100;
  __Motordata.motor_left=speed;
  speed=750+speed;
  TIM_SetCompare2(TIM4,speed);
}

void FanMotor_Init()
{
  GPIO_InitTypeDef GPIO_InitStrue;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
  GPIO_InitStrue.GPIO_Mode=GPIO_Mode_Out_PP;
  GPIO_InitStrue.GPIO_Pin=GPIO_Pin_15;
  GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOD,&GPIO_InitStrue);
}

void FanMotor_Open()
{
  GPIO_SetBits(GPIOD,GPIO_Pin_15);
}

void FanMotor_Close()
{
  GPIO_ResetBits(GPIOD,GPIO_Pin_15);
}
