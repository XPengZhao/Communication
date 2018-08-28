#include "main.h"

void Driver_Init(void)
{
  Usart1_Init(115200);
  LED_Init();
  PWM_Init();
  Wave_Init();
	SysTick_Init();
}
