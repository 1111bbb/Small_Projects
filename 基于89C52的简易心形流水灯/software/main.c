/**************************************************************************************
*		              ������һ��LEDʵ��												  *
ʵ���������س����D1ָʾ�Ƶ���
ע�������																				  
***************************************************************************************/


#include "reg52.h"			 //��????t?D?����?��?�̣�???����?��?D?��?��a1|?��??��??��



typedef unsigned int uint;	  //??��y?Y����D��??DD����?��?����?
typedef unsigned char uchar;
sbit k1=P3^0;
sbit k2=P3^1;
sbit k3=P3^2;
sbit beepIO=P3^7;
uchar code table0[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};//LED�ӵ�λ����λ��
uchar code table1[]={0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};//LED�Ӹ�λ����λ��
uchar code table2[]={0xfe,0xfc,0xf8,0xf0,0xe0,0xc0,0x80,0x00};//LED��1������8��������(�ӵ�λ����λ)
uchar code table3[]={0x7f,0x3f,0x1f,0x0f,0x07,0x03,0x01,0x00};//LED��1������8��������(�Ӹ�λ����λ)
uchar code table4[]={0x00,0x01,0x03,0x07,0x0f,0x1f,0x3f,0x7f,0xff};//LED��8��ȫ����һ��������(�ӵ�λ����λ)
uchar code table5[]={0x00,0x80,0xc0,0xe0,0xf0,0xf8,0xfc,0xfe,0xff};//LED��8��ȫ����һ��������(�Ӹ�λ����λ)
uchar code table6[]={0xfe,0xfc,0xfa,0xf6,0xee,0xde,0xbe,0x7e};//LED�ӵ�λ����λ��(���λʼ��Ϊ0)
uchar code table7[]={0x7f,0x3f,0x5f,0x6f,0x77,0x7b,0x7d,0x7e};//LED�Ӹ�λ����λ��(���λʼ��Ϊ0)
uchar code table8[]={0x7e,0xbd,0xdb,0xe7}; //�������м�һ��һ����
uchar code table9[]={0x7e,0x3c,0x1e,0x00};  //�������м��𽥶�����
uchar code table10[]={0xe7,0xc3,0x81,0x00};  //�м��������𽥶�����
uchar code table11[]={0x18,0x3c,0x7e,0xff};  //�м������ߴ�ȫ���𽥶�����
uchar code table12[]={0xe0,0xc0,0x80,0x00};  //P1���ȫ�����ұߴӵײ���ʼһ��һ����ֱ��ȫ��
uchar code table13[]={0x07,0x03,0x01,0x00};  //P1�ұ�ȫ������ߴӵײ���ʼһ��һ����ֱ��ȫ��
uchar code table14[]={0x80,0xc0,0xe0,0xf0};  //P1���ȫ�������ұ߿�ʼȫ��ֱ��ȫ��
uchar code table15[]={0xef,0xcf,0x8f,0x0f};  //P1���ȫ���ұߴӵײ���ʼһ��һ����ֱ��ȫ��
uchar code table16[]={0x0e,0x0c,0x08,0x00};  //P1�ұ�ȫ��������߿�ʼ���ײ�һ��һ����ֱ��ȫ��
uchar code table17[]={0x10,0x30,0x70,0xf0};  //P1���ȫ�������ұ߿�ʼȫ��ֱ��ȫ��
uchar code table18[]={0x1f,0x3f,0x7f,0xff};  //P1�ұ�ȫ����ߴӿ�ʼһ��һ����ֱ��ȫ�� 
uchar i,j;		//����ѭ������
uchar m,n; 
uint cycle=500,high,low;
uchar code T[49][2]={{0,0},
{0xF8,0x8B},{0xF8,0xF2},{0xF9,0x5B},{0xF9,0xB7},{0xFA,0x14},{0xFA,0x66},{0xFA,0xB9},{0xFB,0x03},{0xFB,0x4A},{0xFB,0x8F},{0xFB,0xCF},{0xFC,0x0B},
{0xFC,0x43},{0xFC,0x78},{0xFC,0xAB},{0xFC,0xDB},{0xFD,0x08},{0xFD,0x33},{0xFD,0x5B},{0xFD,0x81},{0xFD,0xA5},{0xFD,0xC7},{0xFD,0xE7},{0xFE,0x05},
{0xFE,0x21},{0xFE,0x3C},{0xFE,0x55},{0xFE,0x6D},{0xFE,0x84},{0xFE,0x99},{0xFE,0xAD},{0xFE,0xC0},{0xFE,0x02},{0xFE,0xE3},{0xFE,0xF3},{0xFF,0x02},
{0xFF,0x10},{0xFF,0x1D},{0xFF,0x2A},{0xFF,0x36},{0xFF,0x42},{0xFF,0x4C},{0xFF,0x56},{0xFF,0x60},{0xFF,0x69},{0xFF,0x71},{0xFF,0x79},{0xFF,0x81}
};
uchar code music[][2]={{0,4},
{0,4},{24,4},{24,4},{21,4},{19,4},{21,4},{14,8},{19,4},{21,4},{24,4},{21,4},{19,16},{0,4},{24,4},{24,4},{21,4},{19,4},{21,4},{12,8},{19,4},{21,4},{24,4},{19,4},{17,16},{0,4},{17,4},{19,4},{21,4},
{24,4},{26,4},{24,4},{22,4},{24,4},{21,4},{21,4},{19,4},{19,16},{0,4},
{17,4},{19,4},{17,4},{17,4},{19,4},{17,4},{19,4},{19,4},{21,8},{24,4},{21,4},{21,12},{0,4},{24,4},{24,4},{21,4},{19,4},{21,4},{14,8},{19,4},{21,4},{24,4},{21,4},{19,16},{0,4},{24,4},{24,4},{21,4},
{19,4},{21,4},{12,8},{19,4},{21,4},{24,4},{19,4},{17,16},{0,4},{17,4},{19,4},{21,4},{24,4},{26,4},{24,4},{22,4},{24,4},{21,4},{21,4},{19,4},{19,12},{12,4},{21,8},{19,4},{19,8},{17,16},
{0xFF,0xFF}};


