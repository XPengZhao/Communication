#include "main.h"

void taskloop(void)
{
  static u32 system_5ms=0;
  system_5ms++;

#if TASKONCE_CHECK
  static u8 taskloop_flag=1;
  if(taskloop_flag)
  {
    printf("taskloop execute successful!\r\n");
    taskloop_flag=0;
  }
#elif TASKDUPLICATE_CHECK
printf("taskloop execute successful!\r\n");
#endif

  Duty_5ms();
  if(system_5ms%2==0)
    Duty_10ms();
  if(system_5ms%4==0)
    Duty_20ms();
  if(system_5ms%10==0)
    Duty_50ms();
  if(system_5ms%20==0)
    Duty_100ms();
}

 
void Duty_5ms(void)
{

#if TASKONCE_CHECK
  static u8 Duty5ms_flag=1;
  if(Duty5ms_flag)
  {
    printf("Duty_5ms execute successful!\r\n");
    Duty5ms_flag=0;
  }
#elif TASKDUPLICATE_CHECK
printf("Duty_5ms execute successful!\r\n");
#endif

}

void Duty_10ms(void)
{
  DatatransferTask();
#if TASKONCE_CHECK
  static u8 Duty10ms_flag=1;
  if(Duty10ms_flag)
  {
    printf("Duty_10ms execute successful!\r\n");
    Duty10ms_flag=0;
  }
#elif TASKDUPLICATE_CHECK
printf("Duty_10ms execute successful!\r\n");
#endif
}

void Duty_20ms(void)
{
#if TASKONCE_CHECK
  static u8 Duty20ms_flag=1;
  if(Duty20ms_flag)
  {
    printf("Duty_20ms execute successful!\r\n");
    Duty20ms_flag=0;
  }
#elif TASKDUPLICATE_CHECK
printf("Duty_20ms execute successful!\r\n");
#endif

}

void Duty_50ms(void)
{
  Pos_Control();
#if TASKONCE_CHECK
  static u8 Duty50ms_flag=1;
  if(Duty50ms_flag)
  {
    printf("Duty_50ms execute successful!\r\n");
    Duty50ms_flag=0;
  }
#elif TASKDUPLICATE_CHECK
printf("Duty_50ms execute successful!\r\n");
#endif

}

void Duty_100ms(void)
{


#if TASKONCE_CHECK
  static u8 Duty100ms_flag=1;
  if(Duty100ms_flag)
  {
    printf("Duty_100ms execute successful!\r\n");
    Duty100ms_flag=0;
  }
#elif TASKDUPLICATE_CHECK
printf("Duty_100ms execute successful!\r\n");
#endif

}
