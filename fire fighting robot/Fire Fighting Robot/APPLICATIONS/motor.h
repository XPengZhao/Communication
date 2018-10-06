#ifndef MOTOR_H
#define MOTOR_H
#include "main.h"

void MotorRight(int16_t speed);
void MotorLeft(int16_t speed);
void FanSteering(u8 degree);
void FanMotor(void);
void FanMotor_Open(void);
void FanMotor_Close(void);
void turn_left(void);
void turn_right(void);
#endif

