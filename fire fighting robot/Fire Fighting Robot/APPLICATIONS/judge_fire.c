#include "main.h"

u8 judge_fire()        //判断是否有火源，有返回1，无返回0
{
  u16 tem;
  float temp1,temp2,temp3;
  tem=Get_Adc_Average(ADC_Channel_10,1);
  temp1=(float)tem*3.3/4096;
  tem=Get_Adc_Average(ADC_Channel_11,1);
  temp2=(float)tem*3.3/4096;
  tem=Get_Adc_Average(ADC_Channel_12,1);
  temp3=(float)tem*3.3/4096;

  if(temp1<1)
    return fire_on_left;
  else if(temp2<1)
    return fire_in_front;
  else if(temp3<1)
    return fire_on_right;
  else
    return no_fire;
  
}


