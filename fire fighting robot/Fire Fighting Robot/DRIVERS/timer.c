#include "main.h"

u8  TIM2CH2_CAPTURE_STA;            //保存捕获状态
u16 TIM2CH2_CAPTURE_VAL;            //保存捕获值
u8  TIM3CH3_CAPTURE_STA;            //保存捕获状态
u16 TIM3CH3_CAPTURE_VAL;            //保存捕获值
u8  TIM5CH3_CAPTURE_STA;            //保存捕获状态
u16 TIM5CH3_CAPTURE_VAL;            //保存捕获值

/**
  * @brief 控制底盘电机的PWM波驱动
  * @param None
  * @retval None
  * @details 1.右电机接PD.12，左电机接PD.13(从PB.5,PB.6重映射)
  *          2.通过TIM4_CH1与TIM4_CH2输出PWM波,PWM波频率50Hz
  *          3.占空比 speed/ARR_PWM，在这里是 speed/10000
  *          4.通过MotorRight(TIM4,u16 speed);与 MotorLeft(TIM4,u16 speed);
  */
void PWM_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;  
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;  
    TIM_OCInitTypeDef  TIM_OCInitStructure;  

    //端口重映射
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_AFIO,ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

    //设置该引脚为复用输出功能,输出TIM4 CH1(PD.12复用输出)、TIM4 CH2(PD.13复用输出)的PWM脉冲波形
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;    //TIM4_CH1(PD.12复用输出)、TIM4_CH2(PD.13复用输出)  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;             //复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);  
      
    TIM_TimeBaseStructure.TIM_Period = ARR_PWM;                 //设置在下一个更新事件装入活动的自动重装载寄存器
    TIM_TimeBaseStructure.TIM_Prescaler =PSC_PWM;               //设置用来作为TIMx时钟频率除数的预分频值
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;                //设置时钟分割:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM向上计数模式
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);             //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位  
    
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;           //选择定时器模式:TIM脉冲宽度调制模式1  
    TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable; //比较输出使能  
    TIM_OCInitStructure.TIM_Pulse = 0;                          //设置待装入捕获比较寄存器的脉冲值  
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;   //输出极性:TIM输出比较极性高  

    TIM_OC1Init(TIM4, &TIM_OCInitStructure);                    //根据TIM_OCInitStruct中指定的参数初始化外设TIMx   
    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);           //CH1预装载使能
    TIM_OC2Init(TIM4, &TIM_OCInitStructure);                    //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);           //CH2预装载使能  

    TIM_ARRPreloadConfig(TIM4, ENABLE);                         //使能TIMx在ARR上的预装载寄存器  
    TIM_CtrlPWMOutputs(TIM4,ENABLE);                            //MOE 主输出使能
    TIM_Cmd(TIM4, ENABLE);

}

/**
  * ----------------------------------------------------------------------------
  * 右超声波接PB.0
  * 主函数使用时先设置中断分组 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  * 接着调用 Wave_Init();
  * 最后调用 Get_Distance();即可得出距离
  */


