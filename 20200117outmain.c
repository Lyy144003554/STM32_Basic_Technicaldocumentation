//接哪
//D2——PC8（推免输出）
//D4——PC9（推免输出）
//D6——PA8（开漏输出）
//D7——PA11（开漏输出）
//D8——PA12（开漏输出）
//输出的方式和端口
void LED_GPIO_Config(void)
{
	GPIO_InitTypeDefGPIO_InitStructure;
    PCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//使C端时钟开始
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_9;//选择引脚
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT_PP;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10Mhz;//初始速度
    GPIO_Init(GPIOC,&GPIO_InitStructure);//初始化C端口

    PCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使A端时钟开始
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_11|GPIO_Pin_12//选择引脚
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT_OD;//开漏输出
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10Mhz;//初始速度
    GPIO_Init(GPIOA,&GPIO_InitStructure);//初始化C端口
}   

//有关延时函数的延时代码
void delay_nums(u16 time)
{   u16 i=0;
    while(time--)
    {   i=12000;
        while(i--)
    }
}

//LED的初始状态
void TurnOffALLled(void)
{
    D2_OFF;
    D4_OFF;
    D6_OFF;
    D7_OFF;
    D8_OFF;
}

//主函数
int main(void)
{
    SystemInit();//篇日志系统时钟为72Mhz，这个步骤是可以省略的
    LED_GPIO_Config();//GPIO 端口初始化
    TurnOffALLled();//关灯
    while(1)
    {
        D2_ON;
        delay_nums(1000);
        D2_OFF;
        delay_nums(1000);
        D4_ON;
        delay_nums(1000);
        D4_OFF;
        delay_nums(1000);
        D6_ON;
        delay_nums(1000);
        D6_OFF;
        delay_nums(1000);
        D7_ON;
        delay_nums(1000);
        D7_OFF;
        delay_nums(1000);
        D8_ON;
        delay_nums(1000);
        D8_OFF;
        delay_nums(1000);
        //开关开关开关开关（有输出方式的区别）
    }
}