#include "main.h"

static u8  fac_us=0;              //us��ʱ������
static u16 fac_ms=0;              //ms��ʱ������


void SysTick_Init()
{
  u32 reload=0;
  SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);   //ѡ���ⲿʱ��  HCLK/8
  fac_us=SystemCoreClock/8000000;                         //ÿ��us��Ҫ��systickʱ����
  fac_ms=(u16)fac_us*1000;                                //ÿ��ms��Ҫ��systickʱ����
  reload=SystemCoreClock/8000*5;                          //reloadֵΪ5ms��Ҫ��systickʱ����
  SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;                //��ʼSYSTICK�ж�
  SysTick->LOAD=reload;                                   //ÿ5ms�ж�һ��
  SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;                 //��ʼSYSTICK����

}

void delay_us(u32 nus)
{
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
}

void delay_ms(u16 nms)
{
  delay_us((u32)(1000*nms));
} 


//ע�͵���λ��stm32f10x_it.c 136�е�SysTick_Handler(),�����ض��塣
void SysTick_Handler(void)
{
  taskloop();
}
