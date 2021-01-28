#include <stm32f44x.h>
#define D2_ON GPIO_ResetBits(GPIOC,GPIO_Pin_8)
#define D2_OFF GPIO_SetBits(GPIOC,GPIO_Pin_8)
#define S1_DOWN GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)=0

