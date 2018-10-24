#include "main.h"

u8 turn_direction=0;

/**
  * @brief ����Ƿ���Ҫת�䣬��Ҫ��ת��
  * @param None
  * @retval None
  * @details ������ת
*/
void CheckTurn(void)
{
  if(distance.front<19)
  {
    if(distance.right>40)
    {
      FSMFlagNext=TURN_FLAG;
      turn_direction=TURNLEFT;
    }
    else if(distance.left>40)
    {
      FSMFlagNext=TURN_FLAG;
      turn_direction=TURNRIGHT;
    }
  }
}





////////////////////����ʱ����ת90�Ⱥ���ת�꼴ͣ//////////////////////////////////
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
  //ת�䲿��
  if(turn_direction==TURNRIGHT)
  {
    turn_right_withdelay();
  }
  else if(turn_direction==TURNLEFT)
  {
    turn_left_withdelay();
  }

  //���ô���������
  Get_Distance();
  left_encoder_count=0;
  right_encoder_count=0;

}

/////////////////////////////////////////////////////////////////////////////




/*************ת45�ȣ�ת���ͣ�� �����𶯻�ʹencoder��������*********/
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
