#include "main.h"

/**
  * @brief �ȴ�С���ҳ�����ֵ�ȶ���100~300mm
  */
void SenserOffsetInit(void)
{
  static u16 count=0;
  if(count%10==0)
  {
    Get_Distance_Front();
  }
  if(count==1000)
  {
    FSMflag=TASKLOOP_FLAG;
  }
  count++;
}

