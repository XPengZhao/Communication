/*
 * Open_MultiServo.cpp
 *
 *  Created on: 2012-8-31
 *      Author: Administrator
 */


#include <OpenMultiServo.h>


/*********************************************************************************************
 * 74HC595��ATmega328P�������Ӷ���(Ver 3.0)
 *********************************************************************************************/
#define ClkPin     		1  //PB1    ��λʱ�ӱ�����ʱ����һ������
#define DataPin         3  //PB3  �������������

#define Clk_High   		PORTB |= (1<<ClkPin)
#define Clk_Low    		PORTB &= ~(1<<ClkPin)
#define Data_High       PORTB |= (1<<DataPin)
#define Data_Low        PORTB &= ~(1<<DataPin)

volatile const long PwmPro = 40000;
/*********************************************************************************************
 *��������
 *********************************************************************************************/
uint16_t MultiServo::counter2;//������2
uint16_t MultiServo::servotime;//ÿ��servotimeתһ��
uint16_t MultiServo::servoLastAngle[8]={3162,3000,3000,3000,3000,3000,3000,3000};//���ݵ�ǰλ��
uint16_t MultiServo::servoDstAngle[8]={3162,3000,3000,3000,3000,3000,3000,3000};//�洢���Ŀ��λ��
uint16_t MultiServo::Parallel_HighWidSum=0;//�������������֮��

/* �жϷ��������õ��ı��� */
volatile long MultiServo::low_width;//�ܵ͵�ƽʱ��
volatile uint16_t MultiServo::servoNowAngle[8]={3162,3000,3000,3000,3000,3000,3000,3000};//�洢�����ǰλ��
volatile uint16_t MultiServo::servoId;//������
volatile long MultiServo::high_widthsum;//��·��������ܺ�
volatile bool MultiServo::done=false;//���һ��Ŀ��Ƕȱ�־

/*********************************************************************************************
 *�������ܣ���ʼ����·���(���캯��)
 *�����������
 *�����������
 *********************************************************************************************/
void MultiServo::InitOpenMultiChannelServo(void)
{
	InitHc595port();//��ʼ��595�����˿�
	InitTimer1();//��ʼ��16λ��ʱ��1
    InitServo();//��ʼ�����

	int i=0;
	for(i=0;i<8;i++)
	{
		SetServo(i,servoDstAngle[i]);
	}
	TIMSK1 |= (1<<OCIE1A);//ʹ�ܱȽ���Aƥ���ж�
}

/*********************************************************************************************
 *�������ܣ�74HC595����IO��ʼ������
 *�����������
 *�����������
 *********************************************************************************************/
void MultiServo::InitHc595port(void)
{
	DDRB |= (1<<ClkPin)|(1<<DataPin);//����PB1��PB3Ϊ���
	PORTB &= ~((1<<ClkPin)|(1<<DataPin));//PB1��PB3����͵�ƽ
}

/*********************************************************************************************
 *�������ܣ���ʱ��1��ʼ������
 *�����������
 *�����������
 *********************************************************************************************/
void MultiServo::InitTimer1(void)
{
	TCCR1A=0;
	TCCR1B=(1<<CS11);//������8��Ƶ����Ϊ��ʱʱ��
	TCNT1=0;//������ֵ
	OCR1A=2000;//�Ƚ�ƥ���ֵ,��16MHz�������8��Ƶ�󣬶�ʱʱ��Ϊ0.5us��0.5*2000=1ms
	sei();//ʹ��ȫ���ж�
}
/*********************************************************************************************
 *�������ܣ���ʼ����·�������
 *�����������
 *�����������
 *********************************************************************************************/
void MultiServo::InitServo(void)
{
	high_widthsum=0;
	servoId=0;
	Parallel_HighWidSum = servoNowAngle[0]+servoNowAngle[1];

	int i=0;
	for(i=0;i<8;i++)
	{
		high_widthsum += servoNowAngle[i];//��·�����ǰλ�ö�Ӧ��������֮��
	}
	for(i=0;i<8;i++)
	{
		servoLastAngle[i] = servoNowAngle[i];//�����·�����ǰ�Ƕ�
	}
	low_width = PwmPro - high_widthsum;//����������ڣ�20ms��- ������֮�� == �ܵĵ͵�ƽ
}
/*********************************************************************************************
 *��ʱ��1�Ƚ���ƥ���жϷ�����
 *********************************************************************************************/

SIGNAL (TIMER1_COMPA_vect)
{
	if(!MultiServo::servoId)
	{
		//servoId=0
		Data_High;//�������á�1��
		Clk_High;//ʱ�����á�1��,�����أ�����1��������λ�Ĵ���������һ��������ʱ�����浽����Ĵ���
		Clk_Low;//ʱ�����á�0��
		Data_Low;//�������õ�,����һ��ʱ�ӱ�������λ�Ĵ���
	}
		Clk_High;//ʱ������"1"
		Clk_Low;//ʱ������"0"
	if(MultiServo::servoId==8)
	{
		OCR1A += MultiServo::low_width;//ʣ�µĵ͵�ƽʱ��
		MultiServo::servoId=0;
	}
	else
	{
		OCR1A += MultiServo::servoNowAngle[MultiServo::servoId];
		MultiServo::servoId++;
	}
}
/*********************************************************************************************
 *�������ܣ���ʼ����·�������
 *���������servonum - ������
 *���������   Angle      - ������
 *********************************************************************************************/
