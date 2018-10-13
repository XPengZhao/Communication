#ifndef __DRIVER_H__
#define __DRIVER_H__
#include "main.h"

extern u8 FSMflag;

#define SENSOROFFSET_FLAG  1
#define FIRE_FLAG          2
#define TASKLOOP_FLAG      3
#define SENSORRESET_FLAG   4
#define TURN_FLAG          5

void Driver_Init(void);

#endif
