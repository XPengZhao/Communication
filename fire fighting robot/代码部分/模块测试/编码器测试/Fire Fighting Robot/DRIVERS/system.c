#include "main.h"

/**
  * @brief ���������룬�ڱ������ж�
  * @param None
  * @retval None
  * @details �ڱ��ڼ��жϱ����ڣ������ڱκ���Щ�жϽ���ִ�У�������ִ�У�������жϱ�־λ
  */
void NVIC_SETPRIMASK(void)
{
  __asm__ volatile("CPSID i");
}

/**
  * @brief ���������룬�����ڱ������ж�
  * @param None
  * @retval None
  * @details �ڱ��ڼ��жϱ����ڣ������ڱκ���Щ�жϽ���ִ�У�������ִ�У�������жϱ�־λ
  */
void NVIC_RESETPRIMASK(void)
{
  __asm__ volatile("CPSIE i");
}
