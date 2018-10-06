#include "main.h"

/**
  * @brief 等待小车右超声波值稳定在100~300mm
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

