#include "main.h"

/**/
void fire_fighting()
{
  u8 temp;
  temp=judge_fire();

  switch (temp)
  {
    case fire_on_left:              //���0��λ����ƫ��45��
      FanMotor_Open();
      break;
    case fire_in_front:
      FanSteering(45);

      FanMotor_Open();
      break;
    case fire_on_right:
      FanSteering(90);
      FanMotor_Open();
      break;
    case no_fire:
      FanMotor_Close();
      return;
    default : return;		
  }
  return ;
}

