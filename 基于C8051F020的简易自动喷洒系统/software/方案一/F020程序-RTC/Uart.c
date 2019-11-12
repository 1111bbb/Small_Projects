#include "c8051F020.h"
#include "uart.h"
#include "delay.h"
#include "intrins.h"
/************************************************************************************/

/************************************************************************************
// ������ȫ�ֱ�������
*************************************************************************************/


/************************************************************************************
// ������ȫ�ֱ�������
*************************************************************************************/
//#define INPUTSIZE  256	// ���뻺����256�ֽ�
//#define OUTPUTSIZE 256	// ���������256�ֽ�
		
	unsigned char m_InputBuf[INPUTSIZE];  /* ���ջ�����Comm_SendFinish:21*/
	unsigned char m_OutputBuf[OUTPUTSIZE];/* ���ͻ�����*/
	unsigned char m_SendFirstPos;	  	  /* ���ͻ�����������*/
	unsigned char m_SendLastPos;	  	  /* ���ͻ�����β����*/
	unsigned char m_ReceiveFirstPos;	  /* ���ջ�����������*/
	unsigned char m_ReceiveLastPos;	  	  /* ���ջ�����β����*/
	volatile unsigned char m_SendOver;

/************************************************************************************
*  Uart0�ӳ���
*************************************************************************************/
/***********************************************************************************
* �������ƣ�Uart0_Init;
*
* ��������������Uart0��ʼ��;
*              
* ���������unsigned char���ͣ��������ݲ�����;
*
* �������ݣ�none��
*
* ע�⣺    none;
************************************************************************************/

void Uart0_Init(unsigned char BaudRate) //Uart0��ʼ��        
{                                    
	TR1=0;                              // �رն�ʱ��Timer1
	ET1=0;                              // �رն�ʱ��Timer1�ж� 
	PT1=0;                              // �رն�ʱ��Timer1�ж�����Ȩ
	TMOD&= 0x0f;                        // TMOD: ��ʱ��1, ģʽ2, 8λ���� 
	TMOD|= 0x20;                        // TMOD: ��ʱ��1, ģʽ2, 8λ���� 
  SCON0  = 0x50;                      // SCON0: ģʽ1, 8λUART, ʹ��RX
  PCON  |= 0x80;                      // SMOD00 = 1
	if (BaudRate>=BaudRate_4800)
	{
	 	CKCON |= 0x10;                             // ��ʱ��Timer1ʹ��ϵͳʱ����Ϊʱ���׼
	 	TH1    = -(SYSCLK/1200/(BaudRate*16));     // ���ö�ʱ��Timer1����ֵ
	}
	else
	{
		CKCON &= ~0x10;                               // ��ʱ��Timer1ʹ��ϵͳʱ����Ϊʱ���׼
	 	TH1    = -(SYSCLK/1200/(BaudRate*16*12));     // ���ö�ʱ��Timer1����ֵ
	}
		ES0=0;             				 // �رմ���Uart0�ж�
		PS=0;             				 // �رմ���Uart0�ж�����Ȩ
	  TI0  = 1;                  // Indicate TX0 ready
    RI0  = 0;                  // Indicate RX0 ready
    TR1=1;							 // �򿪴���Uart0
    RI0=0;
		TI0=0;
    ES0=1;
    m_ReceiveLastPos=m_ReceiveFirstPos=0;
		m_SendFirstPos=m_SendLastPos=0;	  	  /* ���ͻ�����������*/	
}

/***********************************************************************************
* �������ƣ�Uart0_Enable;
*
* ��������������Uart0��ʼ��;
*              
* ���������bool���ͣ�������1���ر�����0;
*
* �������ݣ�none��
*
* ע�⣺    none;
************************************************************************************/

void Uart0_Enable(bool Flag)
{
    PS=1;
	//PT0=0;
	if (Flag)
		TR1=1;   // �򿪴���Uart0
	else
        TR1=0;   // �رմ���Uart0
}



/***********************************************************************************
* �������ƣ�GetReciLen;
*
* ��������������Uart0���մ������ݳ��ȼ���;
*              
* ���������none;
*
* �������ݣ�unsigned char���ͣ����пڽ������ݳ���Ϊm_ReceiveLastPos-m_ReceiveFirstPos��
*
* ע�⣺    none;
************************************************************************************/

unsigned char GetReciLen(void)
{
//	WDTCN=0xA5;
	return(m_ReceiveLastPos-m_ReceiveFirstPos);
}

/***********************************************************************************
* �������ƣ�ReadString;
*
* ��������������Uart0���մ�������;
*              
* ���������unsigned char* str�������ݷ���Ŀ�����飬unsigned char len�������ݳ���;
*
* �������ݣ�unsigned char���ͣ�ʵ���Ͻ��յ������ݸ�����
*
* ע�⣺    none;
************************************************************************************/
unsigned char ReadString(unsigned char* str, unsigned char len)
{
	register unsigned char i, j;
	j=GetReciLen();
	if(j>len)
		j=len;
	for(i=0; i<j; i++)
	{
		str[i]=m_InputBuf[m_ReceiveFirstPos++];
	//	WDTCN=0xA5;
	}
	return i;
}


void Uart0Send(unsigned char ch)
{
	SBUF0=ch;							//���뻺����
	while (TI0 == 0);     //�ȴ��������
  TI0=0;                // ����
}

void Uart0Sends(unsigned char *str)
{
	while(*str!='\0')
	{
		SBUF0=*str;
		str++;
		while (TI0 == 0);     // Wait for the transmit to complete
    TI0=0;                // Clear TI1
	}
}

void Uart0_ISR(void) interrupt 4 using 1
{
	if(RI0)
	{
		RI0=0;   // ���RI0��־λ
	  m_InputBuf[m_ReceiveLastPos++]=SBUF0;
	}
	else 
	{
		TI0=0;	
		if(m_SendFirstPos!=m_SendLastPos)
		{
	 		SBUF0=m_OutputBuf[m_SendFirstPos];
			m_SendFirstPos++;
		}
		else
		{
			m_SendOver = 1;
		}
	}
}


