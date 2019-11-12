/************************************************************************************
*  Copyright (c) 2004,�������ʵ��ӿƼ��������ι�˾
*            All rights reserved.
*
* �ļ����ƣ� I2C.C
* �ļ���ʶ�� none
* ���������� c8051f0f0��PCF8563
* 
* ժ Ҫ�� ���ļ���I2C�����ӳ��򣻽�������JP5�̽�; ʹ���ⲿ22.1184MHz����.
* 
* ��ǰ�汾��1.0
* �� �ߣ�¬ ��
* ������ڣ�2004��11��14��
*
* ��ʷ�汾��0.9 
* ԭ���� �� ¬��������ǿ
* ������ڣ�2004��1��1��
*************************************************************************************/

/************************************************************************************/
// �����ⲿͷ�ļ�

#include "c8051f020.h"
#include "I2C.h"
//#include "gpsone.h"
#include "delay.h"

/************************************************************************************/

/************************************************************************************/
// ȫ�ֱ���
/************************************************************************************/

unsigned char Command;//�����
int *I2CDataBuff;//���������ݡ���������ָ��
unsigned char ByteNumber;  //�����ֽ���
unsigned char ByteReadBytes;//���ֽ���
int *ByteReadAddress;//��������ָ��
unsigned char ChipChoice;//оƬѡ��0ѡ��RTC��1ѡ��24C256							

bit BusBusy;//����æ
bit NoStop;//������һ�����ݺ󲻷���ֹͣλ

/***********************************************************************************
* �������ƣ�SMBusInit;
*
* ��������������SMBus��ʼ��;
*              
* ���������none;
*
* �������ݣ�none��
*
* ע�⣺    none;
************************************************************************************/

void SMBusInit(void)//SMBus��ʼ��
{
	SMB0CN=0x44;//SMBus���ƼĴ���
	SMB0CR=0xee;//SCL��������l_0xed--0xf0
	EIE1=EIE1|0x02;//�����ж�
	EIP1=EIP1|0x02;//����IIC�ж����ȼ�
	//NoStop=0;
	NoStop=1;
	
}

/***********************************************************************************
* �������ƣ�SMBusService;
*
* ��������������SMBus�ж���Ӧ��������ж�״̬������²�����;
*              
* ���������none;
*
* �������ݣ�none��
*
* ע�⣺    none;
************************************************************************************/

void SMBusService (void) interrupt 7
{
	switch (SMB0STA)
		{
		case 0x08: //0x08��ʼ�����ѷ���
			SMB0DAT=Command;
			STA=0; 
			break;

		case 0x10://0x10 �ظ���ʼ�����ѷ���
			SMB0DAT=Command;
			STA=0;
			break;
			
		case 0x18://0x18 ��ַ+W�ѷ����յ�ACK
			if (ByteNumber>0)
			{
				SMB0DAT=*I2CDataBuff;
				I2CDataBuff++;
				ByteNumber--;			
			}
			else
			{
				STO=1;
				BusBusy=0;
			}
			break;

		case 0x20://0x20 ��ַ+W �ѷ����յ�NACK,��������Ӧ����STOP + START ����
			STO=1;
			STA=1;
			break;

		case 0x28://0x28 �����ֽ��ѷ����յ�ACK
			if (ByteNumber>0)
			{
				SMB0DAT=*I2CDataBuff;
				I2CDataBuff++;
				ByteNumber--;			
			}
           /*else
			{
				STO=1;
				BusBusy=0;
			}*/
			 else
			{
				if(NoStop)
					{
						STO=1;
						BusBusy=0;
					}
				else 
					{
						//STO=0;
						//AA=1;
						if(ChipChoice)
							Command=I2C24AddressR;
						else
							Command=I2CPcfAddressR;
						I2CDataBuff=ByteReadAddress;
						ByteNumber=ByteReadBytes;
						STA=1;
						NoStop=1;
					 }				
			}

			break;

		case 0x30://0x30 �����ֽ��ѷ����յ�NACK,��������Ӧ����STOP + START ����
			STO=1;
			STA=1;
			break;

		case 0x38://0x38 ����ʧ��
			STO=1;
			STA=1;
			break;

		case 0x40://0x40 ��ַ+R �ѷ���,�յ�ACK
			if(ByteNumber>1) 
				AA=1; // ��Ӧ������ACK
			else 
				AA=0; 

			if (ByteNumber==0)
			{	
				STO=1;
				BusBusy=0; // �ͷ�SMBus
			}
			break;

		case 0x48://0x48 ��ַ+R �ѷ����յ�NACK,��������Ӧ�����ظ���ʼ��������
			STA=1;
			break;

		case 0x50://0x50 �յ������ֽ�ACK �ѷ���
			if (ByteNumber>0)
			{
				*I2CDataBuff=SMB0DAT;
				I2CDataBuff++;
				ByteNumber--;			
			}
			if (ByteNumber==1) AA=0;
			break;

		case 0x58://0x58 �յ������ֽ�NACK �ѷ���
			*I2CDataBuff=SMB0DAT;
			STO=1;
			BusBusy=0; // �ͷ�SMBus
			NoStop=1;

			break;
			
		default:// ����״̬��û������,��λSMBus
			STO=1;
			BusBusy=0;
			break;
		}
	SI=0; // ����жϱ�־
}




