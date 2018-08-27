#include "main.h"

static u8  fac_us=0;              //us延时倍乘数
static u16 fac_ms=0;              //ms延时倍乘数


void SysTick_Init()
{
  u32 reload=0;
  SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);   //选择外部时钟  HCLK/8
  fac_us=SystemCoreClock/8000000;                         //每个us需要的systick时钟数
  fac_ms=(u16)fac_us*1000;                                //每个ms需要的systick时钟数
  reload=SystemCoreClock/8000*5;                          //reload值为5ms需要的systick时钟数
  SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;                //开始SYSTICK中断
  SysTick->LOAD=reload;                                   //每5ms中断一次
  SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;                 //开始SYSTICK计数

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


//注释掉了位于stm32f10x_it.c 136行的SysTick_Handler(),避免重定义。
void SysTick_Handler(void)
{
  taskloop();
}
