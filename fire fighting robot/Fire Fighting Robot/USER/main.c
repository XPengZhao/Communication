#include "main.h"

int main(void)
{
  Driver_Init();
  while(1)
  {
    switch(FSMFlagNext)
    {
      case TURN_FLAG:  Turn();  break;
      case ENTERROOM_FLAG: EnterRoom(RoomNumber); break;
      default:  break;
    }
  }
}
