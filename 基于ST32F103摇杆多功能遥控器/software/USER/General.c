#include "include.h"

u8 run_flag =0;  //1Ϊ����ģʽ
u8 mode_flag=0;  //

u8 Remote1_X=0,Remote1_Y=0;
u8 Remote2_X=0,Remote2_Y=0;

u8 CMD[6]={0};
u8 SBuff[4]={0};
u8 check_byte=0;
u8 temp=0;
float AD_temp=0;

u8 page_num=0;
u8 speed=140;
u8 send_flag=0;





void CMD_Send()
{
	check_byte = 0xaa+0x55+0x07+CMD[0]+CMD[1]+CMD[2]+CMD[3]+CMD[4]+CMD[5];
	USART_SendData(USART1,0xaa);
	USART_SendData(USART1,0x55);
	USART_SendData(USART1,0x07);  //���ݳ��ȣ����ֽڿ۳���ʼλ��У��λ���������ݳ���λ
	USART1_Sends(CMD,sizeof(CMD));  //���Ϳ�������
	USART_SendData(USART1,check_byte);  //����У���ֽ�
	CMD[5] = 0;
}