void MultiServo::SetServo(uint8_t servonum,uint16_t Angle)
{
	high_widthsum -= servoLastAngle[servonum];//������ľ��������������ȥ��
	high_widthsum += Angle;//���µ��������
	servoLastAngle[servonum]=Angle;//���¶���ľ�����
}
/*********************************************************************************************
 *�������ܣ����¶����ǰ�ǶȺ���
 *�����������
 *�����������

 *********************************************************************************************/
void MultiServo::CommandSet(void)
{

	uint8_t j=0;
	if(servoNowAngle[0]>servoDstAngle[0])	servoNowAngle[0] -= 27;
	if(servoNowAngle[0]<servoDstAngle[0])	servoNowAngle[0] += 27;
	if(servoNowAngle[1]>servoDstAngle[1])	servoNowAngle[1] -= 27;
	if(servoNowAngle[1]<servoDstAngle[1])	servoNowAngle[1] += 27;
	if(servoNowAngle[2]>servoDstAngle[2])	servoNowAngle[2] -= 27;
	if(servoNowAngle[2]<servoDstAngle[2])	servoNowAngle[2] += 27;
	if(servoNowAngle[3]>servoDstAngle[3])	servoNowAngle[3] -= 27;
	if(servoNowAngle[3]<servoDstAngle[3])	servoNowAngle[3] += 27;
	if(servoNowAngle[4]>servoDstAngle[4])	servoNowAngle[4] -= 27;
	if(servoNowAngle[4]<servoDstAngle[4])	servoNowAngle[4] += 27;
	if(servoNowAngle[5]>servoDstAngle[5])	servoNowAngle[5] -= 27;
	if(servoNowAngle[5]<servoDstAngle[5])	servoNowAngle[5] += 27;
	if(servoNowAngle[6]>servoDstAngle[6])	servoNowAngle[6] -= 27;
	if(servoNowAngle[6]<servoDstAngle[6])	servoNowAngle[6] += 27;
	if(servoNowAngle[7]>servoDstAngle[7])	servoNowAngle[7] -= 27;
	if(servoNowAngle[7]<servoDstAngle[7])	servoNowAngle[7] += 27;

    if( (abs(servoNowAngle[0] - servoDstAngle[0])<27)&&
		(abs(servoNowAngle[1] - servoDstAngle[1])<27)&&
		(abs(servoNowAngle[2] - servoDstAngle[2])<27)&&
		(abs(servoNowAngle[3] - servoDstAngle[3])<27)&&
		(abs(servoNowAngle[4] - servoDstAngle[4])<27)&&
		(abs(servoNowAngle[5] - servoDstAngle[5])<27)&&
		(abs(servoNowAngle[6] - servoDstAngle[6])<27)&&
		(abs(servoNowAngle[7] - servoDstAngle[7])<27))
	{
		servoNowAngle[0]=servoDstAngle[0];
		servoNowAngle[1]=servoDstAngle[1];
		servoNowAngle[2]=servoDstAngle[2];
		servoNowAngle[3]=servoDstAngle[3];
		servoNowAngle[4]=servoDstAngle[4];
		servoNowAngle[5]=servoDstAngle[5];
		servoNowAngle[6]=servoDstAngle[6];
		servoNowAngle[7]=servoDstAngle[7];
		MsTimer2::stop();//�رն�ʱ��2
		done = true;
	}
	for(j=0;j<8;j++)
	{
		SetServo(j,servoNowAngle[j]);
	}
	low_width = PwmPro-high_widthsum;
}
/*********************************************************************************************
 *�������ܣ�������ĽǶ�ӳ��Ϊ������
 *���������*joint -  ָ��8·����Ƕȵ�����ָ��
 *��������� runtime   -  ת��Ŀ��Ƕ�����ʱ��
 *����1��0.5ms��0�ȣ���Ӧ����Ϊ1000��2.5ms��180�ȣ���Ӧ����Ϊ5000����5000-1000��/��180-0��=20
 *����2��0.544ms��0�ȣ���Ӧ����Ϊ1088��2.4ms��180�ȣ���Ӧ����Ϊ4800����4800-1088��/��180-0��=20.6
 *********************************************************************************************/
bool MultiServo::SetJointsAngle(uint16_t *joint)
{
	int i;
	for(i=0;i<7;i++)
	{
		if(joint[i]<1000) joint[i]=1000;
		if(joint[i]>5000) joint[i]=5000;
	}
	if((joint[0]!=0)&&(joint[0]!=servoDstAngle[0]))
	{
		servoDstAngle[0] = joint[0];
		servoDstAngle[1] = Parallel_HighWidSum-joint[0];
	}
	for(i=1;i<7;i++)
	{
		if((joint[i]!=0)&&(joint[i]!=servoDstAngle[i+1]))
			servoDstAngle[i+1] = joint[i];
	}
	return true;
}
/*********************************************************************************************
 *�������ܣ����¶�·���λ�ú���
 *�����������
 *�����������
 *********************************************************************************************/
void MultiServo::UpdateMotion(int time)
{
	done = false;
	MsTimer2::set(time,MultiServo::CommandSet);
	MsTimer2::start();//������ʱ��2
	while(!(done&0x1));//�ȴ�ת��λ
}