void delay1(uchar p)
{
uchar i,j; 
for(;p>0;p--)
for(i=181;i>0;i--)
for(j=181;j>0;j--);
}
void delay2(uint i)
{
	while(i--);
}

void pause()
{
uchar i,j;
for(i=150;i>0;i--)
for(j=150;j>0;j--);
}


void T0_int() interrupt 1
{
P0=P2=0Xc3;
P1=0X81;
beepIO=!beepIO;
TH0=T[m][0]; TL0=T[m][1];
P2=P1=P0=0XFF;
}






void delay(uint time)	//��ʱ����
{
	uint x,y;
	for(x=time;x>0;x--)
	for(y=110;y>0;y--);
}
void disp0()			//״̬0 ����LED��˸3��
{
	for(i=0;i<3;i++)
	{
		P2=0x00; P1=0x00; P0=0x00; 
		delay(300);
		P0=0xff; P2=0xff; P1=0xff;
		delay(300);
	}
}

void disp1()			//״̬1 LED˳ʱ��תһȦ
{
	for(i=0;i<8;i++)
	{
		P2=table1[i];
		delay(50);
	}
	P2=0xff;
	for(i=0;i<8;i++)
	{
		P1=table1[i];
		delay(50);
	}
	P1=0xff;
	for(i=0;i<8;i++)
	{
		P0=table0[i];
		delay(50);
	}
	P0=0xff;
}

void disp2()			//״̬2 LED��ʱ��תһȦ
{
	for(i=0;i<8;i++)
	{
		P0=table1[i];
		delay(50);
	}
	P0=0xff;
	for(i=0;i<8;i++)
	{
		P1=table0[i];
		delay(50);
	}
	P1=0xff;
	for(i=0;i<8;i++)
	{
		P2=table0[i];
		delay(50);
	}
	P2=0xff;
}

void disp3()			//״̬3 3��LEDͬʱ˳ʱ����ʱ���ƶ�1/3Ȧ
{
	for(i=0;i<8;i++)
	{
		P0=table1[i];
		P1=table0[i];
		P2=table0[i];		
		delay(100);
	}
	for(i=0;i<8;i++)
	{
		P0=table0[i];
		P1=table1[i];
		P2=table1[i];
		delay(100);
	}
	P0=0xff;P1=0xff; P2=0xff; 
}

void disp4()			//״̬4  
{
	for(i=0;i<12;i++)
	{
		if(i<8)
		{
			P0=table1[i];
			P2=table1[i];
		}
		else
		{
			P0=0xff; P2=0xff;
		 	P1=table8[i];
		}	
		delay(100);
	}
		P1=0xff;	
}
void disp5()			//״̬5 
{
	for(i=0;i<12;i++)
	{
		if(i<4)
		{
			P1=table8[3-i];	
		}
		else
		{
			P1=0xff;
			P0=table0[i];
			P2=table0[i];
		}	
		delay(100);
	}
		P0=0xff; P2=0xff;	
}
void disp6()			//״̬6 LED���϶����𽥵���(һ�����һ�벻��)
{
	for(i=0;i<8;i++)
	{
		P0=table3[i];
		P2=table3[i];
		delay(100);
	}
	P0=0xff; P2=0xff;
	for(i=0;i<4;i++)
	{
		P1=table9[i];		
		delay(100);
	}
	P1=0xff;
}

