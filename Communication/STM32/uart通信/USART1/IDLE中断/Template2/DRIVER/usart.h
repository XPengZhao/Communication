#ifndef USART_H
#define USART_H
#include "stm32f10x.h"
#include "stdio.h"

#define USART1_DMA_RX_LEN 256
#define USART1_DMA_TX_LEN 256
void Usart1_Init(u32 baudrate);
void Usart1_Send(unsigned char *DataToSend,u16 data_num);

#endif
