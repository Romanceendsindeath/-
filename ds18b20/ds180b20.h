/**
  ******************************************************************************
  * @file    DS180b20.h
  * @author  hhy/wattercutter
  * @date    2020/1/20
  * @brief   DS18B20����
	
	* @UpdateTime 
			2021/1/20 hhy/wattercutter
  ******************************************************************************
*/ 

#ifndef _DS180B20_H
#define _DS180B20_H
#include <stm32f10x.h>
#include "timer.h"
#include "delay.h"
#include "sys.h"
/* DQ������غ궨�� */
#define GPIODQ GPIOB
#define PINDQ GPIO_Pin_7
#define DQ_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO�˿�ʱ�� */
/* DQ��ƽ������ */
#define DQ_H GPIO_SetBits(GPIODQ,PINDQ)
#define DQ_L GPIO_ResetBits(GPIODQ,PINDQ)
/* DS18B20��ָ��� */
#define CONVERTT 0x44
#define READSCRATCHPAD 0xbe
#define WRITESCRATCHPAD 0x4e
#define COPYSCRATCHPAD 0x48
#define RECALLEE 0xb8
#define READPOWERSUPPLY 0xb4

void DS18B20_DQGPIOConfig(void);
void DS18B20_Init(void);
void DS18B20_Rst(void);
uint8_t DS18B20_ReadByte(void);
void DS18B20_WriteBye(uint8_t data);
float DS18B20_GetTemp(void);

#endif
