#include "hc05.h"	
#include "string.h"
#include "delay.h"
#include "oled.h"

extern int mode;

void uart3_init(u32 Bound)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStruct;
    NVIC_InitTypeDef NVIC_InitStructure;    //定义串口初始化结构体
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3 , ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB	, ENABLE); //开时钟
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);    
    /* Configure USART3 Rx (PB.11) as input floating 浮点输入模式*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

	  USART_InitStruct.USART_BaudRate = Bound;
	  USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //没有硬件流
	  USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	  USART_InitStruct.USART_Parity = USART_Parity_No;
	  USART_InitStruct.USART_StopBits = USART_StopBits_1;
	  USART_InitStruct.USART_WordLength = USART_WordLength_8b;
		
	  USART_Init(USART3, &USART_InitStruct);
	  
      USART_Cmd(USART3, ENABLE);
	  
	  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//使能接收中断
	  
	      //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;	 
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//3和3
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	  NVIC_Init(&NVIC_InitStructure);       //串口中断初始化
	  
}

void USART3_IRQHandler(void) 
{
	u8 Bluetooth_data;
	if(USART_GetITStatus(USART3,USART_IT_RXNE)!=RESET)//接收中断标志位拉高
	{
		Bluetooth_data=USART_ReceiveData(USART3);//保存接收的数据
		
		switch(Bluetooth_data){
			case 0x00: mode = 0 ;break; 
			case 0x01: mode = 1  ;break;
		}
	}
}

//一个
void USART3_Send_Data(char data)
{
	USART_SendData(USART3,data);
	while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=1);
}

//一串
void USART3_Send_String(char *String)
{
	u16 len,j;
	
	len=strlen(String);
	for(j=0;j<len;j++)
	{
		USART3_Send_Data(*String++);
	}
}
