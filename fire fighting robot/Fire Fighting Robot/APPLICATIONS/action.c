#include "main.h"

u8 turn_direction=0;

/**
  * @brief 检测是否需要转弯，需要则转弯
  * @param None
  * @retval None
  * @details 优先右转
*/
void CheckTurn(void)
{
  if(distance.front<19)
  {
    if(distance.right>40)
    {
      turn_right_withdelay();
    }
    else if(distance.left>40)
    {
      turn_left_withdelay();
    }
  }
}





////////////////////用延时左右转90度函数转完即停//////////////////////////////////
void turn_left_withdelay()
{
  MotorLeft(-50);
  MotorRight(50);
  delay_ms(440) ;
  MotorLeft(0)  ;
  MotorRight(0) ;
}

void turn_right_withdelay()
{
  MotorLeft(50)  ;
  MotorRight(-50);
  delay_ms(445)  ;
  MotorLeft(0)   ;
}

void Turn(void)
{
  FSMFlagNow=FSMFlagNext;
  if(turn_direction==TURNRIGHT)
  {
    turn_right_withdelay();
  }
  else if(turn_direction==TURNLEFT)
  {
    turn_left_withdelay();
  }
  switch(FSMFlagLast)
  {
    case FINDROOM_FLAG:    FSMFlagNext=FINDROOM_FLAG;break;
    case ENTERROOM_FLAG:   FSMFlagNext=SEARCHFIRE_FLAG;break;
    case SEARCHFIRE_FLAG:  FSMFlagNext=SEARCHFIRE_FLAG;break;
    case OUTROOM_FLAG:     FSMFlagNext=OUTROOM_FLAG;break;
  }
  FSMFlagLast=FSMFlagNow;
}

/////////////////////////////////////////////////////////////////////////////




/*************转45度，转完就停车 风扇震动会使encoder产生脉冲*********/
void turn_left45()
{
  MotorRight(20);
  MotorLeft(0);
  delay_ms(900);
  MotorRight(0);
}

void turn_left45_return()
{
  MotorLeft(0);
  MotorRight(-20);
  delay_ms(960);
  MotorRight(0);
}


void turn_right45()
{
  MotorRight(0);
  MotorLeft(20);
  delay_ms(900);
  MotorLeft(0);
}

void turn_right45_return()
{
  MotorLeft(-20);
  MotorRight(0);
  delay_ms(930);
  MotorLeft(0);
}
