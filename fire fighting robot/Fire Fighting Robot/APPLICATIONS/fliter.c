#include "main.h"

/*
Q:����������Q���󣬶�̬��Ӧ��죬�����ȶ��Ա仵
R:����������R���󣬶�̬��Ӧ�����������ȶ��Ա��
x_last=x(k-1|k-1)��һʱ�̵ľ���    p_last=p(k-1|k-1)��һʱ�̵�Э����ϸ�ʱ�̵ĵ���ֵ
x_mid=x(k|k-1)����һʱ�̵�Ԥ�����    p_mid=p(k|k-1)Ԥ��Э����
z_measure ����ֵ    R���������������Ϊ����Э����
x_now����ó��ı�ʱ�̾��룬p_now��������ı�ʱ��Э�������һʱ�̵���
*/

void kalmanfilter(u16 *z_measure)
{
  static float x_mid,x_last=0,p_mid,p_last=0,p_now,x_now=0;
  static float Q=ProcessNiose_Q,kg,R=MeasureNoise_R;
  static int8_t init_flag=0;
  if(!init_flag)
  {
    init_flag=1;
    x_last=*z_measure;
  }
  x_mid=x_last;                       //Ԥ������һʱ��һ��
  p_mid=p_last+Q;                     //Ԥ��Э����Ϊ��һʱ��Э����+Q_Noise
  kg=p_mid/(p_mid+R);                 //kgΪkalman filter��R Ϊ��������
  x_now=x_mid+kg*(*z_measure-x_mid);  //�����������ֵ
  p_now=(1-kg)*p_mid;                   //����ֵ��Ӧ��covariance
  p_last=p_now;                         //����covariance ֵ
  x_last=x_now;                            //����ϵͳ״ֵ̬
  *z_measure=(u16)x_now;
}

//�˵��ִ����
void limitfilter(u16 *measure,u16 refer)
{
  int16_t err=*measure-refer;
  if(err>20||err<20)
  {
    *measure=refer;
  }
}
