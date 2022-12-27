#include "HCSR501.h"

void HCSR501_init(void){

	GPIO_InitTypeDef GPIO_TypeHCSR501_init;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //ʹ�� PB
	
	GPIO_TypeHCSR501_init.GPIO_Pin = GPIO_Pin_15; //PB.15
	GPIO_TypeHCSR501_init.GPIO_Mode = GPIO_Mode_IPD; //��������
	GPIO_TypeHCSR501_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_TypeHCSR501_init);
	
	PBout(15) = 0; //
}

