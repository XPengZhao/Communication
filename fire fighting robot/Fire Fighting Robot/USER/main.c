#include "main.h"

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  Driver_Init();
	while(1)
	{
		delay_ms(50);
		printf("aaaaaa\r\n");
	}
}