void disp7()			//״̬7 LED���¶����𽥵���(ֱ��ȫ������)
{
	for(i=0;i<4;i++)
	{
		P1=table9[i];
		delay(100);
	}
	for(i=0;i<8;i++)
	{
		P0=table2[i];
		P2=table2[i];
		delay(100);
	}
}

void disp10()			//״̬10 ��LEDȫ������ȫ����(���8���3��LED��ʼ��ʱ��Ϩ��)
{
	for(i=0;i<9;i++)
	{
		P0=table5[i];
		P2=table4[i];
		P1=table4[i];
		delay(100);
	}
	delay(300);
}

void disp11()			//״̬11 ���8���3��LED����˳ʱ����ת
{
	for(j=0;j<2;j++)
	{
		for(i=0;i<8;i++)
		{
			P0=table0[i];
			P2=table1[i];
			P1=table1[i];
			delay(100);
		}
		P0=0xff; P2=0xff; P1=0xff;
		for(i=0;i<8;i++)
		{
			P0=table0[i];
			P2=table1[i];
			P1=table1[i];
			delay(100);
		}
		P0=0xff; P2=0xff; P1=0xff; 
	}
}

void disp12()			//���8���3��LED����Ȼ��˳ʱ���𽥵���(ֱ��ȫ������)
{
	for(i=0;i<8;i++)
	{
		P0=table2[i];
		P2=table3[i];
		P1=table3[i];
		delay(100);
	}
	delay(1000);
}

void disp13()			//״̬13 ��LEDȫ������ȫ����(���8���3��LED��ʼ˳ʱ��Ϩ��)
{
	for(i=0;i<8;i++)
	{
		P0=table4[i];
		P2=table5[i];
		P1=table5[i];
		delay(100);
	}
	delay(300);
}

void disp14()			//״̬14 ��LED������ȫ��(��P0.0��P1.0��P1.7��P2.0��ʼ�𲽵���)
{
	for(i=0;i<8;i++)
	{
		P0=table2[i];
		P2=table2[i];
		if(i<4)
		{
			P1=table8[i];
		}		
		delay(100);
	}
}

void disp15()			//״̬15 ��LEDȫ����ȫ����(��P0.7��P1.3��P1.4��P2.7��ʼ��Ϩ��)
{
	for(i=0;i<8;i++)
	{
		P0=table5[i];
		P2=table5[i];
		if(i<4)
		{
			P1=table11[i];
		}		
		delay(100);
	}
}

void disp16()			//״̬16 LED�ƽ�����˸(Ƶ���������)
{
	for(i=0;i<5;i++)
	{
		P0=0xaa; P1=0x55; P2=0xaa;
		delay(100);
		P0=~P0; P1=~P1; P2=~P2; 
		delay(100);
	}
	for(i=0;i<5;i++)
	{
		P0=0xaa; P1=0x55; P2=0xaa;
		delay(200);
		P0=~P0; P1=~P1; P2=~P2;
		delay(200);
	}
	for(i=0;i<5;i++)
	{
		P0=0xaa; P1=0x55; P2=0xaa;
		delay(300);
		P0=~P0; P1=~P1; P2=~P2;
		delay(300);
	}
	P0=0xff; P2=0xff; P1=0xff; 
	delay(300);
}

void disp17()  //״̬17 LED��P0.7��ʼ��ʱ���𲽵���,�����ٶȻ������
{
	for(i=0;i<4;i++)
	{
		P1=table3[3-i];	
		delay(100);
	}
	for(i=0;i<8;i++)
	{
		P0=table2[i];
		delay(100);
	}
	for(i=0;i<4;i++)
	{
		P1=table12[i];	
		delay(100);	
	}
	for(i=0;i<8;i++)
	{
		P2=table2[i];
		delay(100);
	}
	P0=0xff; P1=0xff; P2=0xff;
/************��ѭ��һ��****************/
for(i=0;i<4;i++)
	{
		P1=table3[3-i];	
		delay(50);
	}
	for(i=0;i<8;i++)
	{
		P0=table2[i];
		delay(50);
	}
	for(i=0;i<4;i++)
	{
		P1=table12[i];	
		delay(50);	
	}
	for(i=0;i<8;i++)
	{
		P2=table2[i];
		delay(50);
	}
	P0=0xff; P1=0xff;P2=0xff;
			
}

