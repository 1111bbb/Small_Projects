#include "include.h"



void Perpheral_Init(void)                         //���������Χ��ʼ��
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2
	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
	KEY_Init();          	//��ʼ���밴�����ӵ�Ӳ���ӿ�
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�

 	Adc_Init(GPIO_Pin_0);		  		//ADC��ʼ��	  
 	Adc_Init(GPIO_Pin_1);		  		//ADC��ʼ��	
 	Adc_Init(GPIO_Pin_2);		  		//ADC��ʼ��	  
 	Adc_Init(GPIO_Pin_3);		  		//ADC��ʼ��		 
	TIM3_Int_Init(1000,7199);                       //10Khz�ļ���Ƶ�ʣ�������5000Ϊ500ms
	OLED_Init();
	
}




