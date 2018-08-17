#include "stm32f10x_conf.h"
#include "usart.h"

/*--------------------------USART1ȫ�ֱ���-----------------------------------*/
u8 USART1_RXBUFF[USART1_DMA_RX_LEN];
/*--------------------------------------------------------------------------*/

/**
  * @brief ����1��ʼ��
  * @param BaudRate
  * @retval None
  * @details BaudRate 115200
  *          TX PA.9   RX PA.10
  *          USART1_RX-->DMA1_CH5    USART1_TX-->DMA1_CH4
  *          �ֳ�8λ    һλֹͣλ    ����żУ��λ
  *          �ж��ȡ������ȼ���1��1
  *          ʹ��DMA����,ʹ��IDLE�жϣ�������һ֡���ݺ��һ���ֽڿ��к�����ж�
  *          ʹ��DMA����
  */
void Usart1_Init(u32 baudrate)
{
  GPIO_InitTypeDef GPIO_InitStrue;
  USART_InitTypeDef USART_InitStrue;
  NVIC_InitTypeDef NVIC_InitStrue;
  DMA_InitTypeDef DMA_InitStructure;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
  
  GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;
  GPIO_InitStrue.GPIO_Pin=GPIO_Pin_9;
  GPIO_InitStrue.GPIO_Speed=GPIO_Speed_10MHz;
  GPIO_Init(GPIOA,&GPIO_InitStrue);
  
  GPIO_InitStrue.GPIO_Mode=GPIO_Mode_IN_FLOATING;
  GPIO_InitStrue.GPIO_Pin=GPIO_Pin_10;
  GPIO_InitStrue.GPIO_Speed=GPIO_Speed_10MHz;
  GPIO_Init(GPIOA,&GPIO_InitStrue);
  
  USART_InitStrue.USART_BaudRate=baudrate;
  USART_InitStrue.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
  USART_InitStrue.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;
  USART_InitStrue.USART_Parity=USART_Parity_No;
  USART_InitStrue.USART_StopBits=USART_StopBits_1;
  USART_InitStrue.USART_WordLength=USART_WordLength_8b;
  
  USART_Init(USART1,&USART_InitStrue);
  USART_Cmd(USART1,ENABLE);//ʹ�ܴ���1
  
  USART_ITConfig(USART1,USART_IT_IDLE,ENABLE);//���������ж�
  
  NVIC_InitStrue.NVIC_IRQChannel=USART1_IRQn;
  NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;
  NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=1;
  NVIC_InitStrue.NVIC_IRQChannelSubPriority=1;
  NVIC_Init(&NVIC_InitStrue);
  
  DMA_DeInit(DMA1_Channel5);
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART1->DR;  //DMA����ADC����ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&USART1_RXBUFF;  //DMA�ڴ����ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  //���ݴ��䷽�򣬴��ڴ��ȡ���͵�����
	DMA_InitStructure.DMA_BufferSize = USART1_DMA_RX_LEN;  //DMAͨ����DMA����Ĵ�С
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //�����ַ�Ĵ�������
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //�ڴ��ַ�Ĵ�������
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  //���ݿ��Ϊ8λ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; //���ݿ��Ϊ8λ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  //��������������ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; //DMAͨ�� xӵ�������ȼ� 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //DMAͨ��xû������Ϊ�ڴ浽�ڴ洫��
	DMA_Init(DMA1_Channel5, &DMA_InitStructure);  //����DMA_InitStruct��ָ���Ĳ�����ʼ��DMA��ͨ��USART1_Tx_DMA_Channel����ʶ�ļĴ���
	DMA_Cmd(DMA1_Channel5, ENABLE);

  DMA_DeInit(DMA1_Channel4);
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;  //���ݴ��䷽�򣬴��ڴ��ȡ���͵�����
  DMA_Init(DMA1_Channel4, &DMA_InitStructure);
}

void USART1_IRQHandler(void)
{
  u8 buff;
  if(USART_GetITStatus(USART1,USART_IT_IDLE)!= RESET)				//���߿���
  {
    //clear the idle pending flag 
    (void)USART1->SR;
    (void)USART1->DR;

    for(int i=0;i<USART1_DMA_RX_LEN;i++)
    {
      buff=USART1_RXBUFF[i];
      while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
      USART_SendData(USART1,buff);
    }
    
  }
}
