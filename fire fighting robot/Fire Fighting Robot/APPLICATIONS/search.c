#include "main.h"


//y               0          1         2          3          4          5     
/*u8 m[6][6]={0b10010110,0b00010000,0b00010010,0b10010000,0b00000000,0b10000000,
              0b00010000,0b00010000,0b10010000,0b00010000,0b00000000,0b10000000,
              0b10010110,0b00101001,0b01000101,0b00010000,0b00000000,0b00000000,
              0b00010110,0b00010000,0b00100000,0b00100000,0b00000000,0b00000000,
              0b00010000,0b00010000,0b00100000,0b10100000,0b00000000,0b00100000,
              0b10010110,0b10010110,0b00100000,0b00100000,0b00100000,0b00100101
};*/
//y            0    1    2    3    4    5
u8 map[6][6]={0x00,0x00,0x12,0x00,0x00,0x00,
              0x00,0x00,0x90,0x00,0x00,0x00,
              0x00,0x00,0x45,0x00,0x00,0x00,
              0x00,0x00,0x20,0x00,0x00,0x00,
              0x00,0x00,0x20,0x00,0x00,0x00,
              0x00,0x00,0x20,0x00,0x00,0x00
};

u8 pid_flag=RIGHTWALL_FLAG, turn_flag=NOTURN;

//��ǰλ����Ϣ������x����,y����
Car_info car_info={3,4,2};

/**
  * @brief ��ȡС����λ����Ϣ
  * @param None
  * @retval ������·���1�����򷵻�0
  */
int GetCarInfo(void)
{
  /*----------------ͨ�������������ߵ�·��--------------------*/
  float length=0;
  static u32 last_leftcount=0,last_rightcount=0;
  length=(left_encoder_count + right_encoder_count -
          last_leftcount - last_rightcount) / 60 * WHEEL_DIR;
  if(length>ONESTEP)
  {
    last_leftcount=left_encoder_count;
    last_rightcount=right_encoder_count;
    switch(car_info.direction)
    {
      case 0:car_info.pos_y++;break;
      case 1:car_info.pos_x++;break;
      case 2:car_info.pos_y--;break;
      case 3:car_info.pos_x--;break;
    }
    __Sensordata.POS_X=car_info.pos_x;
    __Sensordata.POS_Y=car_info.pos_y;
    return 1;
  }
  return 0;
}


/**
  * @brief ���»�����״̬��Ϣ
  * @param None
  * @retval None
  * @details ����pid_flag��Ϣ��turn_flag��Ϣ
  */
void update_info(void)
{
  u8 X=car_info.pos_x,Y=car_info.pos_y;
  
  /*-------------------------���µ�����ʽ-----------------------------*/
  if(map[X][Y]&NavigateWithRW_Msk)
  {
    pid_flag=RIGHTWALL_FLAG;
  }
  else if(map[X][Y]&NavigateWithLW_Msk)
  {
    pid_flag=LEFTWALL_FLAG;
  }
  else
  {
    pid_flag=NOWALL_FLAG;
  }
  /*-----------------------------------------------------------------*/

  /*-------------------------����ת����Ϣ------------------------------*/
  if(map[X][Y]&LeftTurnFLAG_Msk)
  {
    if(map[X][Y]&TurnWithFWFLAG_Msk)       //ǰǽ����ת��
    {
      turn_flag=LeftTurnFW;
    }
    else                                   //��ǰǽ����ת��
    {
      turn_flag=LeftTurnNFW;
    }
  }
  else if(map[X][Y]&RightTurnFLAG_Msk)
  {
    if(map[X][Y]&TurnWithFWFLAG_Msk)       //ǰǽ����ת��
    {
      turn_flag=RightTurnFW;
    }
    else                                   //��ǰǽ����ת��
    {
      turn_flag=RightTurnNFW;
    }
  }
  else
  {
    turn_flag=NOTURN;
  }
  /*-----------------------------------------------------------------*/

}

/**
  * @brief ��������ֱ�ߵ���
  * @param None
  * @retval None
  * @details ���ֵ�����ʽ
  */
void Navigate(void)
{
  switch(pid_flag)
  {
    case RIGHTWALL_FLAG:Pos_ControlRight();break;
    case LEFTWALL_FLAG:break;
    case NOWALL_FLAG:break;
  }
}

/**
  * 
  */
void Turn(void)
{
  switch(turn_flag)
  {
    case LeftTurnFW:TurnLeft_WithFW();break;
    case LeftTurnNFW:break;
    case RightTurnFW:TurnRight_WithFW();break;
    case RightTurnNFW:break;
  }
}
