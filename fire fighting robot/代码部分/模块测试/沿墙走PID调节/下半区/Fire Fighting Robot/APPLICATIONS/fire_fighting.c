#include "main.h"

/**/
void fire_fighting()
{

    if(__judge_result==FIRE_ON_LEFT){         //��⵽����л�
      FanMotor_Open();                      //������
      turn_left45();                        //��ת45
      delay_ms(1000);                       //����Ŀ�ĵ㴵1000ms
      turn_left45_return();                 //����
      FanMotor_Close();                     //�ط���
    }

    if(__judge_result==FIRE_ON_RIGHT){
      FanMotor_Open();
      turn_right45();
      delay_ms(1000);
      turn_right45_return();
      FanMotor_Close();
    }
    
    if(__judge_result==NO_FIRE){
      FanMotor_Close();
      return;
    }

  return ;
}
