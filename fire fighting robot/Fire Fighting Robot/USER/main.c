#include "main.h"

int main(void)
{
  LED_Init();
	SysTick_Init();
  while(1)
  {
    delay_ms(1000);
    LED_TOGGLE();

  }
}
