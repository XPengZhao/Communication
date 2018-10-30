#include "main.h"

static u8 __FilterFlush_l=0;
static u8 __FilterFlush_r=0;
/*
Q:����������Q���󣬶�̬��Ӧ��죬�����ȶ��Ա仵
R:����������R���󣬶�̬��Ӧ�����������ȶ��Ա��
x_last=x(k-1|k-1)��һʱ�̵ľ���    p_last=p(k-1|k-1)��һʱ�̵�Э����ϸ�ʱ�̵ĵ���ֵ
x_mid=x(k|k-1)����һʱ�̵�Ԥ�����    p_mid=p(k|k-1)Ԥ��Э����
z_measure ����ֵ    R���������������Ϊ����Э����
x_now����ó��ı�ʱ�̾��룬p_now��������ı�ʱ��Э�������һʱ�̵���
*/
void kalmanfilter_r(u16 *z_measure)
{
  static float x_mid1,x_last1=0,p_mid1,p_last1=0,p_now1,x_now1=0;
  static float Q1=ProcessNiose_Q,kg1,R1=MeasureNoise_R;

  if(!__FilterFlush_r)
  {
    __FilterFlush_r=1;
    x_last1=*z_measure;
  }
  x_mid1=x_last1;                         //Ԥ������һʱ��һ��
  p_mid1=p_last1+Q1;                      //Ԥ��Э����Ϊ��һʱ��Э����+Q_Noise
  kg1=p_mid1/(p_mid1+R1);                 //kgΪkalman filter��R Ϊ��������
  x_now1=x_mid1+kg1*(*z_measure-x_mid1);  //�����������ֵ
  p_now1=(1-kg1)*p_mid1;                  //����ֵ��Ӧ��covariance
  p_last1=p_now1;                         //����covariance ֵ
  x_last1=x_now1;                         //����ϵͳ״ֵ̬
  *z_measure=(u16)x_now1;
}

void kalmanfilter_l(u16 *z_measure)
{
  static float x_mid2,x_last2=0,p_mid2,p_last2=0,p_now2,x_now2=0;
  static float Q2=ProcessNiose_Q,kg2,R2=MeasureNoise_R;

  if(!__FilterFlush_l)
  {
    __FilterFlush_l=1;
    x_last2=*z_measure;
  }
  x_mid2=x_last2;                       //Ԥ������һʱ��һ��
  p_mid2=p_last2+Q2;                     //Ԥ��Э����Ϊ��һʱ��Э����+Q_Noise
  kg2=p_mid2/(p_mid2+R2);                 //kgΪkalman filter��R Ϊ��������
  x_now2=x_mid2+kg2*(*z_measure-x_mid2);  //�����������ֵ
  p_now2=(1-kg2)*p_mid2;                   //����ֵ��Ӧ��covariance
  p_last2=p_now2;                         //����covariance ֵ
  x_last2=x_now2;                            //����ϵͳ״ֵ̬
  *z_measure=(u16)x_now2;
}

void FilterFlush(void)
{
  __FilterFlush_l=0;
  __FilterFlush_r=0;
}
