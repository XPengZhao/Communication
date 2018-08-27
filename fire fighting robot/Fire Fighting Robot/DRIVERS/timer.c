#include "main.h"

/**
  * @brief ���Ƶ��̵����PWM������
  * @param None
  * @retval None
  * @details 1.�ҵ����PD.12��������PD.13(��PB.5,PB.6��ӳ��)
  *          2.ͨ��TIM4_CH1��TIM4_CH2���PWM��,PWM��Ƶ��50Hz
  *          3.ռ�ձ� speed/ARR_PWM���������� speed/10000
  *          4.ͨ��MotorRight(TIM4,u16 speed);�� MotorLeft(TIM4,u16 speed);
  */
void PWM_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;  
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;  
    TIM_OCInitTypeDef  TIM_OCInitStructure;  

    //�˿���ӳ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_AFIO,ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

    //���ø�����Ϊ�����������,���TIM4 CH1(PD.12�������)��TIM4 CH2(PD.13�������)��PWM���岨��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;    //TIM4_CH1(PD.12�������)��TIM4_CH2(PD.13�������)  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;             //�����������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);  
      
    TIM_TimeBaseStructure.TIM_Period = ARR_PWM;                 //��������һ�������¼�װ�����Զ���װ�ؼĴ���
    TIM_TimeBaseStructure.TIM_Prescaler =PSC_PWM;               //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;                //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM���ϼ���ģʽ
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);             //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ  
    
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;           //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1  
    TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable; //�Ƚ����ʹ��  
    TIM_OCInitStructure.TIM_Pulse = 0;                          //���ô�װ�벶��ȽϼĴ���������ֵ  
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;   //�������:TIM����Ƚϼ��Ը�  

    TIM_OC1Init(TIM4, &TIM_OCInitStructure);                    //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx   
    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);           //CH1Ԥװ��ʹ��
    TIM_OC2Init(TIM4, &TIM_OCInitStructure);                    //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);           //CH2Ԥװ��ʹ��  

    TIM_ARRPreloadConfig(TIM4, ENABLE);                         //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���  
    TIM_CtrlPWMOutputs(TIM4,ENABLE);                            //MOE �����ʹ��
    TIM_Cmd(TIM4, ENABLE);

}
