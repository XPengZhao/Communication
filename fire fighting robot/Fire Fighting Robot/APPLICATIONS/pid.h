#ifndef PID_H
#define PID_H

#define kp 0
#define ki 0
#define kd 0
#define STANDARD_DIS 200

typedef struct{
  float P,I,D,FF,MaxError;
}PIDParams;

typedef struct{
  float Error,Target;
}PIDState;

void Speed_Control(void);
void Pos_Control(void);

#endif
