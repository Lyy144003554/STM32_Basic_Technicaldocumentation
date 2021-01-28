//配置引脚
//PWM的输出口必须是复用推免输出
GPIO_Mode_AF_PP;
//如果连接多个接口需要打开重定向功能Remap，因此需要打开AFIO时钟（复用时钟使能）

//配置定时器

TIM_TimeBaseStructure_Prescaler=72-1;//系统默认时钟72MHz，预分频71+1次，得到TIM计数始终为1MHz，计数长度为1999+1=2000
TIM_TimeBaseStructure_Period=2000-1;//必须-1，在内部计算的时候自动加1
//配置定时器的主要设置
TIM_DeInit(TIM2);//利用TIM_Denit函数将Timer设置成为默认值
TIM_InternationalClockConfig（TIM2）；//选择TIM2设置内时钟源
TIM_TimeBaseStructure.TIM_Prescaler=72;//设置预分频系数为72
TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_D1V1;//在固件库中的设置，参数表见书本P90
TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;//向上计数模式
TIM_TimeBaseStructure.TIM_Period=1000-1;//设置计数溢出大小
TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);//配置应用到具体TIM2定时器中
TIM_ARRPreloadConfig（TIM2,DISABLE);//不需要同步输出的时候禁止预装载寄存器
TIM_Cmd(TIM2,ENABLE);//使能TIMx外设
viod TIM_OC3Init(TIM_TypeDef*TIMx,TIM_OCInitType*Def*TIM_OCInitStruct

//配置PWM模式
TIM_OCStructInit(&TimOCInitStructure);//设置默认值
TimOCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;//设置输出模式为PWM1
TimOCInitStructure.TIM_Pulse=400-1;//设置占空比（CCRx/ARR）*100% or（TIM_Pulse/TIM_Period)*100% 
TimOCInitStructure.TIM_OCPolarity=TIM_OCPolarity_HIGH;//TIM输出可比性：高
TimOCInitStructure.TIM_OutputState=TIM_OutputState_Enable;//使能输出状态
TIM_OC3Init(TIM3,&TimOCInitStructure);//TIM3的CH3输出
TIM_CtrlPWMOutput(TIM3,ENABLE);//使能

//修改占空比的函数是
void TIM_SerCompare2(TIM_TypeDef*TIUMx,uint16_t Compare2);
//对于其他函数
TIM_SetComparex(x=1,2,3,4)

//呼吸灯的主程序
#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include "stm32f4xx_gpio.h"
//#define Premap
#define Fremap
//根据宏定义控制PWM的引脚
    #ifdef Premap//部分重定位
    #define Ch1 GPIO_Pin_4//GPIOB
    #define Ch2 GPIO_Pin_5//GPIOB
    #define Ch3 GPIO_Pin_0//GPIOB
    #define Ch4 GPIO_Pin_1//GPIOB
#else
    #ifdef Fremap//完全重定位
    #define Ch1 GPIO_Pin_6//GPIOC
    #define Ch2 GPIO_Pin_7
    #define Ch3 GPIO_Pin_8
    #define Ch4 GPIO_Pin_9
#else
    #define Ch1 GPIO_Pin_6//GPIOA
    #define Ch2 GPIO_Pin_7//GPIOA
    #define Ch3 GPIO_Pin_0//GPIOB
    #define Ch4 GPIO_Pin_1//GPIOB
    #endif
#endif

void GPIO_Tim3PWM(u8 chx) 
{   GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOC,ENABLE);//GPIO时钟
    RCC_APB1PeriphClockCmd(GPIO_AF_TIM2,ENABLE);
	  RCC_APB1PeriphClockCmd(GPIO_AF_TIM3,ENABLE);//使能定时器三时钟
    switch(chx)//chx是要选择的通道号
    {
    case 1:
    GPIO_InitStructure.GPIO_Pin=Ch1;//TIM1_CH1
        break;
    case 2:
    GPIO_InitStructure.GPIO_Pin=Ch2;//TIM1_CH2
        break;
    case 3:
    GPIO_InitStructure.GPIO_Pin=Ch3;//TIM1_CH3
        break;
    case 4:
    GPIO_InitStructure.GPIO_Pin=Ch4;//TIM1_CH4
        break;
    }
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;//复用模式
		GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;//推免输出
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
//根据PWM通道自适应定义引脚
#ifdef Premap
    GPIO_Init(GPIOB,&GPIO_InitStructure);
#else
#ifdef Fremap
    GPIO_Init(GPIOC,&GPIO_InitStructure); 
#else
switch (chx)
  {
  case 1:
      GPIO_Init(GPIOA,&GPIO_InitStructure)
      break;
  case 2:
      GPIO_Init(GPIOA,&GPIO_InitStructure)
      break;
  case 3:
      GPIO_Init(GPIOB,&GPIO_InitStructure)
      break;
  case 4:
      GPIO_Init(GPIOB,&GPIO_InitStructure)
      break;
  }
#endif
#endif
}
//输出引脚重定位，remap为重定位函数，0为无重定位，1为部分重定位，2为全部重定位。
void TIM3PinReMap(u8 remap)
{
    switch (remap)
    {
    case 0:
        break;
    case 1:
		//TIM2输出引脚部分重定位
        break;
    case 2:
    //TIM3输出引脚部分重定位
        break;
    }
}
void TIM_Init(TIM_TypeDef*TIMx,u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_Period=arr-1;//设置自动重装载值
    TIM_TimeBaseStructure.TIM_Prescaler=psc-1;//设置预分频值
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;//设置时钟分割:TIM_CKD_DIV1=0的时候PWM不延时
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;//向上计数模式
    TIM_TimeBaseInit(TIMx,&TIM_TimeBaseStructure);//根据制定的参数初始化TIMx
    //TIM_ARRPreloadConfig(TIMx,DISABLE);
	  //禁止ARR预装载缓冲器
    TIM_ARRPreloadConfig(TIMx,ENABLE);//使能ARR预装载缓冲器
}
void TIM_PWMMode(TIM_TypeDef*TIMx,u8 chx,u8 H2L,u16 pulse)
{
    TIM_OCInitTypeDef TIM_OCInitStructure;
    switch (chx)
    {
    case 1:
        if(H2L)
        TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
    //选择定时器模式,TIM脉冲宽度调制模式1,相等时转换为低
        else
        TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM2;
    //选择定时器模式,TIM脉冲宽度调制模式2,相等时转换为高
        TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;//比较输出使能
        TIM_OCInitStructure.TIM_Pulse=pulse-1;
        TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;//输出极性:TIM输出比较级性高
        TIM_OC1Init(TIMx,&TIM_OCInitStructure);//根据TIM_OCInitStruct中指定的参数初始化外设TIMx
        TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable);//使能TIMx在CCR1上的预装载寄存器
        TIM_CtrlPWMOutputs(TIM1,ENABLE);//设置TIMx的PWM输出为使能
        TIM_ARRPreloadConfig(TIM1,ENABLE);//使能TIMx在ARR上的预装载寄存器
        TIM_Cmd(TIMx,ENABLE);//使能TIMx外设
        break;
    //后文同理
    case 2:
        if(H2L)
        TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
        else
        TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM2;
        TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
        TIM_OCInitStructure.TIM_Pulse=pulse-1;
        TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
        TIM_OC2Init(TIMx,&TIM_OCInitStructure);
        TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Enable);
        TIM_CtrlPWMOutputs(TIM2,ENABLE);
        TIM_ARRPreloadConfig(TIM2,ENABLE);
        TIM_Cmd(TIMx,ENABLE);
        break;
    case 3:
        if(H2L)
        TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
        else
        TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM2;
        TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
        TIM_OCInitStructure.TIM_Pulse=pulse-1;
        TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
        TIM_OC3Init(TIMx,&TIM_OCInitStructure);
        TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);
        TIM_CtrlPWMOutputs(TIM3,ENABLE);
        TIM_ARRPreloadConfig(TIM3,ENABLE);
        TIM_Cmd(TIMx,ENABLE);
        break;
    case 4:
        if(H2L)
        TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
        else
        TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM2;
        TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
        TIM_OCInitStructure.TIM_Pulse=pulse-1;
        TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
        TIM_OC4Init(TIMx,&TIM_OCInitStructure);
        TIM_OC4PreloadConfig(TIM4,TIM_OCPreload_Enable);
        TIM_CtrlPWMOutputs(TIM4,ENABLE);
        TIM_ARRPreloadConfig(TIM4,ENABLE);
        TIM_Cmd(TIMx,ENABLE);
        break;
    }
}

//有关延时函数的延时代码
void delay_nums(u16 time)
{   u16 i=0;
    while(time--)
    {   i=12000;
        while(i--);
    }
}

//主函数
int main(void)
{
    short int kcnt=2000;
    SystemInit();
    GPIO_Tim3PWM(3);
    TIM3PinReMap(2);
    TIM_Init(TIM3,2000,72);
    GPIO_Tim3PWM(4);
    TIM_PWMMode(TIM3,4,0,kcnt);
    TIM_PWMMode(TIM3,4,0,kcnt);

     while (1)
     {
         for(kcnt=2001;kcnt>0;kcnt=kcnt-200)
			 {
         TIM_SetCompare3(TIM3,kcnt);//改变占空比
         TIM_SetCompare3(TIM3,kcnt);
         delay_nums(100);
			 }
         for(kcnt=1;kcnt<=2001;kcnt=kcnt+200)
     {
         TIM_SetCompare3(TIM3,kcnt);
         TIM_SetCompare3(TIM3,kcnt);
         delay_nums(100);
     }
    }
	}
















