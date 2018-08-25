#include "stm32f10x.h"
#include "led.h"
void Delay(u32 count)
{
  u32 i=0;
  for(;i<count;i++);
}

int main(void)
{
  LED_Init();
  while(1)
  {
    Delay(3000000);
    LED_TOGGLE();
    Delay(3000000);
  }
}