void Wave_Init(void){
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_ICInitTypeDef  TIM2_ICInitStructure;
    TIM_ICInitTypeDef  TIM3_ICInitStructure;
    TIM_ICInitTypeDef  TIM5_ICInitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);        //使能TIM2时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);        //使能TIM3时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);        //使能TIM5时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOA, ENABLE);

    /*----------------------------------Front---------------------------------*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;                   //trig-->PC.11端口配置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;             //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);                       //根据设定参数初始化PC.11
    GPIO_ResetBits(GPIOC,GPIO_Pin_11);                           //trig下拉电位
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;                    //echo-->PA.1 端口配置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;                //下拉输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);

  /*----------------------------------Left-----------------------------------*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;                   //trig-->PC.13端口配置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOC,GPIO_Pin_13);                           //trig 下拉电位
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;                    //echo-->PA.2 端口配置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;                //下拉输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /*----------------------------------Right-----------------------------------*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;                   //trig-->PC.12端口配置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOC,GPIO_Pin_12);                           //trig 下拉电位
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;                    //echo-->PB.0 端口配置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;                //下拉输入
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /*------------------------------TIM2--------------------------------------*/
    //初始化TIM2时基
    TIM_TimeBaseStructure.TIM_Period = ARR_WAVE;                 //设定计数器自动重装值 
    TIM_TimeBaseStructure.TIM_Prescaler =PSC_WAVE;               //预分频器
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;      //设置时钟分割:TDTS= Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);              //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位


    //初始化TIM2输入捕获参数
    TIM2_ICInitStructure.TIM_Channel = TIM_Channel_2;            //选择输入端 IC2映射到TI2上
    TIM2_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising; //上升沿捕获
    TIM2_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI2上
    TIM2_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;       //配置输入分频,不分频 
    TIM2_ICInitStructure.TIM_ICFilter = 0x00;                    //配置输入滤波器 不滤波
    TIM_ICInit(TIM2, &TIM2_ICInitStructure);


    //中断分组初始化
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;              //TIM2中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;    //先占优先级2级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;           //从优先级0级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;              //IRQ通道被使能
    NVIC_Init(&NVIC_InitStructure);                              //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 
    
    TIM_ITConfig(TIM2,TIM_IT_Update|TIM_IT_CC2,ENABLE);          //允许更新中断 ,允许CC1IE捕获中断
    TIM_Cmd(TIM2,ENABLE);                                        //使能定时器2
    
    /*------------------------------TIM3--------------------------------------*/
    //初始化定时器3 TIM3	 
    TIM_TimeBaseStructure.TIM_Period = ARR_WAVE;                 //设定计数器自动重装值 
    TIM_TimeBaseStructure.TIM_Prescaler =PSC_WAVE;               //预分频器
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;      //设置时钟分割:TDTS= Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);              //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位


    //初始化TIM3输入捕获参数
    TIM3_ICInitStructure.TIM_Channel = TIM_Channel_3;            //选择输入端 IC3映射到TI3上
    TIM3_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising; //上升沿捕获
    TIM3_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI3上
    TIM3_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;       //配置输入分频,不分频 
    TIM3_ICInitStructure.TIM_ICFilter = 0x00;                    //配置输入滤波器进行滤波，不滤波
    TIM_ICInit(TIM3, &TIM3_ICInitStructure);


    //中断分组初始化
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;              //TIM5中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;    //先占优先级2级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;           //从优先级0级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;              //IRQ通道被使能
    NVIC_Init(&NVIC_InitStructure);                              //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 
    
    TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC3,ENABLE);          //允许更新中断 ,允许CC1IE捕获中断	
    TIM_Cmd(TIM3,ENABLE);                                        //使能定时器3
    
    /*------------------------------TIM5--------------------------------------*/
    
    //初始化定时器5 TIM5
    TIM_TimeBaseStructure.TIM_Period = ARR_WAVE;                 //设定计数器自动重装值 
    TIM_TimeBaseStructure.TIM_Prescaler =PSC_WAVE;               //预分频器   
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;      //设置时钟分割:TDTS= Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);


    //初始化TIM3输入捕获参数
    TIM5_ICInitStructure.TIM_Channel = TIM_Channel_3;            //CC2S=01 	选择输入端 IC2映射到TI2上
    TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising; //上升沿捕获
    TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI2上
    TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;       //配置输入分频,不分频 
    TIM5_ICInitStructure.TIM_ICFilter = 0x00;                    //配置输入滤波器进行滤波
    TIM_ICInit(TIM5, &TIM5_ICInitStructure);


    //中断分组初始化
    NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;             //TIM5中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;   //先占优先级2级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;          //从优先级0级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //IRQ通道被使能
    NVIC_Init(&NVIC_InitStructure);                             //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 
    
    TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC3,ENABLE);         //允许更新中断 ,允许CC1IE捕获中断
    TIM_Cmd(TIM5,ENABLE);                                       //使能定时器3
}

