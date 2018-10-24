#ifndef SEARCH_H
#define SEARCH_H

#include "main.h" 

#define WHEEL_DIR 7
#define ONESTEP 41.5

#define NOT_FOUND  0
#define RIGHT_TURN 1

extern u8 FSMFlagNext;
extern u8 FSMFlagNow;
extern u8 FSMFlagLast;
extern u8 RoomNumber;

#define SENSOROFFSET_FLAG  1
#define FINDROOM_FLAG      2
#define ENTERROOM_FLAG     3
#define OUTROOM_FLAG       4
#define TURN_FLAG          5
#define SEARCHFIRE_FLAG    6
#define PUTOUTFLAG         7
#define SENSORRESET_FLAG   8

void FindRoom(u8 room_number);
void EnterRoom(u8 room_number);

#endif
