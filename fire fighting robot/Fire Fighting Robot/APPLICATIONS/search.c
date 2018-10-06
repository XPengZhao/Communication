#include "main.h"

u8 map[6][6];

//当前位置信息：朝向，x坐标,y坐标
Car_info car_info={0,0,0};

/**
  * @brief 获取小车的位置信息
  */
void GetCarInfo(void)
{
  /*----------------通过编码器计算走的路程--------------------*/
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
