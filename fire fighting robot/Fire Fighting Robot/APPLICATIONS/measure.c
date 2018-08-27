#include "main.h"


Distance distance={0,0,0};

void Get_Distance_Left(void)
{
  u32 temp=0; 
  int dis=0;

  GPIO_SetBits(GPIOC,GPIO_Pin_13);     //PE.0-->trig 拉低电平 
  delay_us(20);
  GPIO_ResetBits(GPIOC,GPIO_Pin_13);	//PE.0-->trig 拉高电平

  while(!TIM5CH3_CAPTURE_STA&0X80);        //成功捕获到了一次高电平
  temp=TIM5CH3_CAPTURE_STA&0X3F;
  temp*=5000;                       //溢出时间总和
  temp+=TIM5CH3_CAPTURE_VAL;        //得到总的高电平时间
  dis=temp*170;
  dis /= 100;

  TIM5CH3_CAPTURE_STA=0;            //开启下一次捕获


  distance.left=dis;
}

void Get_Distance_Right(void)
{
  u32 temp=0; 
  int dis=0;

  GPIO_SetBits(GPIOC,GPIO_Pin_12);     //PE.0-->trig 拉低电平 
  delay_us(20);
  GPIO_ResetBits(GPIOC,GPIO_Pin_12);	//PE.0-->trig 拉高电平

  while(!TIM3CH3_CAPTURE_STA&0X80);        //成功捕获到了一次高电平
  temp=TIM3CH3_CAPTURE_STA&0X3F;
  temp*=5000;                       //溢出时间总和
  temp+=TIM3CH3_CAPTURE_VAL;        //得到总的高电平时间
  dis=temp*170;
  dis /= 100;

  TIM3CH3_CAPTURE_STA=0;            //开启下一次捕获


    distance.right=dis;
}

void Get_Distance_Front(void)
{
  u32 temp=0; 
  int dis=0;

  GPIO_SetBits(GPIOC,GPIO_Pin_11);     //PE.0-->trig 拉低电平 
  delay_us(20);
  GPIO_ResetBits(GPIOC,GPIO_Pin_11);	//PE.0-->trig 拉高电平

  while(!TIM2CH2_CAPTURE_STA&0X80);        //成功捕获到了一次高电平
  temp=TIM2CH2_CAPTURE_STA&0X3F;
  temp*=5000;                       //溢出时间总和
  temp+=TIM2CH2_CAPTURE_VAL;        //得到总的高电平时间
  dis=temp*170;
  dis /= 100;

  TIM2CH2_CAPTURE_STA=0;            //开启下一次捕获


  distance.front=dis;
}
