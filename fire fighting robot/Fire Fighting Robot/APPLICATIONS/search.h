#ifndef SEARCH_H
#define SEARCH_H

#define WHEEL_DIR 7
#define ONESTEP 41.5       //һ���Թ�

//��ǰλ����Ϣ������x����,y����
typedef struct{
  u8 direction;
  u8 pos_x;
  u8 pos_y;
}Car_info;

extern Car_info car_info;

void GetCarInfo(void);

#endif
