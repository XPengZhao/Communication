#include "main.h"

u8 map[6][6];

//��ǰλ����Ϣ������x����,y����
Car_info car_info={0,0,0};

/**
  * @brief ��ȡС����λ����Ϣ
  */
void GetCarInfo(void)
{
  /*----------------ͨ�������������ߵ�·��--------------------*/
  float length=0;
  length=(left_encoder_count+right_encoder_count)/60*WHEEL_DIR;
  if(length>ONESTEP)
  {
    switch(car_info.direction)
    {
      case 0:car_info.pos_y++;break;
      case 1:car_info.pos_x++;break;
      case 2:car_info.pos_y--;break;
      case 3:car_info.pos_x--;break;
    }
    left_encoder_count-=30;
    right_encoder_count-=30;
    __Sensordata.POS_X=car_info.pos_x;
    __Sensordata.POS_Y=car_info.pos_y;
  }
}
