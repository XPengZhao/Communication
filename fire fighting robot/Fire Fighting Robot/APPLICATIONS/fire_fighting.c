#include "main.h"

/**/
void fire_fighting()
{
    
    if(judge_result==fire_on_left){      //???????
      FanMotor_Open();                   //???
      turn_left45();                     //??45
      delay_ms(1000);                    //??????1000ms
      turn_left45_return();              //??
      FanMotor_Close();                  //???
      FSMflag=TASKLOOP_FLAG;             //????????????????
    }

    if(judge_result==fire_on_right){
      FanMotor_Open();
      turn_right45();
      delay_ms(1000);
      turn_right45_return();
      FanMotor_Close();
      FSMflag=TASKLOOP_FLAG;
    }
    
    if(judge_result==no_fire){
      FanMotor_Close();
      return;
    }

  return ;
}
