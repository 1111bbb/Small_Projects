#include "c8051f020.h"
#include "keydown.h"
#include "delay.h"
#include "lcd.h"

typedef unsigned int u16;	  //���������ͽ�����������
typedef unsigned char u8;

sbit up     = P2^0;
sbit down   = P2^1;
sbit left   = P2^2;
sbit right  = P2^3;
sbit centre = P2^4;
u8 KeyValue=0;
int Set_Begin[16]={0,0,0,0,8},Set_End[16]={0,0,0,0,9};
int flag_page=0,flag_move=0;
extern int Clock[];
extern char code begin_time[],end_time[];//����
extern char code num[],heng[],maohao[],kong[];//�ַ�
extern int bcd_dec(uchar bat);	//BCD��תʮ����


void Key_Move(int page[16])//��ʼor���� ҳ���趨
{
	int i,j;
	if(right == 0)//���� �޸�ʱ��
	{Delay_ms(40);if(right == 0){flag_move++;if(flag_move > 2)flag_move=0;}}
		if(left == 0)//���� �޸�ʱ��
	{Delay_ms(40);if(left ==  0){flag_move--;if(flag_move < 0)flag_move=2;}}
	
		if(flag_move == 0)//ʱ�������޸�
		{
			Delay_ms(80);
			if(up == 0)
			{page[4]++;page[4]=(page[4]>24 ? 0:page[4]);}
			if(down == 0)
			{page[4]--;page[4]=(page[4]<0  ? 24:page[4]);}//����ʱ���޷�
		}
		
		if(flag_move != 0)i=flag_move;	
		if(flag_move == i)
		{
			Delay_ms(80);
			if(up == 0)
			{page[4-i]++;page[4-i]=(page[4-i]>59 ? 0:page[4-i]);}
			if(down == 0)
			{page[4-i]--;page[4-i]=(page[4-i]<0  ? 59:page[4-i]);}//����ʱ���޷�
		}
	
		if(flag_page == 1 || flag_page == 2)//�޸ĳ�ʼʱ��ҳ�� ���ַ���˸
		 {
			 j=flag_move;
				if(flag_move == j)
				{
					display_graphic_8x16(7,(16+8*(3*j)),kong);
					display_graphic_8x16(7,(16+8*(3*j+1)),kong);//ʱ������λ����ʾΪ�գ�ʵ����˸Ч��
					Delay_ms(200);
				}		
		 }		 
}

void Key_setting()
{
	u8 x,y;
	Time_Display();
	if(centre == 0)
	{
		Delay_ms(20);
		flag_page=1;
		if(centre == 0)
		{
			//Set_Begin[4]=(bcd_dec(Clock[4]&0x3f));//ʱ
			//Set_Begin[3]=(bcd_dec(Clock[3]&0x3f));//��
			//Set_Begin[2]=(bcd_dec(Clock[2]&0x7f));//��
			
			//Set_End[4]=(bcd_dec(Clock[4]&0x3f));//ʱ
			//Set_End[3]=(bcd_dec(Clock[3]&0x3f));//��
			//Set_End[2]=(bcd_dec(Clock[2]&0x7f));//��
			Initial_Lcd();
			Delay_ms(200);
			while((flag_page==1))//���ó�ʼ��ˮʱ��
			{
				for(x=0;x<6;x++)
				{
					display_graphic_16x16(1,(8+16*x),&begin_time[x*32]);
				}
				display_graphic_8x16(7,(16+8*0),&num[(Set_Begin[4])/10*16]);
				display_graphic_8x16(7,(16+8*1),&num[(Set_Begin[4])%10*16]);//ʱ
				display_graphic_8x16(7,(16+8*2),maohao);
				display_graphic_8x16(7,(16+8*3),&num[(Set_Begin[3])/10*16]);
				display_graphic_8x16(7,(16+8*4),&num[(Set_Begin[3])%10*16]);//��
				display_graphic_8x16(7,(16+8*5),maohao);
				display_graphic_8x16(7,(16+8*6),&num[(Set_Begin[2])/10*16]);
				display_graphic_8x16(7,(16+8*7),&num[(Set_Begin[2])%10*16]);//��
				if(centre == 0)flag_page=2;//����ҳ��2 �����ý���ʱ��ҳ��
				Key_Move(Set_Begin);//���� ����ʱ��ʱ���ƶ�
			}
			Initial_Lcd();
			Delay_ms(100);
			while((flag_page==2))//���ý�����ˮʱ��
			{
				for(y=0;y<6;y++)
				{
					display_graphic_16x16(1,(8+16*y),&end_time[y*32]);
				}
				display_graphic_8x16(7,(16+8*0),&num[(Set_End[4])/10*16]);
				display_graphic_8x16(7,(16+8*1),&num[(Set_End[4])%10*16]);//ʱ
				display_graphic_8x16(7,(16+8*2),maohao);
				display_graphic_8x16(7,(16+8*3),&num[(Set_End[3])/10*16]);
				display_graphic_8x16(7,(16+8*4),&num[(Set_End[3])%10*16]);//��
				display_graphic_8x16(7,(16+8*5),maohao);
				display_graphic_8x16(7,(16+8*6),&num[(Set_End[2])/10*16]);
				display_graphic_8x16(7,(16+8*7),&num[(Set_End[2])%10*16]);//��
				if(centre == 0)flag_page=0;//��ת�� ʱ����ʾҳ��
				Key_Move(Set_End);//���� ����ʱ��ʱ���ƶ�
			}
			Initial_Lcd();
			Delay_ms(100);
		}
	}
		if(up == 0)KeyValue=1;
		if(down ==0)KeyValue=2;
		if(left == 0)KeyValue=3;
		if(right == 0)KeyValue=4;
		if(centre == 0)KeyValue=5;
}


