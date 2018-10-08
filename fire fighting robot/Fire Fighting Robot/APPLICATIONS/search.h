#ifndef SEARCH_H
#define SEARCH_H

#define WHEEL_DIR 7
#define ONESTEP 41.5       //一格迷宫
#define RIGHTWALL_FLAG 0
#define LEFTWALL_FLAG 1
#define NOWALL_FLAG 2

//当前位置信息：朝向，x坐标,y坐标
typedef struct{
  u8 direction;
  u8 pos_x;
  u8 pos_y;
}Car_info;

extern Car_info car_info;

void GetCarInfo(void);

#endif
