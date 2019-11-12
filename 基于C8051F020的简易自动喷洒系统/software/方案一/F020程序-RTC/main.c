#include "c8051f020.h"
#include "delay.h"
#include "lcd.h"
#include "I2C.h"
#include "keydown.h"

typedef unsigned int u16;
typedef unsigned char u8;
int Clock[16]; //���Ĵ���pecf8563  buffer

sbit LED = P1^6;//���س���ָʾ��

extern u8 KeyValue;
extern u8 code num[],kong[],kong1[],rain[];
extern int flag_move,flag_set,Time_Count_flag;

struct Time //�ṹ��ȫ�ֱ���
{
	unsigned char second;
	unsigned char minite;
	unsigned char hour;
	unsigned char day;
	unsigned char week;
	unsigned char month;
	unsigned char year;
};
struct Reg
{
	unsigned char reg1;
	unsigned char reg2;
	unsigned char clk;
	unsigned char count1;
	unsigned char count2;
};
struct Alarm
{
	unsigned char minite;
	unsigned char hour;
	unsigned char day;
	unsigned char week;
};
/*----------------������������-------------------------*/
void PORT_Init();//���濪��ʹ��
void SYSCLK_Init();
void Disable_Wdog();  //��ֹ���Ź���ʱ��
void Clock_Setting();
void Init();             //��ʼ��
	

void PORT_Init()//���濪��ʹ��
{
	XBR0    = 0x07;   // Enable UART0(TXD0-P0.0  RXD-P0.1)  SPI_SCK-P0.2  SPI_MISO-P0.3
										// SPI_MOSI-P0.4  SPI_NSS-P0.5   (SDA-P0.6   SCL-P0.7)
  XBR1    = 0x10;		// INT1ʹ��P1.2
  XBR2    = 0x44;		// TXD1-P1.0  RXD1-P1.1
	P3MDOUT = 0xff;	
	P1MDOUT = 0xff;	
	P2MDOUT = 0xff;	
}
/*void Timer0_Init() 
	{     
		TMOD      = 0x02; //��ʽ2 ��ʱ���Զ���װ��  
		TL0       = 0x06;     
		TH0       = 0x06; 
	}*/
void SYSCLK_Init()
{   
	unsigned int i;
	OSCXCN=0X67;           //0X67=0110,0111
	for(i=0;i<256;i++);    //�ȴ�>1ms
	while(!(OSCXCN&0X80)); //�ȴ�XTLVLD��Ϊ1
	OSCICN=0X88;           //ʱ��ʧЧ�������ѡ���ⲿʱ��Դ��Ϊϵͳʱ��
}

void Disable_Wdog()   //��ֹ���Ź���ʱ��
{  
	WDTCN=0xDE;  
	WDTCN=0xAD; 
}

void Clock_Setting()
{
	struct Time TIME={0x10,0x49,0x09,0x15,0x00,0x03,0x18};//����ʱ�䣺 ��/��/ʱ/��/����/��/��
	struct Reg REG={0x00,0x00,0x83,0x82,0x00};//���üĴ���
	struct Alarm ALARM={0x00,0x00,0x00,0x00};//���ñ�ʱ���ƼĴ���
	unsigned char Set[16];//д�Ĵ���buffer
	Set[0]=REG.reg1;	
	Set[1]=REG.reg2;
	Set[2]=TIME.second;
	Set[3]=TIME.minite;
	Set[4]=TIME.hour;
	Set[5]=TIME.day;
	Set[6]=TIME.week;
	Set[7]=TIME.month;
	Set[8]=TIME.year;
	Set[9]=ALARM.minite;
	Set[10]=ALARM.hour;
	Set[11]=ALARM.day;
	Set[12]=ALARM.week;
	Set[13]=REG.clk;		//CLKOUT����Ĵ���	 0DH
	Set[14]=REG.count1;	//��ʱ�����ƼĴ���	 0EH
	Set[15]=REG.count2; //��ʱ���������Ĵ��� 0FH
	//WritePcf(Set,0,16);//����ʱ��
}

void Init()
{
	Disable_Wdog();
	PORT_Init();
	SYSCLK_Init();
  Initial_Lcd();//LCD��ʼ��
	clear_screen();//����
	SMBusInit();//SMBus��ʼ�� ����I2C
}
void main()
{	
	u8 i=0;
	LED=0;//���س���ɹ�ָʾ��
	Init();
	EA=1;//���ж�
	Clock_Setting();
	//Timer0_Init();//��ʱ��0�ж�
	//IE = 0x82;//�жϳ�ʼ��
	//TR0=1;
	Delay_ms(200);
	while(1)
	{
		//Clock_Setting();//������ʱ��ʱʹ��
		ReadPcf(Clock,0,16);//ʵʱʱ���Զ�ȡ
		//display_graphic_8x16(1,(0+8*0),&num[KeyValue*16]);//����ֵ��־
		Key_setting();
		Time_Watch();
	}
}
