#include "main.h"

u8 __judge_result;        //ȫ�ֱ������ڴ���жϻ�Դ�Ľ����
void judge_fire()       //�ж��Ƿ��л�Դ
{
  u16 tem;
  float temp1,temp3;
  tem=Get_Adc_Average(ADC_Channel_10,1);
  temp1=(float)tem*3.3/4096;
  
  tem=Get_Adc_Average(ADC_Channel_12,1);
  temp3=(float)tem*3.3/4096;

  if(temp1<1){
    __judge_result=FIRE_ON_LEFT;
  }
  
  else if(temp3<1){
    __judge_result=FIRE_ON_RIGHT;
  }
  else
    __judge_result=NO_FIRE;
}