void disp19()			//״̬19 LED��P2.7��ʼ˳ʱ���𲽵���,(ѭ��2��)�����ٶȻ������
{
	for(i=0;i<8;i++)
	{
		P2=table3[i];
		delay(100);
	}
	for(i=0;i<4;i++)
	{
		P1=table3[i];
		delay(100);
	}	
	for(i=0;i<8;i++)
	{
		P0=table3[i];
		delay(100);
	}	
	for(i=0;i<4;i++)
	{
		P0=table13[i];
		delay(100);
	}
	P0=0xff; P1=0xff;P2=0xff;
/*******************************/
	for(i=0;i<8;i++)
	{
		P2=table3[i];
		delay(50);
	}
	for(i=0;i<4;i++)
	{
		P1=table3[i];
		delay(50);
	}	
	for(i=0;i<8;i++)
	{
		P0=table3[i];
		delay(50);
	}	
	for(i=0;i<4;i++)
	{
		P0=table13[i];
		delay(50);
	}
	P0=0xff; P1=0xff; P2=0xff;
}

void disp23()			//״̬23 LED���½�����˸
{

	for(i=0;i<2;i++)
	{
		P0=0x00; P2=0x00;
		delay(1000);
		P0=0xff; P2=0xff;
		P1=0x00;
		delay(1000);
		P1=0xff;
	}
}

void disp39()			//״̬39 P1һֱ��,�ϰ벿��LED����������,Ȼ����˸3��
{
	P1=0x00;
	for(i=0;i<8;i++)
	{
		P0=table3[i];
		P2=table3[i];
		delay(50);
	}
	for(i=0;i<8;i++)
	{
		P0=table3[i];
		P2=table3[i];
		delay(100);
	}
	for(i=0;i<4;i++)
	{
		P0=~P0; P2=~P2;
		delay(80);
	}
	delay(200);
	P1=0xff; P2=0xff;P0=0xff;
} 

void disp32()			//״̬32 LED���϶����𲽵�����Ȼ�����������Ϩ��
{
	for(i=0;i<8;i++)
	{
		P0=table3[i];
		P2=table3[i];
		delay(100);
	}
	for(i=0;i<4;i++)
	{
		P1=table8[i];
		delay(100);
	}
	for(i=0;i<4;i++)
	{
		P1=table11[i];
		delay(100);
	}
	for(i=0;i<8;i++)
	{
		P0=table4[i];
		P2=table4[i];
		delay(100);
	}
}

void disp33()			//״̬33 LED�������ҿ�ʼ����(ֱ��ȫ��)��Ȼ����������߿�ʼϨ��(ֱ��ȫ��Ϩ��)
{
	for(i=0;i<8;i++)
	{
		P0=table2[i];		
		if(i<4)
		{
			P1=table2[i];
		}		
		delay(100);
	}
	for(i=0;i<8;i++)
	{		
		P2=table3[i];
		if(i<4)
		{
			P1=table12[i];
		}		
		delay(100);
	}
/****************************/
	for(i=0;i<8;i++)
	{
		P2=table4[i];		
		if(i<4)
		{
			P1=table14[i];
		}		
		delay(100);
	}
	for(i=0;i<8;i++)
	{
		P0=table5[i];		
		if(i<4)
		{
			P1=table5[i+5];
		}		
		delay(100);
	}
}

void disp36()			//״̬36  ��P0.7��P1.4��ʼͬʱ��ʱ����ת��ֱ��LEDȫ��
{
	for(i=0;i<8;i++)
	{
	 	if(i<4)	 P1=table15[i];
	 	if(i<8)	 P0=table3[i];	  
		delay(100);
	}
	for(i=0;i<8;i++)
	{
		if(i<4)	 P1=table16[i];
	 	if(i<8)	 P2=table2[i];
		delay(100);
	}
}

void disp40()			//״̬40 LED��P1.4��P0.7��ʼ��ʱ��ͬʱϨ��ֱ��LEDȫ��Ϩ��
{
	for(i=0;i<8;i++)
	{
		if(i<4)	 P1=table17[i];
	 	if(i<8)	 P0=table3[i];
		delay(100);
	}
	for(i=0;i<8;i++)
	{
		if(i<4)	 P1=table18[i];
	 	if(i<8)	 P2=table2[i];
		delay(100);
	}
	delay(300);	
}

