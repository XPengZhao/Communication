#include "main.h"

static u8  fac_us=0;              //us��ʱ������

void SysTick_Init()
{
  u32 reload=0;
  fac_us=SystemCoreClock/8000000;                          //ÿ��us��Ҫ��systickʱ����
  reload=SystemCoreClock/8000*5;                           //reloadֵΪ5ms��Ҫ��systickʱ����
  SysTick->LOAD  = (reload & SysTick_LOAD_RELOAD_Msk) - 1; //ÿ5ms�ж�һ��
  NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);
  SysTick->VAL   = 0;
  SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);    //ѡ���ⲿʱ��  HCLK/8
  SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;                 //��ʼSYSTICK�ж�
  SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;                  //��ʼSYSTICK����

#if DRIVER_CHECK
printf("SysTick init successful\r\n");
#endif
}

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

void delay_ms(u16 nms)
{
  delay_us((u32)(1000*nms));
} 


//ע�͵���λ��stm32f10x_it.c 136�е�SysTick_Handler(),�����ض��塣
void SysTick_Handler(void)
{

#if IRQONCE_CHECK
  static u8 systickIRQ_flag=1;
  if(systickIRQ_flag)
  {
    printf("SysTick_Handler execute successful!\r\n");
    systickIRQ_flag=0;
  }
#elif IRQDUPLICATE_CHECK
  printf("SysTick_Handler execute successful!\r\n");
#endif

//  switch(FSMflag)
//  {
//    case SENSOROFFSET_FLAG: SenserOffsetInit();break;
//    case TASKLOOP_FLAG:     taskloop();break;
//    case START_FLAG:        StartSearch();break;

//  }
  taskloop();
}