//定时器2中断服务程序	 
void TIM2_IRQHandler(void)
{
  if((TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET))
    if((TIM2CH2_CAPTURE_STA&0X80)==0)
      if(TIM2CH2_CAPTURE_STA&0X40)
      {
        if((TIM2CH2_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
        {
          TIM2CH2_CAPTURE_STA|=0X80;//标记成功捕获了一次
          TIM2CH2_CAPTURE_VAL=0XFFFF;
        }
        else 
          TIM2CH2_CAPTURE_STA++;
      }
  if(TIM_GetITStatus(TIM2, TIM_IT_CC2) != RESET)//通道3发生捕获事件
  {
    if(TIM2CH2_CAPTURE_STA&0X40)		//捕获到一个下降沿
    { 			
      TIM2CH2_CAPTURE_STA|=0X80;		//标记成功捕获到一个完整脉冲
      TIM2CH2_CAPTURE_VAL=TIM_GetCapture2(TIM2);
      TIM_OC2PolarityConfig(TIM2,TIM_ICPolarity_Rising); //CC3P=0 设置为上升沿捕获
    }
    else                            //还未开始,第一次捕获上升沿
    {
      TIM2CH2_CAPTURE_STA=0;      //清空
      TIM2CH2_CAPTURE_VAL=0;
      TIM_SetCounter(TIM2,0);
      TIM2CH2_CAPTURE_STA|=0X40;  //标记捕获到了上升沿
      TIM_OC2PolarityConfig(TIM2,TIM_ICPolarity_Falling);		//CC3P=1 设置为下降沿捕获
    }    
    }
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC2|TIM_IT_Update); //清除中断标志位
}

void TIM3_IRQHandler(void)
{
  if((TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET))
    if((TIM3CH3_CAPTURE_STA&0X80)==0)
      if(TIM3CH3_CAPTURE_STA&0X40)
      {
        if((TIM3CH3_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
        {
          TIM3CH3_CAPTURE_STA|=0X80;//标记成功捕获了一次
          TIM3CH3_CAPTURE_VAL=0XFFFF;
        }
        else 
          TIM3CH3_CAPTURE_STA++;
      }
  if(TIM_GetITStatus(TIM3, TIM_IT_CC3) != RESET)//通道3发生捕获事件
  {
    if(TIM3CH3_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
    { 			
      TIM3CH3_CAPTURE_STA|=0X80;		//标记成功捕获到一个完整脉冲
      TIM3CH3_CAPTURE_VAL=TIM_GetCapture3(TIM3);
      TIM_OC3PolarityConfig(TIM3,TIM_ICPolarity_Rising); //CC3P=0 设置为上升沿捕获
    }
    else                            //还未开始,第一次捕获上升沿
    {
      TIM3CH3_CAPTURE_STA=0;      //清空
      TIM3CH3_CAPTURE_VAL=0;
      TIM_SetCounter(TIM3,0);
      TIM3CH3_CAPTURE_STA|=0X40;  //标记捕获到了上升沿
      TIM_OC3PolarityConfig(TIM3,TIM_ICPolarity_Falling);		//CC3P=1 设置为下降沿捕获
    }    
    }
    TIM_ClearITPendingBit(TIM3, TIM_IT_CC3|TIM_IT_Update); //清除中断标志位
}

void TIM5_IRQHandler(void)
{
  if((TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET))
    if((TIM5CH3_CAPTURE_STA&0X80)==0)
      if(TIM5CH3_CAPTURE_STA&0X40)
      {
        if((TIM5CH3_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
        {
          TIM5CH3_CAPTURE_STA|=0X80;//标记成功捕获了一次
          TIM5CH3_CAPTURE_VAL=0XFFFF;
        }
        else 
          TIM5CH3_CAPTURE_STA++;
      }
  if(TIM_GetITStatus(TIM5, TIM_IT_CC3) != RESET)//通道3发生捕获事件
  {
    if(TIM5CH3_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
    { 			
      TIM5CH3_CAPTURE_STA|=0X80;		//标记成功捕获到一个完整脉冲
      TIM5CH3_CAPTURE_VAL=TIM_GetCapture3(TIM5);
      TIM_OC3PolarityConfig(TIM5,TIM_ICPolarity_Rising); //CC3P=0 设置为上升沿捕获
    }
    else                            //还未开始,第一次捕获上升沿
    {
      TIM5CH3_CAPTURE_STA=0;      //清空
      TIM5CH3_CAPTURE_VAL=0;
      TIM_SetCounter(TIM5,0);
      TIM5CH3_CAPTURE_STA|=0X40;  //标记捕获到了上升沿
      TIM_OC3PolarityConfig(TIM5,TIM_ICPolarity_Falling);		//CC3P=1 设置为下降沿捕获
    }    
    }
    TIM_ClearITPendingBit(TIM5, TIM_IT_CC3|TIM_IT_Update); //清除中断标志位
}
