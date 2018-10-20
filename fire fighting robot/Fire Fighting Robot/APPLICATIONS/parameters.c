#include "main.h"

/**
  * @brief �ȴ�С���ҳ�����ֵ�ȶ���100~300mm
  */
void SenserOffsetInit(void)
{
  static u16 count=0;
  if(count%10==0)       //100ms
  {
    Get_Distance_Right();
  }
  if(count==500)        //5s
  {
    FSMFlagNext=FINDROOM_FLAG;
  }
  count++;
}

void SensordataReset(void)
{
  left_encoder_count=0;
  right_encoder_count=0;
  Get_Distance_Right();
  Get_Distance_Left();
  FSMFlagNext=FINDROOM_FLAG;
}
