#include "main.h"

/**
  * @brief �ȴ�С���ҳ�����ֵ�ȶ���100~300mm
  */
void SenserOffsetInit(void)
{
  static u16 count=0;
  if(count%5==0)       //100ms
  {
    Get_Distance_Left();
    Get_Distance_Right();
  }
  if(count==250)        //5s
  {
  }
  count++;
}

