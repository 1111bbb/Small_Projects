
#include <intrins.h>   
#include <Ctype.h>  

#define uchar unsigned char    
#define uint unsigned  int   
#define ulong unsigned long

typedef unsigned char  INT8U; 
sbit sclk=P3^1;           //�ӿڶ���:lcd_sclk ����LCD��sclk   
sbit sda=P3^2;            //�ӿڶ���:lcd_sid ����LCD��sid   
sbit rs=P3^3;             //�ӿڶ���:lcd_rs ����LCD��rs   
sbit reset=P3^4;          //�ӿڶ���:lcd_reset ����LCD��reset   
sbit cs1=P3^5;            //�ӿڶ���:lcd_cs1 ����LCD��cs1  
//sbit CLCD=P3^0; 
//sbit key=P2^0;          //����һ������ 

//void SYSCLK_Init (void); 
void Initial_Lcd();
void lcd_address(uchar page,uchar column);
void clear_screen();
void display_graphic_8x16(uchar page,uchar column,uchar *dp);
void display_graphic_16x16(uchar page,uchar column,uchar *dp); 
//void display_graphic_32x32(uchar page,uchar column,uchar *dp);  
void delay(int i) ;
void lcddelay_us(int i);
void transfer_command(int data1);
void transfer_data(int data1);
//void zifukong();
void Time_Watch();
void Time_Display();
