#include "main.h"

//  int16_t Target,Error_r,Error_l,MaxError
static PIDParams pos_pidparam={14,0,0,80};

//  int8_t ne_min,ne_two,ne_one,zero,one,two,max;��������
//static FuzzyParam fuzzyparam={-35,-20,-15,0,15,20,35};
static FuzzyParam fuzzyparam={-35,-20,-15,0,15,15,35};

//  int8_t ne_min,ne_two,ne_one,zero,one,two,max;΢�ֲ���
//static FuzzyD fuzzyd={30,15,15,40,15,15,30};
static FuzzyD fuzzyd={30,20,15,30,15,20,30};

/*
now_dis ���β����ľ���    last_dis �ϴβ����ľ���
now_diff ��������ź���    last_diff �ϴ�����ź���
*/
void Pos_ControlRight(void)
{
    float e=0,de=0,ctrl_signal=0;
    Get_Distance_Right();
    e = pos_pidparam.Target - __distance.right;
    de = e - pos_pidparam.Error_r;
    pos_pidparam.Error_r = e;

    if(de>8 || de<-8){
      FlushPIDparam();
      FilterFlush();
      return;
    }

    //ģ������
    if(e>2)
    {
      ctrl_signal=fuzzyparam.max+fuzzyd.max*de;
    }
    else if(e==2)
    {
      ctrl_signal=fuzzyparam.two+fuzzyd.two*de;
    }
    else if(e==1)
    {
      ctrl_signal=fuzzyparam.one+fuzzyd.one*de;
    }
    else if(e==0)
    {
      ctrl_signal=fuzzyparam.zero+fuzzyd.zero*de;
    }
    else if(e==-1)
    {
      ctrl_signal=fuzzyparam.ne_one+fuzzyd.ne_one*de;
    }
    else if(e==-2)
    {
      ctrl_signal=fuzzyparam.ne_two+fuzzyd.ne_two*de;
    }
    else if(e<-2)
    {
      ctrl_signal=fuzzyparam.ne_min+fuzzyd.ne_min*de;
    }

    if(ctrl_signal>pos_pidparam.MaxError)
    {
      ctrl_signal=pos_pidparam.MaxError;
    }
    else if(ctrl_signal<-pos_pidparam.MaxError)
    {
      ctrl_signal=-pos_pidparam.MaxError;
    }

    if(e>0)                  //��ƫ
    {
      MotorLeft(100-ctrl_signal);
      MotorRight(100);
    }
    else if(e<0)             //��ƫ
    {
      MotorLeft(100);
      MotorRight(100+ctrl_signal);
    }
    else if(de>0)       //��߻���
    {
      MotorLeft(100-ctrl_signal);
      MotorRight(100);
    }
    else                //�ұ߻���
    {
      MotorLeft(100);
      MotorRight(100+ctrl_signal);
    }

}

void Pos_ControlLeft(void)
{
    float e=0,de=0,ctrl_signal=0;
    Get_Distance_Left();
    e = pos_pidparam.Target - __distance.left;
    de = e - pos_pidparam.Error_l;
    pos_pidparam.Error_l = e;

    if(de>8  || de<-8){
      FlushPIDparam();
      FilterFlush();
      return;
    }

    //ģ������
    if(e>2)
    {
      ctrl_signal=fuzzyparam.max+fuzzyd.max*de;
    }
    else if(e==2)
    {
      ctrl_signal=fuzzyparam.two+fuzzyd.two*de;
    }
    else if(e==1)
    {
      ctrl_signal=fuzzyparam.one+fuzzyd.one*de;
    }
    else if(e==0)
    {
      ctrl_signal=fuzzyparam.zero+fuzzyd.zero*de;
    }
    else if(e==-1)
    {
      ctrl_signal=fuzzyparam.ne_one+fuzzyd.ne_one*de;
    }
    else if(e==-2)
    {
      ctrl_signal=fuzzyparam.ne_two+fuzzyd.ne_two*de;
    }
    else if(e<-2)
    {
      ctrl_signal=fuzzyparam.ne_min+fuzzyd.ne_min*de;
    }

    if(ctrl_signal>pos_pidparam.MaxError)
    {
      ctrl_signal=pos_pidparam.MaxError;
    }
    else if(ctrl_signal<-pos_pidparam.MaxError)
    {
      ctrl_signal=-pos_pidparam.MaxError;
    }

    if(e>0)                  //��ƫ
    {
      MotorLeft(100);
      MotorRight(100-ctrl_signal);
    }
    else if(e<0)             //��ƫ
    {
      MotorLeft(100+ctrl_signal);
      MotorRight(100);
    }
    else if(de>0)       //�ұ߻���
    {
      MotorLeft(100);
      MotorRight(100-ctrl_signal);
    }
    else                //��߻���
    {
      MotorLeft(100+ctrl_signal);
      MotorRight(100);
    }
}

void FlushPIDparam(void)
{
  pos_pidparam.Error_l=0;
  pos_pidparam.Error_r=0;
}

/**
  * @brief ͨ����������ֱ��
  *
  */
void GoStraight(void)
{
  int e;
  float kp=16,u=0;
  e=__left_encoder_count-__right_encoder_count;    //>0 ���ֿ죻<0 ������
  if(e>2)
    e=3;
  else if(e<-2)
    e=-3;

  u=kp*e;
  MotorLeft(86-u);
  MotorRight(100+u-16);
}
