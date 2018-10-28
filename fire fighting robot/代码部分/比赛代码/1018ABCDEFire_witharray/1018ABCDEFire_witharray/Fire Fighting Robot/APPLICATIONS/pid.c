#include "main.h"

//  float P,I,D,FF,MaxError
static PIDParams pos_pidparam={0,0,0,0,80};

//  float Error,Target;
static PIDState  pos_pidstate={0,14};

//  int8_t ne_min,ne_two,ne_one,zero,one,two,max;????
//static FuzzyParam fuzzyparam={-35,-20,-15,0,15,20,35};
static FuzzyParam fuzzyparam={-33,-20,-13,0,13,20,33};

//  int8_t ne_min,ne_two,ne_one,zero,one,two,max;????
//static FuzzyD fuzzyd={28,15,15,40,15,15,28};
static FuzzyD fuzzyd={29,15,15,5,15,15,29};

/*
now_dis ???????    last_dis ???????
now_diff ???????    last_diff ???????
*/
void Pos_ControlRight(void)
{
    float e=0,de=0,ctrl_signal=0;
    Get_Distance_Right();
    e = pos_pidstate.Target - __distance.right;
    de = e - pos_pidstate.Error;
    pos_pidstate.Error = e;

    //????
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

    if(e>0)                  //??
    {
      MotorLeft(100-ctrl_signal);
      MotorRight(100);
    }
    else if(e<0)             //??
    {
      MotorLeft(100);
      MotorRight(100+ctrl_signal);
    }
    else if(de>0)       //????
    {
      MotorLeft(100-ctrl_signal);
      MotorRight(100);
    }
    else                //????
    {
      MotorLeft(100);
      MotorRight(100+ctrl_signal);
    }

}

void Pos_ControlLeft(void)
{
    float e=0,de=0,ctrl_signal=0;
    Get_Distance_Left();
    e = pos_pidstate.Target - __distance.left;
    de = e - pos_pidstate.Error;
    pos_pidstate.Error = e;

    //????
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

    if(e>0)                  //??
    {
      MotorLeft(100);
      MotorRight(100-ctrl_signal);
    }
    else if(e<0)             //??
    {
      MotorLeft(100);
      MotorRight(100);
    }
    else if(de>0)       //????
    {
      MotorLeft(100);
      MotorRight(100-ctrl_signal);
    }
    else                //????
    {
      MotorLeft(100+ctrl_signal);
      MotorRight(100);
    }

}
