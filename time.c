//有关延时函数的延时代码
void delay_nums(u16 time)
{   u16 i=0;
    while(time--)
    {   i=12000;
        while(i--)
    }
}

//有关SysTick中断延时
//stm3210x_it.h
extern_IO uint32_t TimingDealay;
//stm32f40x_it.c定义中断函数
void SysTick_Handler(void)
    {
    if(TimingDealay !=0x00)
    {
            TimingDealay--;
    }
}
//mian.c定义函数和全局变量
void Init_SysTick(void)
{
    if(SysTick_Config(SystemCoreClock/1000))//1ms的时间基准
    while(1)
}
//延时函数
_IO uint32_t TimingDealay;
void dealay_ms(_IO uint32_t nTime)
{
    TimingDealay = nTime;
    while(TimingDealay!=0);
}

//有关定时器中断延时
//前期操作：1）由于使用了TIMx所以将#inclde stm32f40x_tim.h使用
//stm32f40x_it.c加入中断函数
void TIM3_IROHandler(void)
{
    if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET)
    //检查TIM中断是否发生
    {
        TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
        //清除中断待处理位：TIM中断源
        i++;
        //外部全局变量1s点亮1s关闭
        if(i==1000)
        {
            LED0_ON;
        }
        if(i=2000)
        {
            LED0_OFF;
            i=0;
        }
    }
}
//stm32f40x_it.h加入
extern u16 i;//外部变量说明，在主函数致中定义，在中断函数中使用
void TIM3_IROHandler(void);//TIM3中断函数说明

