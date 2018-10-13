#ifndef SEARCH_H
#define SEARCH_H

#define WHEEL_DIR 7
#define ONESTEP 41.5       //一格迷宫

#define RIGHTWALL_FLAG 0
#define LEFTWALL_FLAG 1
#define NOWALL_FLAG 2

#define NOTURN 0
#define LeftTurnFW 1
#define LeftTurnNFW 2
#define RightTurnFW 3
#define RightTurnNFW 4

#define LeftTurnFLAG_Pos        0
          /*!< 左转标志位置 */
#define LeftTurnFLAG_Msk        (1u << LeftTurnFLAG_Pos)
          /*!< 左转标志 */

#define RightTurnFLAG_Pos       1
          /*!< 右转标志位置 */
#define RightTurnFLAG_Msk       (1u << RightTurnFLAG_Pos)
          /*!< 右转标志 */

#define TurnWithFWFLAG_Pos      2
          /*!< 前墙导航转弯标志位置 */
#define TurnWithFWFLAG_Msk      (1u << TurnWithFWFLAG_Pos)
          /*!< 前墙导航转弯标志 */

#define TurnWithNFWFLAG_Pos     3
          /*!< 无前墙导航转弯标志位置 */
#define TurnWithNFWFLAG_Msk     (1u << TurnWithNFWFLAG_Pos)
          /*!< 无前墙导航转弯标志 */

#define NavigateWithLW_Pos      4
          /*!< 左墙导航走直线标志位置 */
#define NavigateWithLW_Msk      (1u << NavigateWithLW_Pos)
          /*!< 左墙导航走直线标志 */

#define NavigateWithRW_Pos      5
          /*!< 右墙导航走直线标志位置 */
#define NavigateWithRW_Msk      (1u << NavigateWithRW_Pos)
          /*!< 右墙导航走直线标志 */

#define NavigateWithNW_Pos      6
          /*!< 无墙导航走直线标志位置 */
#define NavigateWithNW_Msk      (1u << NavigateWithNW_Pos)
          /*!< 无墙导航走直线标志 */

#define FireFLAG_Pos            7
          /*!< 需检测火焰标志位置 */
#define FireFLAG_Msk            (1u << FireFLAG_Pos)
          /*!< 需检测火焰标志 */

//当前位置信息：朝向，x坐标,y坐标
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
