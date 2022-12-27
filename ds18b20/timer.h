/**
  ******************************************************************************
	* @project ��Яʽ���ʵ��վ
  * @file    timer.h
  * @author  hhy/wattercutter
  * @date    2020/1/19
  * @brief   ��ʱ�������
	
	* @UpdateTime 
			2021/1/19 hhy/wattercutter
  ******************************************************************************
*/ 

#ifndef _TIMER_H
#define _TIMER_H
#include <stm32f10x.h>

void Timer_InitConfig(void);
void Decre_TIMERTICVAL(void);
void Timer_DelayUs(int us);

void Delay_Timer_Init(void);
void Delay_us(uint32_t us_cnt);

#endif
