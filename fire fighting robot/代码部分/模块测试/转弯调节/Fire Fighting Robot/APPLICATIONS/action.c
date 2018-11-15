#include "main.h"

u8 __turn_direction=0;

////////////////////����ʱ����ת90�Ⱥ���ת�꼴ͣ//////////////////////////////////
void turn_left_withdelay()
{
  MotorLeft(-50);
  MotorRight(50);
  delay_ms(380) ;
  MotorLeft(0)  ;
  MotorRight(0) ;
}

void turn_right_withdelay()
{
  MotorLeft(50)  ;
  MotorRight(-50);
  delay_ms(395)  ;
  MotorLeft(0)   ;
	MotorRight(0) ;
}

void Turn(void)
{
  //ת�䲿��
  if(__turn_direction==TURNRIGHT)
  {
    turn_right_withdelay();
  }
  else if(__turn_direction==TURNLEFT)
  {
    turn_left_withdelay();
  }

  //���ô���������
  Get_Distance();
  __left_encoder_count=0;
  __right_encoder_count=0;

}

/////////////////////////////////////////////////////////////////////////////




/*************ת45�ȣ�ת���ͣ�� �����𶯻�ʹencoder��������*********/
void turn_left45()
{
  MotorRight(20);
  MotorLeft(0);
  delay_ms(1060);
  MotorRight(0);
}

void turn_left45_return()
{
  MotorLeft(0);
  MotorRight(-20);
  delay_ms(890);
  MotorRight(0);
}


void turn_right45()
{
  MotorRight(0);
  MotorLeft(20);
  delay_ms(960);
  MotorLeft(0);
}

void turn_right45_return()
{
  MotorLeft(-20);
  MotorRight(0);
  delay_ms(800);
  MotorLeft(0);
}
