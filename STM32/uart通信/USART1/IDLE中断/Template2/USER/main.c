#include "stm32f10x.h"
#include "usart.h"

int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Usart1_Init(115200);
	  USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);
    while(1);
}
