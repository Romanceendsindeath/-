#include "delay.h"
#include "string.h"	
#include "oled.h"
#include "sys.h"
#include "MQ2.h"
#include "BEEP.h"
#include "HCSR501.h"
#include "HC05.h"
#include "usart.h"
#include "DS180b20.h"

int mode = 0;

int main(){
	
u16 ad = 0;
float wendu = 0;

	NVIC_Configuration();		//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart3_init(9600);
	delay_init(); 			//延时函数初始化
	ADC_Pin_Init();			//初始化MQ2
	DS18B20_Init();
	BEEP_init();			//初始化蜂鸣器
	HCSR501_init();			//初始化人体红外
	OLED_Init();			//初始化OLED  
	OLED_Clear();

	while(1)    
	{

if( mode == 0 ){
		int c=1;
		ad = ADC_Trans();
		wendu =	DS18B20_GetTemp();

		OLED_MMOL();		//浓度显示	
		OLED_STATE();		//状态显示:正常
		OLED_ShowNum(40,2,ad,3,16);//显示浓度的值
		OLED_ShowNum(80,2,wendu,2,16);//显示温度的值
			
		BEEP_mode = 1;

		while(ad>=400){
			if(c==1){
				OLED_Clear();
				c=0;
			}
			BEEP_mode=0;	
			OLED_STATE1();	//状态显示：异常
			ad = ADC_Trans();  //继续读取浓度值
		}
		while(wendu>=37){
			if(c==1){
				OLED_Clear();
				c=0;
			}
			BEEP_mode=0;
			OLED_STATE1();	//状态显示：异常
			ad = ADC_Trans();  //继续读取浓度值
		}
		}
		delay_ms(1000);
if(mode == 1){  //防盗模式
	
		if(HCSR501_MODE == 1){
			BEEP_mode = 0;
			OLED_STATE1();
			delay_ms(3000);
			USART3_Send_String("********Your car is in danger！********");
		}else
		BEEP_mode = 1;
		OLED_STATE();
		}
	}
}


