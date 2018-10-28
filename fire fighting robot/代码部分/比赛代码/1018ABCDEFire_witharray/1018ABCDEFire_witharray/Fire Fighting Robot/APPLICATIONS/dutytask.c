#include "main.h"


void taskloop(void)
{
  static u32 system_10ms=0;
  system_10ms++;

  Duty_10ms();
  if(system_10ms%2==0)
    Duty_20ms();
  if(system_10ms%3==0)
    Duty_30ms();
  if(system_10ms%10==0)
    Duty_100ms();
  if(system_10ms%100==0)
    Duty_1000ms();
}

void Duty_10ms(void)
{
}

void Duty_20ms(void)
{
  if(along_flag==RIGHT)
    Pos_ControlRight();
  else if(along_flag==LEFT)
    Pos_ControlLeft();

}


void Duty_30ms(void)
{
  u8 FirePosition[5]={1,1,1,1,1};
  static u8 candle=2;         //灭一个火则减一，为0时返程 如果图有3个火焰直接改为3就好。
  static u8 FLAG=1,CLR=1;     //flag:选择step   clr：标志第一次进入step，完成step时退出

  if(FLAG==1){                //沿墙 step1  FLAG=0,1
    along_flag=LEFT;
    Get_Distance_Front();
    if(__distance.front<=42){
      along_flag=0;
      FLAG++;                 //along_flag FLAG CLR 
    }
  }

  else if(FLAG==2){
    along_flag=0;
    MotorLeft(100);
    MotorRight(100);
    Get_Distance_Front();
    if(__distance.front<=18){
      turn_left_withdelay();
      FLAG++;
    }
  }
  
  else if(FLAG==3){
    along_flag=RIGHT;
    Get_Distance_Front();
    if(__distance.front<=42){
      CLR=1;
      along_flag=0;
      FLAG++;
    }
  }

else if(FLAG==4){
  along_flag=0;
  MotorLeft(100);
  MotorRight(100);
  Get_Distance_Front();
  if(__distance.front<=18){

    if(FirePosition[0]){
      MotorLeft(0);
      MotorRight(0);
      FanMotor_Open();
      turn_left45();
      delay_ms(1000);
      turn_left45_return();
      FanMotor_Close();
      candle--;
    }

    turn_right_withdelay();
    FLAG++;
  }
}

else if(FLAG==5){
  along_flag=LEFT;
  if(CLR){
    Get_Distance_Front();
    CLR=0;
  }
  Get_Distance_Front();
  if(__distance.front<=18){

    if(FirePosition[1]){
      MotorLeft(0);
      MotorRight(0);
      FanMotor_Open();
      turn_left45();
      delay_ms(1000);
      turn_left45_return();
      FanMotor_Close();
      candle--;
    }

    turn_right_withdelay();
    if(candle)
      FLAG++;
    else{
      FLAG=100;
      turn_right_withdelay();
    }
    CLR=1;
  }
}

else if(FLAG==6){
  along_flag=LEFT;
  if(CLR){
    Get_Distance_Front();
    CLR=0;
  }
  Get_Distance_Front();
  if(__distance.front<=18){
    turn_right_withdelay();
    CLR=1;
    FLAG++;
  }
}

else if(FLAG==7){
  along_flag=LEFT;
  Get_Distance_Front();
  if(__distance.front<=18){
    if(FirePosition[2]){
    MotorLeft(0);
    MotorRight(0);
    FanMotor_Open();
    turn_left45();
    delay_ms(1000);
    turn_left45_return();
    FanMotor_Close();
    candle--;
    }
    turn_right_withdelay();
    if(candle)
      FLAG++;
    else
      FLAG=120;
    along_flag=0;
    
  }
}

else if(FLAG==8){
  along_flag=LEFT;
  if(CLR){
    Get_Distance_Front();
    CLR=0;
    }
  Get_Distance_Front();
  if(__distance.front<=42){
    
    FLAG++;
    CLR=1;
    along_flag=0;
  }
}

else if(FLAG==9){
  along_flag=0;
  MotorLeft(100);
  MotorRight(100);
  Get_Distance_Front();
  if(__distance.front<=18){
    turn_left_withdelay();
    FLAG++;
    along_flag=0;
    }
  }


else if(FLAG==10){
  along_flag=RIGHT;
  
  Get_Distance_Front();
  if(__distance.front<=18){
    turn_left_withdelay();
  
    FLAG++;
    CLR=1;
    along_flag=0;
  }
}

else if(FLAG==11){
  along_flag=RIGHT;
  Get_Distance_Right();
  if(__distance.right>=40){				//dont be too small
    FLAG++;
    along_flag=0;
  }
}

else if(FLAG==12){
  along_flag=0;
  if(CLR){
    left_encoder_count=right_encoder_count=0;
    left_encoder_count=right_encoder_count=0;
    CLR=0;
  }
  MotorLeft(100);
  MotorRight(100);
  if(left_encoder_count>=22||right_encoder_count>=22){
    turn_right_withdelay();
    FLAG++;
    CLR=1;
  }
}

else if(FLAG==13){
  along_flag=0;
  if(CLR){
      left_encoder_count=right_encoder_count=0;
      CLR=0;
  }
  MotorLeft(100);
  MotorRight(100);
  if(left_encoder_count>=53||right_encoder_count>=53){
    turn_right_withdelay();
    FLAG++;
    CLR=1;
  }
}

else if(FLAG==14){
  along_flag=0;
  MotorRight(100);
  MotorLeft(100);
  Get_Distance_Right();
  if(__distance.right<=25){
    FLAG++;
  }
}

else if(FLAG==15){
  along_flag=RIGHT;
  Get_Distance_Front();
  if(__distance.front<=18){
    turn_left_withdelay();
    FLAG++;
    along_flag=0;
  }
}

else if(FLAG==16){
  along_flag=RIGHT;
  Get_Distance_Front();
  if(__distance.front<=18){
    if(FirePosition[3]){
    MotorLeft(0);
    MotorRight(0);
    FanMotor_Open();
    turn_right45();
    delay_ms(1000);
    turn_right45_return();
    FanMotor_Close();
    }
    turn_left_withdelay();
    FLAG++;
    along_flag=0;
  }
}

else if(FLAG==17){
  along_flag=RIGHT;
  if(CLR){
      Get_Distance_Front();
      Get_Distance_Front();
      Get_Distance_Front();
      Get_Distance_Front();
      CLR=0;
    }
  Get_Distance_Front();
  if(__distance.front<=18){
    if(FirePosition[4]){
    MotorLeft(0);
    MotorRight(0);
    FanMotor_Open();
    turn_right45();
    delay_ms(1000);
    turn_right45_return();
    FanMotor_Close();
    }
    turn_left_withdelay();
    FLAG++;
    CLR=1;
    along_flag=0;
  }
}

else if(FLAG==18){
  along_flag=RIGHT;
  if(CLR){
      Get_Distance_Front();
      Get_Distance_Front();
      Get_Distance_Front();
      Get_Distance_Front();
      CLR=0;
    }
  Get_Distance_Front();
  if(__distance.front<=42){
    FLAG++;
    CLR=1;
    along_flag=0;
  }
}

else if(FLAG==19){
  along_flag=0;
  MotorLeft(100);
  MotorRight(100);
  Get_Distance_Front();
  if(__distance.front<=22){
    turn_right_withdelay();
    FLAG++;
  }
}

else if(FLAG==20){
  along_flag=0;
  if(CLR){
      left_encoder_count=right_encoder_count=0;
      CLR=0;
  }
  MotorLeft(100);
  MotorRight(100);
  if(left_encoder_count>=51||right_encoder_count>=51){
    turn_right_withdelay();
    FLAG++;
    CLR=1;
  }
}

else if(FLAG==21){
  along_flag=0;
  
  MotorLeft(30);
  MotorRight(30);
  
  Get_Distance_Right();
  if(__distance.right<=30){
    FLAG++;
    CLR=1;
  }
}

else if(FLAG==22){
  along_flag=RIGHT;
  if(CLR){
    Get_Distance_Right();
    Get_Distance_Right();
    CLR=0;
  }
  Get_Distance_Front();
  if(__distance.front<=41){
    
    //turn_right_withdelay();
    //turn_right_withdelay();
    MotorLeft(0);
    MotorRight(0);
    FLAG=23;                          //no 23 step
    CLR=1;
    along_flag=0;
    
  }
}

else if(FLAG==100){                   //return journey from B fire
  along_flag=RIGHT;
    if(CLR){
    Get_Distance_Front();
    CLR=0;
  }
  Get_Distance_Front();
  if(__distance.front<=18){
    turn_left_withdelay();
    FLAG++;
    CLR=1;
    along_flag=0;
  }
}

else if(FLAG==101){
  along_flag=RIGHT;
  Get_Distance_Right();
  if(__distance.right>=40){           //dont be too small
    FLAG++;
    along_flag=0;
  }
}

else if(FLAG==102){
  along_flag=LEFT;
  if(CLR){
    left_encoder_count=right_encoder_count=0;
    CLR=0;
  }
  if(left_encoder_count>=85||right_encoder_count>=85){
    turn_right_withdelay();
    FLAG=21;
    CLR=1;
    along_flag=0;
  }
}


else if(FLAG==120){ 				//return journey from  C fire
  along_flag=LEFT;
  if(CLR){
    Get_Distance_Front();
    CLR=0;
    }
  Get_Distance_Front();
  if(__distance.front<=42){
    
    FLAG++;
    CLR=1;
    along_flag=0;
  }
}

else if(FLAG==121){
  along_flag=0;
  MotorLeft(100);
  MotorRight(100);
  Get_Distance_Front();
  if(__distance.front<=18){
    turn_left_withdelay();
    FLAG=100;
    along_flag=0;
    }
}

}





void Duty_100ms(void)
{

}

void Duty_1000ms(void)
{
  
}
