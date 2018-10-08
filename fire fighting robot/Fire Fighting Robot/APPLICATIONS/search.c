#include "main.h"


//y               0          1         2          3          4          5     
/*u8 map[6][6]={0b10010110,0b00010000,0b00010000,0b10010000,0b00000000,0b10000000,
              0b00010000,0b00010000,0b10010000,0b00010000,0b00000000,0b10000000,
              0b10010110,0b00101001,0b01000000,0b00010000,0b00000000,0b00000000,
              0b00010110,0b00010000,0b00000000,0b00100000,0b00000000,0b00000000,
              0b00010000,0b00010000,0b00000000,0b10100000,0b00000000,0b00100000,
              0b10010110,0b10010110,0b00000000,0b00100000,0b00100000,0b00100101
};*/
static u8 pid_flag=0;

//当前位置信息：朝向，x坐标,y坐标
Car_info car_info={0,5,3};

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
    left_encoder_count=0;
    right_encoder_count=0;
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

void search_path(void)
{
  GetCarInfo();
  switch(pid_flag)
  {
    case RIGHTWALL_FLAG:Pos_ControlRight();break;
    case LEFTWALL_FLAG:break;
    case NOWALL_FLAG:break;
  }
}