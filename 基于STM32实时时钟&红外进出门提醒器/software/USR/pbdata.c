#include "pbdata.h"   //�����Զ��幫��ͷ�ļ�

/*********************************************************************************
*   �� �� ��: delay_us
*   ����˵��: ΢����ʱ����ע��˺��������л���Ϊ(16Mʱ���ٶ�)
*   ��    �Σ�nCountҪ��ʱ��΢����������nCount=1΢��
*   �� �� ֵ: ��
*********************************************************************************/
void delay_us(u16 nCount)   //16M ����ʱ  ��ʱ 1��΢��
{
    nCount*=3;//��ͬ�� nCount=nCount*3  �൱�ڰ�nCount��������3��
    while(--nCount);//nCount������ֵ�ȼ�һ�����ж�nCount����ֵ�Ƿ����0������0ѭ����һ������0�˳�ѭ����
}

/*********************************************************************************
*   �� �� ��: delay_ms
*   ����˵��: ������ʱ����ע��˺��������л���Ϊ(16Mʱ���ٶ�)
*   ��    �Σ�nCountҪ��ʱ�ĺ�����������nCount=1����
*   �� �� ֵ: ��
*********************************************************************************/
void delay_ms(u16 nCount)  //16M ����ʱ  ��ʱ 1������
{
    while(nCount--)//���ж�while()ѭ�������nCount��ֵ�Ƿ����0������0ѭ������һִ��ѭ���壬����0�˳�ѭ����
    {
        delay_us(1000);//����΢����ʱ����������1000������ʾ1���롣
    }
}



void Configuration_Init(void)//Ӳ�����ó�ʼ��
{  
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);//ʱ���ٶ�Ϊ�ڲ�16M��1��Ƶ��

  GPIO_Init(GPIOA, GPIO_PIN_1, GPIO_MODE_OUT_PP_HIGH_SLOW);//����Թ�1
  GPIO_Init(GPIOA, GPIO_PIN_2, GPIO_MODE_OUT_PP_HIGH_SLOW);//����Թ�1
  GPIO_Init(GPIOA, GPIO_PIN_3, GPIO_MODE_OUT_PP_HIGH_SLOW);//LED
  
  GPIO_Init(GPIOC, GPIO_PIN_7, GPIO_MODE_OUT_PP_HIGH_SLOW);//KEY1
  I2C_Configuration();
  PCF8563_Init();
  
  OLED_Init();
  OLED_Clear();
  Uart_Init();
  
  TIM1_TimeBaseInit(16,TIM1_COUNTERMODE_UP,1000,0);//16��Ƶ    1M/1000=1000
  TIM1_ARRPreloadConfig(ENABLE);
  TIM1_ITConfig(TIM1_IT_UPDATE , ENABLE);
  TIM1_Cmd(ENABLE);
  __enable_interrupt();//�����ж�
  
  for(u8 i=0;i<5;i++)//OLED��ʾ��ǰ����
  {
      OLED_ShowCHinese(0+16*i,6,8+i);
  }
  OLED_ShowString(80,6,":");
}


