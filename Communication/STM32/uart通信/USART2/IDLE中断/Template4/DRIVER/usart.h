#ifndef USART_H
#define USART_H
#include "stm32f10x.h"

#define USART1_DMA_RX_LEN 8
void Usart1_Init(u32 baudrate);

#endif
