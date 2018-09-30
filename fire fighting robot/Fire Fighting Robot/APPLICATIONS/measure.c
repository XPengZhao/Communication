#include "main.h"

//ȫ�ֽṹdistance���ڱ��泬����̽�⵽�ľ��룬��������Ա��
Distance distance={0,0,0};

/**
  * @brief ������ǽ�ľ���
  * @param None
  * @retval None
  * @details trig-->PC.13  echo-->PA.2  TIM5_CH3
  *          ���׼���࣬�����޷��˲��뿨�����˲�
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
    temp+=TIM5CH3_CAPTURE_VAL;             //�õ��ܵĸߵ�ƽʱ��
    dis=temp*170;
    dis /= 10;
 //   limitfilter(&dis);
 //   kalmanfilter2(&dis);
    distance.left=dis;
    __Sensordata.dis_left=dis;
  }
  TIM_Cmd(TIM5,DISABLE);
  TIM5CH3_CAPTURE_STA=0;                   //������һ�β���
}

/**
  * @brief ������ǽ�ľ���
  * @param None
  * @retval None
  * @details trig-->PC.12  echo-->PB.0  TIM3_CH3
  *          ���׼���࣬�����޷��˲��뿨�����˲�
  */
void Get_Distance_Right(void)
{
  u32 temp=0; 
  u16 dis=0;

  TIM_Cmd(TIM3,ENABLE);                    //ʹ�ܶ�ʱ��2
  GPIO_SetBits(GPIOC,GPIO_Pin_12);
  delay_us(20);
  GPIO_ResetBits(GPIOC,GPIO_Pin_12);

  while((!(TIM3CH3_CAPTURE_STA&0X80))&&(SysTick->VAL>100));
  if(TIM3CH3_CAPTURE_STA&0X80)
  {
    temp+=TIM3CH3_CAPTURE_VAL;             //�õ��ܵĸߵ�ƽʱ��
    dis=temp*170;
    dis /= 10;
//    limitfilter(&dis);
 //   kalmanfilter1(&dis);
    distance.left=dis;
    __Sensordata.dis_left=dis;
  }
  TIM_Cmd(TIM3,DISABLE);                   //ʧ�ܶ�ʱ��2
  TIM3CH3_CAPTURE_STA=0;                   //������һ�β���
}

void Get_Distance_Front(void)
{
  u16 dis=0,temp=0;

	TIM2CH2_CAPTURE_STA=0;
  TIM_Cmd(TIM2,ENABLE);                     //ʹ�ܶ�ʱ��2
  GPIO_SetBits(GPIOC,GPIO_Pin_13);
  delay_us(20);
  GPIO_ResetBits(GPIOC,GPIO_Pin_13);
  while((!(TIM2CH2_CAPTURE_STA&0X80))&&(SysTick->VAL>4500));
  if(TIM2CH2_CAPTURE_STA&0X80)
  {
    LED_TOGGLE();
    temp = TIM2CH2_CAPTURE_VAL;             //�õ��ܵĸߵ�ƽʱ��
    dis = temp * 170 / 1000;
    __Sensordata.dis_left=(int)dis;
    limitfilter(&dis);
    kalmanfilter(&dis);
    __Sensordata.dis_right=(int)dis;
    dis/=10;
    distance.front=dis;
    __Sensordata.dis_front=(int)dis;
  }
  else
  {
    TIM_OC2PolarityConfig(TIM2,TIM_ICPolarity_Rising);       //����Ϊ�����ز���
  }
  TIM_Cmd(TIM2,DISABLE);                   //ʧ�ܶ�ʱ��2
  TIM2CH2_CAPTURE_STA=0;                   //������һ�β���
}

