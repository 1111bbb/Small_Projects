/************************ �Զ��幫��ͷ�ļ� **************************************/

#ifndef _PBDATA_H//�궨�壬�����ļ�����
#define _PBDATA_H
#include "stm8s.h"//����STM8��ͷ�ļ�
#include <stdio.h>//��Ҫ�������ͷ�ļ�����ʵ��
#include "math.h"//��Ҫ�������ͷ�ļ�����ʵ��
#include "stm8s_tim1.h"

#include "led.h"  //����LEDͷ�ļ�
#include "uart.h"
#include "i2c.h"
#include "pcf8563.h"
#include "oled.h"



typedef enum {//ʱ�䶨��ö��
  sec,
  min,
  hour,
  day,
  week,
  moon,
  year
}RTC_INDEX_e;

typedef enum{
  NONE ,
  OUT , 
  IN ,
}IrDA_STATUS_e;//����Թ�״̬
void delay_us(u16 nCount); //΢����ʱ����
void delay_ms(u16 nCount); //������ʱ����
u16 Get_decimal(double dt,u8 deci);   //�����ֵС������
void Configuration_Init(void); //Ӳ�����ó�ʼ��
#endif //�����ļ����ƽ���


/************************ ��̳��ַ www.zxkjmcu.com ******************************/