#include "main.h"

static u8  fac_us=0;              //us��ʱ������

/**
  * @brief ��ʼ��SysTick��શ�ʱ��
  * @param None
  * @retval None
  * @details ʹ��SysTick��ʱ���жϣ�ÿ25ms�ж�һ�Σ��ж����ȼ����
  *          SysTick��ʱ��1us����9��
  */
void SysTick_Init(void)
{
  u32 reload=0;
  fac_us=SystemCoreClock/8000000;                          //ÿ��us��Ҫ��systickʱ����=9
  reload=SystemCoreClock/8000*25;                          //reloadֵΪ25ms��Ҫ��systickʱ����=225000
  SysTick->LOAD  = (reload & SysTick_LOAD_RELOAD_Msk) - 1; //ÿ25ms�ж�һ��
  NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);
  SysTick->VAL   = 0;
  SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);    //ѡ���ⲿʱ��  HCLK/8
  SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;                 //��ʼSYSTICK�ж�
  SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;                  //��ʼSYSTICK����
}

/**
  * @brief ΢����ʱ����
  * @param ������ʱ΢����
  * @retval None
  * @details 1����ʱ�ڼ��ڱ������ж�
  *          2��������ʱ�����΢����Ϊ(2^32)/9=477218588us
  *          3���ڱ��ڼ��жϱ����𣬽����ڱκ���Щ�жϽ���ִ��
  */
void delay_us(u32 nus)
{
  NVIC_SETPRIMASK();
  u32 tick=nus*fac_us;
  u32 time_old,time_now,time_cnt=0;
  u32 reload=SysTick->LOAD;
  time_old=SysTick->VAL;

  while(1)
  {
    time_now=SysTick->VAL;
    if(time_now<=time_old)
      time_cnt+=time_old-time_now;
    else
      time_cnt+=reload-time_now+time_old;
    time_old=time_now;
    if(time_cnt>=tick)
      break;
  }
  NVIC_RESETPRIMASK();
}

/**
  * @brief ������ʱ����
  * @param ������ʱ������
  * @retval None
  * @details 1����ʱ�ڼ��ڱ������ж�
  *          2��������ʱ����������Ϊ 2^16-1=65535ms
  *          3���ڱ��ڼ��жϱ����𣬽����ڱκ���Щ�жϽ���ִ��
  */
void delay_ms(u16 nms)
{
  delay_us((u32)(1000*nms));
}


//ע�͵���λ��stm32f10x_it.c 136�е�SysTick_Handler(),�����ض��塣
void SysTick_Handler(void)
{
  taskloop();
}