void disp28()			//״̬28 P1��P2��P0������˸
{	
	for(i=0;i<2;i++)
	{
		P1=0x0f; P2=0x00;  
		delay(1000);
		P1=0xf0; P2=0xff; P0=0x00; 
		delay(1000);
	}
	P1=0xff; P2=0xff; P0=0xff;
}

void disp66()
{
	for(i=0;i<10;i++)
	{
		P0=0xff;
		P2=0x00;
		P1=0x0f;
		delay(80);
		P1=0xf0;
		P2=0xff;
		P0=0x00;		
		delay(80);
	}
	P1=P0=P2=0X00;
}




			

void main()
{
	uchar i=0; 
	TMOD=0x01; EA=1; ET0=1;
	while(1)
	{
	if(k1==0)
	{
	   delay(100);
	   if(k1==0)
	   {  
		disp0();	//״̬0 ����LED��˸3��
		disp1();	//״̬1 LED˳ʱ��תһȦ
		disp2();	//״̬2 LED��ʱ��תһȦ	
		disp3();	//״̬3 3��LEDͬʱ˳ʱ����ʱ���ƶ�1/3Ȧ
		disp4();	//״̬4  2��LEDͬʱ�Ӷ����м俪ʼ�����ߵ��ײ��ƶ���Ȧ
		disp5();	//״̬5  2��LEDͬʱ�ӵײ��м俪ʼ�����ߵ������ƶ���Ȧ
		disp6();	//״̬6 LED���϶����𽥵���(һ�����һ�벻��)
		disp7();	//״̬7 LED���¶����𽥵���(ֱ��ȫ������)
		disp0();	//״̬0 ����LED��˸3��
		disp10();	//״̬10 ��LEDȫ������ȫ����
		disp11();	//״̬11 ���8���3��LED����˳ʱ����ת
		disp12();	//״̬12 ���8���3��LED����Ȼ��˳ʱ���𽥵���(ֱ��ȫ������)
		disp13();	//״̬13 ��LEDȫ������ȫ����(���8���3��LED��ʼ˳ʱ��Ϩ��)
		disp14();	//״̬14 ��LED������ȫ��(��P0.0��P1.0��P1.7��P2.0��ʼ�𲼵���)
		disp15();	//״̬15 ��LEDȫ����ȫ����(��P0.7��P1.3��P1.4��P2.7��ʼ��Ϩ��)
		disp16();	//״̬16 LED�ƽ�����˸(Ƶ���������)
		disp17();	//״̬17 LED��P0.7��ʼ��ʱ���𲽵���,�����ٶȻ������
		disp19();	//״̬19 LED��P2.7��ʼ˳ʱ���𲽵���,(ѭ��2��)�����ٶȻ������
		disp23();	//״̬23 LED���½�����˸
		disp39();	//״̬39 P1(�°벿��)һֱ��,�ϰ벿��LED����������,Ȼ����˸3��
		disp32();	//״̬32 LED���϶����𲽵�����Ȼ�����������Ϩ��
		disp33();	//״̬33 LED�������ҿ�ʼ����(ֱ��ȫ��)��Ȼ����������߿�ʼϨ��(ֱ��ȫ��Ϩ��)
		disp36();	//״̬36  ��P0.7��P1.4��ʼͬʱ��ʱ����ת��ֱ��LEDȫ��
		disp40();	//״̬40 ��P0.7��P1.4��ʼ��ʱ��ͬʱϨ��ֱ��LEDȫ��Ϩ��
		disp28();	//״̬28 P1��P2��P0������˸
		disp66();	//״̬66 ���ұ߽�����
		}
		while(!k1);
	}
	if(k2==0)
	{
		delay(100);
		if(k2==0)
		{
		while(1)
		{		
		for(high=1;high<cycle;high++)
		{
			P2=P1=P0=0XFF;
			delay2(high);
			P2=P1=P0=0X00;
			low=cycle-high;
			delay2(low);
		}			
		for(low=1;low<cycle;low++)
		{
			
			P2=P1=P0=0XFF;;
			high=cycle-low;
			delay2(high);
			P2=P1=P0=0X00;
			delay2(low);
		}
     	}
	}
		while(!k2);
		}
	if(k3==0)
	{	
		delay(100);
		if(k3==0)
		{
		while(1)
		{		
			m=music[i][0];n=music[i][1]; 
		if(m==0x00)
		{TR0=0;delay1(n);i++;} 
		else if(m==0xFF)
		{TR0=0;delay1(30);i=0;} 
		else if(m==music[i+1][0]) 
		{TR0=1;delay1(n);TR0=0;pause();i++;}
		else
		{TR0=1;delay1(n);i++;}
		}
		}
	}
	}
	while(!k3);		
}