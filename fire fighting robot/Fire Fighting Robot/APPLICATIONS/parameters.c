#include "main.h"

/**
  * @brief 等待小车右超声波值稳定在100~300mm
  */
void SenserOffsetInit(void)
{
  static int16_t last_dis=0,count1=0;
  count1++;
  if(count1%10==0)
  {
    Get_Distance_Front();
/*    if(last_dis>150&&last_dis<300)
    {
      if(distance.front>150&&distance.front<300)
      {
        FSMflag=START_FLAG;
        RED_ON();
        return;
      }
    }
    last_dis=distance.front; */
    DatatransferTask();
    RED_OFF();
    count1=0;

  }
}

void StartSearch(void)
{
  static u8 count2=0;
  count2++;
  if(count2%10==0)
  {
      Get_Distance_Front();
    if(distance.front<100)
    {
      FSMflag=TASKLOOP_FLAG;
      RED_OFF();
    }
    count2=0;
  }
}
