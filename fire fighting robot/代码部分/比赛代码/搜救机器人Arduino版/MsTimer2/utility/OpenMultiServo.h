/*
 * OpenMultiServo.h
 *
 *  Created on: 2012-8-31
 *      Author: Administrator
 */

#include <Arduino.h>
#include <./MsTimer2.h>

#ifndef OPEN_MULTISERVO_H_
#define OPEN_MULTISERVO_H_

namespace MultiServo
{
	extern uint16_t counter2;//������2
	extern uint16_t servotime;//ÿ��servotimeתһ��
	extern uint16_t servoLastAngle[8];
	extern uint16_t servoDstAngle[8];//�洢���Ŀ��λ��
	extern volatile long low_width;//ʣ�µ͵�ƽʱ��
	extern volatile uint16_t servoNowAngle[8];//�洢�����ǰλ��
	extern uint16_t Parallel_HighWidSum;//�������������֮��
	extern volatile uint16_t servoId;//������
	extern volatile long high_widthsum;//��·��������ܺ�
	extern volatile bool done;//���һ��Ŀ��Ƕȱ�־

	void InitOpenMultiChannelServo(void);
	bool SetJointsAngle(uint16_t *joint);
	void UpdateMotion(int time);
	void InitHc595port(void);
	void InitTimer1(void);
	void InitServo(void);
	void SetServo(uint8_t servonum,uint16_t Angle);
	void CommandSet(void);//����ִ�к���
}
#endif /* OPEN_MULTISERVO_H_ */
