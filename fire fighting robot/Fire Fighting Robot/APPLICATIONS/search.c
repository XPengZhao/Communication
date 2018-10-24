#include "main.h"

u8 FSMFlagNext=SENSOROFFSET_FLAG;         //��̬
u8 FSMFlagNow =0;
u8 FSMFlagLast=0;                         //��һ��״̬
u8 RoomNumber =1;                         //�������

u8 turn_count=1;                          //ת�����

void action1(void)
{
  Get_Distance();
  GoStraight();
  if(distance.front<19){
    if(distance.left>40){
      turn_direction=TURNLEFT;
      Turn();
      turn_count++;
    }

  }
}

void action2(void)
{
  Get_Distance();
  GoStraight();
  if(distance.front<19){
    if(distance.right>40){
      turn_direction=TURNRIGHT;
      Turn();
      turn_count++;
    }
  }
}

void action3(void)
{
  Get_Distance();
  GoStraight();
  if(distance.front<19){
    if(distance.right>40){
      turn_direction=TURNRIGHT;
      Turn();
      turn_count++;
    }
  }
}

void action4(void)
{
  Get_Distance();
  GoStraight();
  if(distance.front<19){
    if(distance.right>40){
      turn_direction=TURNRIGHT;
      Turn();
      turn_count++;
    }
  }
}

void action5(void)
{
  Get_Distance();
  GoStraight();
  if(distance.front<19){
    if(distance.right>40){
      turn_direction=TURNRIGHT;
      Turn();
      turn_count++;
    }
  }
}

void action5(void)
{
  Get_Distance();
  GoStraight();
  if(distance.front<19){
    if(distance.right>40){
      turn_direction=TURNRIGHT;
      Turn();
      turn_count++;
    }
  }
}

void action6(void)
{
  Get_Distance();
  GoStraight();
  if(distance.front<19){
    if(distance.left>40){
      turn_direction=TURNLEFT;
      Turn();
      turn_count++;
    }
  }
}

void action7(void)
{
  Get_Distance();
  GoStraight();
  if(distance.front<19){
    if(distance.left>40){
      turn_direction=TURNLEFT;
      Turn();
      turn_count++;
    }
  }
}

void action8(void)
{
  Get_Distance();
  GoStraight();
  if(distance.front<19){
    if(distance.left>40){
      turn_direction=TURNLEFT;
      Turn();
      turn_count++;
    }
  }
}


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
  Get_Distance();
  GoStraight();

  //�жϷ�������
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

  CheckTurn();

  FSMFlagLast=FSMFlagNow;
}

void EnterRoom(u8 room_number)
{
  FSMFlagNow=FSMFlagNext;

  switch(room_number)
  {
    case 1:
      delay_ms(500);
      turn_direction=TURNRIGHT;
      FSMFlagNext=TURN_FLAG;
      break;

    case 2:
      delay_ms(500);
      turn_direction=TURNRIGHT;
      FSMFlagNext=TURN_FLAG;
      break;

    default:
      break;
  }

  FSMFlagLast=FSMFlagNow;
}

void SearchFire(u8 room_number)
{
  FSMFlagNow=FSMFlagNext;
  Get_Distance();
  GoStraight();
  
  switch(room_number)
  {
    case 1:
      if(IDMarks()==5) ;
    case 2 
  }

  CheckTurn();
}

//�ж���ԵĹ��������
u8 IDMarks(void)
{
  u8 mark=0;

  if(distance.left+distance.right<40 && distance.front>40){
    mark=1;
  }
  else if(distance.left+distance.right>40 && distance.front>40){
    if(distance.left>distance.right)
      mark=2;
    else if(distance.left<distance.right)
      mark=3;
  }
  else if(distance.left+distance.right>40 && distance.front<40){
    if(distance.left>distance.right && distance.right<40)
      mark=4;
    else if(distance.left<distance.right && distance.front<40)
      mark=5;
    else
      mark=6;
  }
  return mark;
}