#ifndef _PCF8563_H  //�궨�壬�����ļ�����
#define _PCF8563_H

/*---------------------------ͷ�ļ�����--------------------------------------*/
#include "stm8s.h"//����STM8ͷ�ļ�

#define PCF8563_ADDRESS 0xA2
#define BcdToHex(dec) ((dec/10)<<4)+(dec%10)
#define HexToBcd(hex) ((hex>>4)*10)+(hex%16)


void PCF8563_WriteByte(u8 addr,u8 dt);
void PCF8563_SetTime(void);
void PCF8563_GetTime(u8 *buf);
void PCF8563_Init(void);
void PCF8563_ShowTime(void);

#endif