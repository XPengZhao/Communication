#include "main.h"

/**/
void fire_fighting()
{

    if(judge_result==fire_on_left){         //��⵽����л�
      FanMotor_Open();                      //������
      turn_left45();                        //��ת45
      delay_ms(1000);                       //����Ŀ�ĵ㴵1000ms
      turn_left45_return();                 //����
      FanMotor_Close();                     //�ط���
      FSMFlagNext=FINDROOM_FLAG;                 //�����֮��������״̬��Ϊ�ճ�����
    }

    if(judge_result==fire_on_right){
      FanMotor_Open();
      turn_right45();
      delay_ms(1000);
      turn_right45_return();
      FanMotor_Close();
      FSMFlagNext=FINDROOM_FLAG;
    }
    
    if(judge_result==no_fire){
      FanMotor_Close();
      return;
    }

  return ;
}
