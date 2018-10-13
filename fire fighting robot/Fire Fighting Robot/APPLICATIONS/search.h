#ifndef SEARCH_H
#define SEARCH_H

#define WHEEL_DIR 7
#define ONESTEP 41.5       //һ���Թ�

#define RIGHTWALL_FLAG 0
#define LEFTWALL_FLAG 1
#define NOWALL_FLAG 2

#define NOTURN 0
#define LeftTurnFW 1
#define LeftTurnNFW 2
#define RightTurnFW 3
#define RightTurnNFW 4

#define LeftTurnFLAG_Pos        0
          /*!< ��ת��־λ�� */
#define LeftTurnFLAG_Msk        (1u << LeftTurnFLAG_Pos)
          /*!< ��ת��־ */

#define RightTurnFLAG_Pos       1
          /*!< ��ת��־λ�� */
#define RightTurnFLAG_Msk       (1u << RightTurnFLAG_Pos)
          /*!< ��ת��־ */

#define TurnWithFWFLAG_Pos      2
          /*!< ǰǽ����ת���־λ�� */
#define TurnWithFWFLAG_Msk      (1u << TurnWithFWFLAG_Pos)
          /*!< ǰǽ����ת���־ */

#define TurnWithNFWFLAG_Pos     3
          /*!< ��ǰǽ����ת���־λ�� */
#define TurnWithNFWFLAG_Msk     (1u << TurnWithNFWFLAG_Pos)
          /*!< ��ǰǽ����ת���־ */

#define NavigateWithLW_Pos      4
          /*!< ��ǽ������ֱ�߱�־λ�� */
#define NavigateWithLW_Msk      (1u << NavigateWithLW_Pos)
          /*!< ��ǽ������ֱ�߱�־ */

#define NavigateWithRW_Pos      5
          /*!< ��ǽ������ֱ�߱�־λ�� */
#define NavigateWithRW_Msk      (1u << NavigateWithRW_Pos)
          /*!< ��ǽ������ֱ�߱�־ */

#define NavigateWithNW_Pos      6
          /*!< ��ǽ������ֱ�߱�־λ�� */
#define NavigateWithNW_Msk      (1u << NavigateWithNW_Pos)
          /*!< ��ǽ������ֱ�߱�־ */

#define FireFLAG_Pos            7
          /*!< ��������־λ�� */
#define FireFLAG_Msk            (1u << FireFLAG_Pos)
          /*!< ��������־ */

//��ǰλ����Ϣ������x����,y����
typedef struct{
  u8 direction;
  u8 pos_x;
  u8 pos_y;
}Car_info;

extern Car_info car_info;
extern u8 pid_flag,turn_flag;

int GetCarInfo(void);
void Navigate(void);
void Turn(void);
void update_info(void);
#endif