/***********************************************************************************
* �������ƣ�ReadPcf;
*
* ����������������PCF8563;
*              
* ���������unsigned char����ָ��BytesAddress���������ݴ洢��ͷ��ַ;
*	    unsigned char ����RomAddress��Ƭ�ڵ�ַ;
*	    unsigned char ����Count�������ݸ���;
*
* �������ݣ�none��
*
* ע�⣺    none;
************************************************************************************/

void ReadPcf( int *BytesAddress,int RomAddress,unsigned char Count)//��PCF8563
{
/*
	while (BusBusy);
	I2CDataBuff=&RomAddress;
	BusBusy=1;
	AA=1;
	NoStop=0;
	ByteNumber=1;
	Command=I2CPcfAddressW;
	STA=1;
	while (BusBusy);
    NoStop=1;
	I2CDataBuff=BytesAddress;
	BusBusy=1;
	AA=1;
	ByteNumber=Count;
	Command=I2CPcfAddressR;
	STA=1;
	while (BusBusy);*/


	ChipChoice=0;
	ByteReadAddress=BytesAddress;
	ByteReadBytes=Count;    
  while (BusBusy);
	I2CDataBuff=&RomAddress;//�洢�ռ��ַ
	BusBusy=1;
	AA=1;
	//NoStop=1;
	NoStop=0;
	ByteNumber=1;
	Command=I2CPcfAddressW;//�豸д��ַ
	STA=1;
	while (BusBusy);
}

/***********************************************************************************
* �������ƣ�WritePcf;
*
* ��������������дPCF8563;
*              
* ���������unsigned char����ָ��BytesAddress��д�����ݵ�ͷ��ַ;
*	    unsigned char ����RomAddress��Ƭ�ڵ�ַ;
*	    unsigned char ����Count��д���ݸ���;
*
* �������ݣ�none��
*
* ע�⣺    none;
************************************************************************************/
/*
void WritePcf(unsigned char *BytesAddress,unsigned char RomAddress,unsigned char Count)//дPCF8563
{
	int xdata TempBuff[17],n;
	ChipChoice=0;
	TempBuff[0]=RomAddress;
	for(n=1;n<(Count+1);n++)
	{
		TempBuff[n]=*BytesAddress++;
	}
	while (BusBusy);
	NoStop=1;
	I2CDataBuff=&TempBuff[0];
	BusBusy=1;
	AA=1;
	ByteNumber=Count+1;
	Command=I2CPcfAddressW;
	STA=1;
	while (BusBusy);
}*/

/***********************************************************************************/
// �ļ�����
/***********************************************************************************/
