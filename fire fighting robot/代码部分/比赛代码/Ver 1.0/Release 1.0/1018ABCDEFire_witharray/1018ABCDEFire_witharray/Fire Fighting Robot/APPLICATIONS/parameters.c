#include "main.h"

/**
  * @brief —” ±∆Ù∂Ø
  */
void SenserOffsetInit(void)
{
  static u16 count=0;
  if(count%10==0)       //100ms
  {
    Get_Distance_Front();
  }
  if(count==500)        //5s
  {
    FSMflag=TASKLOOP_FLAG;
  }
  count++;
}

