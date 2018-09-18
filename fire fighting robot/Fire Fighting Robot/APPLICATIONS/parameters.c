#include "main.h"

/**
  * @brief 等待小车右超声波值稳定在100~300mm
  */
void SenserOffsetInit(void)
{
  static int16_t last_dis=0;
  Get_Distance_Front();
  printf("i'm in sensor\r\n");
  if(last_dis>150&&last_dis<300)
  {
    if(distance.front>150&&distance.front<300)
    {
      FSMflag=START_FLAG;
      RED_ON();
    }
  }
  last_dis=distance.front;
  RED_OFF();
}

void StartSearch(void)
{
  Get_Distance_Front();
  printf("i'm in start\t");
  printf("%d\r\n",distance.front);
  if(distance.front<100)
  {
    FSMflag=TASKLOOP_FLAG;
    RED_OFF();
  }
}
