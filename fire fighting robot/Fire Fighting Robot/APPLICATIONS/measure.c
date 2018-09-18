#include "main.h"

//全局结构distance用于保存超声波探测到的距离，有三个成员。
Distance distance={0,0,0};

/**
  * @brief 测量左墙的距离
  * @param None
  * @retval None
  * @details trig-->PC.13  echo-->PA.2  TIM5_CH3
  *          毫米级测距，采用限幅滤波与卡尔曼滤波
  */
void Get_Distance_Left(void)
{
  u32 temp=0; 
  int16_t dis=0;

  TIM_Cmd(TIM5,ENABLE);
  GPIO_SetBits(GPIOC,GPIO_Pin_13);
  delay_us(20);
  GPIO_ResetBits(GPIOC,GPIO_Pin_13);
  
  while((!(TIM5CH3_CAPTURE_STA&0X80))&&(SysTick->VAL>100));
  if(TIM5CH3_CAPTURE_STA&0X80)
  {
    temp+=TIM5CH3_CAPTURE_VAL;             //得到总的高电平时间
    dis=temp*170;
    dis /= 10;
    limitfilter(&dis);
    kalmanfilter(&dis);
    distance.left=dis;
    __Sensordata.dis_left=dis;
  }
  TIM_Cmd(TIM5,DISABLE);
  TIM5CH3_CAPTURE_STA=0;                   //开启下一次捕获
}

/**
  * @brief 测量右墙的距离
  * @param None
  * @retval None
  * @details trig-->PC.12  echo-->PB.0  TIM3_CH3
  *          毫米级测距，采用限幅滤波与卡尔曼滤波
  */
void Get_Distance_Right(void)
{
  u32 temp=0; 
  int16_t dis=0;

  TIM_Cmd(TIM3,ENABLE);                    //使能定时器2
  GPIO_SetBits(GPIOC,GPIO_Pin_12);
  delay_us(20);
  GPIO_ResetBits(GPIOC,GPIO_Pin_12);

  while((!(TIM3CH3_CAPTURE_STA&0X80))&&(SysTick->VAL>100));
  if(TIM3CH3_CAPTURE_STA&0X80)
  {
    temp+=TIM3CH3_CAPTURE_VAL;             //得到总的高电平时间
    dis=temp*170;
    dis /= 10;
    limitfilter(&dis);
    kalmanfilter(&dis);
    distance.left=dis;
    __Sensordata.dis_left=dis;
  }
  TIM_Cmd(TIM3,DISABLE);                   //失能定时器2
  TIM3CH3_CAPTURE_STA=0;                   //开启下一次捕获
}

void Get_Distance_Front(void)
{
  u32 temp=0; 
  int16_t dis=0;
  printf("Sysinit is %d\t",SysTick->VAL);
  TIM_Cmd(TIM2,ENABLE);                    //使能定时器2
  GPIO_SetBits(GPIOC,GPIO_Pin_13);
  delay_us(20);
  GPIO_ResetBits(GPIOC,GPIO_Pin_13);

  while((!(TIM2CH2_CAPTURE_STA&0X80))&&(SysTick->VAL>4500));
  if(TIM2CH2_CAPTURE_STA&0X80)
  {
    temp+=TIM2CH2_CAPTURE_VAL;             //得到总的高电平时间
    dis=temp*170;
    dis /= 10;
    limitfilter(&dis);
    kalmanfilter(&dis);
    distance.front=dis;
    __Sensordata.dis_front=dis;
    printf("Syslast is %d\r\n",SysTick->VAL);
  }
  TIM_Cmd(TIM2,DISABLE);                   //失能定时器2
  TIM2CH2_CAPTURE_STA=0;                   //开启下一次捕获
}

