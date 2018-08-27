#include "main.h"

void Driver_Init(void)
{
  LED_Init();
  SysTick_Init();
  PWM_Init();
}
