/************************************************************************************
*  Copyright (c) 2004,�������ʵ��ӿƼ��������ι�˾
*            All rights reserved.
*
* �ļ����ƣ� Uart.c
* �ļ���ʶ�� none
* ���������� C8051F020
* 
* ժ Ҫ�� ���ļ��Ǵ���0��1�ӳ���ͷ�ļ���ʹ���ⲿ22.1184MHz����. Uart�������򣬰�����ʼ����
*	  ���������ã����ֽڷ��ͽ��ա��ַ������ͽ��ܵȡ���������JP7��JP11�̽ӡ�
* 	  ʹ���ⲿ22.1184MHz����
* ��ǰ�汾��1.0
* �� �ߣ�¬ ��
* ������ڣ�2004��11��14��
*
* ��ʷ�汾��0.9 
* ԭ���� �� ������
* ������ڣ�2004��1��1��
*************************************************************************************/

#define INPUTSIZE  256	// ���뻺����256�ֽ�
#define OUTPUTSIZE 256	// ���������256�ֽ�
		
extern unsigned char m_InputBuf[INPUTSIZE];  /* ���ջ�����Comm_SendFinish:21*/
extern unsigned char m_OutputBuf[OUTPUTSIZE];/* ���ͻ�����*/
extern unsigned char m_SendFirstPos;	  	  /* ���ͻ�����������*/
extern unsigned char m_SendLastPos;	  	  /* ���ͻ�����β����*/
extern unsigned char m_ReceiveFirstPos;	  /* ���ջ�����������*/
extern unsigned char m_ReceiveLastPos;	  	  /* ���ջ�����β����*/
//extern struct	Time	PKTimeNow;

extern unsigned char m_InputBuf11[INPUTSIZE];
extern unsigned char m_ReceiveFirstPos11;
extern	unsigned char m_ReceiveLastPos11;


#define  bool   unsigned char
#define  SYSCLK   22118400      //SYSCLK frequency in Hz
#define DisableUart0	ES0=0
#define EnableUart0		ES0=1
#define BaudRate_1200    1		//1*1200
#define BaudRate_2400    2		//2*1200
#define BaudRate_4800    4		//4*1200
#define BaudRate_9600    8		//8*1200
#define BaudRate_19200   16		//16*1200
#define BaudRate_38400   32		//32*1200
#define BaudRate_57600   48		//48*1200
#define BaudRate_115200  96		//96*1200
#define BaudRate_230400  192		//192*1200

#define RI1  SCON1&0x01
#define TI1  SCON1&0x02

#define WDT_CLOSE   EA=0; WDTCN=0xde; WDTCN=0xad; EA=1;
#define WDT_OPEN    WDTCN = 0xff;
#define WDT_CLR     WDTCN = 0xa5;

/************************************************************************************/
// �����ⲿ��������

void SYSCLK_Init (void);
void PORT_Init (void);

void Uart0_Init(unsigned char BaudRate);
void Uart0_Enable(bool Flag);
unsigned char ReadString(unsigned char* str, unsigned char len);
void Uart0Send(unsigned char ch);
void Uart0Sends(unsigned char *str);
void Uart0_ISR(void);



