#include "stm32f10x.h"
#include "usart.h"
int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Usart2_Init(115200);
    while(1);
}
