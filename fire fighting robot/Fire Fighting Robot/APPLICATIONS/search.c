#include "main.h"

u8 FSMFlagNext=SENSOROFFSET_FLAG;         //��̬
u8 FSMFlagNow =0;
u8 FSMFlagLast=0;                         //��һ��״̬
/**
  * @brief ���������״̬
  * @param ����ı��
  * @retval None
  * @details �жϷ�����ڵ�����
  *          ִ�����񣺱�������ֱ��  ����������ľ���
  */
void FindRoom(u8 room_number)
{
  FSMFlagNow=FSMFlagNext;
  GoStraight();
  Get_Distance();
  switch(room_number)
  {
    case 1:
      if(distance.front<20)
      {
        if(distance.left<40 && distance.right>40)
        {
          FSMFlagNext=ENTERROOM_FLAG;
        }
      }
      break;

    case 2:
      if(distance.left<40)
        if(distance.right>40 && distance.front>40)
        {
          FSMFlagNext=ENTERROOM_FLAG;
        }
      break;

    default:
      break;
  }
}

void EnterRoom(u8 room_number)
{
  FSMFlagLast=FSMFlagNow;
  FSMFlagNow=FSMFlagNext;
  switch(room_number)
  {
    case 1:
      delay_ms(500);
      FSMFlagNext=TURN_FLAG;
      break;

    case 2:
      delay_ms(500);
      FSMFlagNext=TURN_FLAG;
      break;

    default:
      break;
  }
}
