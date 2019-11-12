#include "include.h"

extern u8 Remote1_X,Remote1_Y;
extern u8 Remote2_X,Remote2_Y;

extern u8 run_flag;  //1Ϊ����ģʽ
extern u8 mode_flag;  //
extern u8 Remote1_X,Remote1_Y;
extern u8 Remote2_X,Remote2_Y;
extern u8 CMD[6];
void TIM3_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(  //ʹ�ܻ���ʧ��ָ����TIM�ж�
			TIM3, //TIM2
			TIM_IT_Update ,
			ENABLE  //ʹ��
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	TIM_Cmd(TIM3, DISABLE);          //��ֹTIMx����
							 
}
void TIM3_IRQHandler(void)   //TIM3�ж�
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
	{

			KYE1_SHOW();
			KYE2_SHOW();
	
			Remote1_X = Get_Adc_Value(ADC_Channel_10);  //��Y   --->A4 /  ͨ��4   
			Remote1_Y = Get_Adc_Value(ADC_Channel_11);  //��X   --->A5 /  ͨ��5   	
			Remote2_X = Get_Adc_Value(ADC_Channel_13);  //��X   --->A7 /  ͨ��7  
			Remote2_Y = Get_Adc_Value(ADC_Channel_12);  //��Y   --->A6 /  ͨ��6  
			CMD[0]=run_flag;    //������־λ
			CMD[1]=Remote1_Y;   //ǰ��
			//CMD[2]=mode_flag;		//״̬��־λ
			if(mode_flag==0){CMD[3]=Remote2_X;}//����
			else{CMD[3]=Remote2_Y;}//����
			CMD[4]=Remote1_X;   //ץȡ�ͷ�
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );   //���TIMx���жϴ�����λ:TIM �ж�Դ

	}
}
