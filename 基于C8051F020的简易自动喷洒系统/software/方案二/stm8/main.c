#include "stm8s.h"
#include "uart.h"
#include "oled.h"
#include "stm8s_uart1.h"

u8 Connect_flag=0;
BitStatus KEY1,KEY2;   

u8 N1[]={0x74,0x35,0x2E,0x74,0x78,0x74,0x3D,0x22,0x30,/**/0x31/**/,0xD2,0xD1,0xB9,0xD8,0xB1,0xD5,0x22,0xff,0xff,0xff};//t1.txt="01�ѹر�"
u8 N2[]={0x74,0x35,0x2E,0x74,0x78,0x74,0x3D,0x22,0x30,/**/0x31/**/,0xD2,0xD1,0xB4,0xF2,0xBF,0xAA,0x22,0xff,0xff,0xff};//t1.txt="01�Ѵ�"
u8 Wifi_Icon[]={0x70,0x30,0x2E,0x70,0x69,0x63,0x3D,0x35,0x30,0xff,0xff,0xff};//������ WIFIͼ��>>GREEN
u8 Wifi_va0[]={0x76,0x61,0x30,0x2E,0x76,0x61,0x6C,0x3D,0x30,0xff,0xff,0xff};//va0.val=0
u8 Wifi_t7[]={0x74,0x37,0x2E,0x74,0x78,0x74,0x3D,0x22,0xD2,0xD1,0xBD,0xD3,0xC1,0xAC,0x22,0xff,0xff,0xff};//t7.txt="�ѽ���"
u8 Wifi_t7_c[]={0x74,0x37,0x2E,0x70,0x63,0x6F,0x3D,0x47,0x52,0x45,0x45,0x4E,0xff,0xff,0xff};//t7.pco=GREEN

void Delay(uint32_t nCount);
void All_ON();
void All_OFF();
void Tim1_Init(void);
void ESP_8266_Init();
void All_Init();
void Enter_Page();

u8 *Replace_Array(u8 array[],u8 num)//���ı��
{
  array[9] = num;
  return array;
}

void Connect_Check()//���WIFI�Ƿ�����
{
  u8 j,return_data;
  return_data = UART1_ReceiveData8();
  OLED_ShowNum(96,6,return_data,3,16);
  if(return_data == 0xbb || return_data == 0xcc || return_data == 0xdd)
  {
    Connect_flag=1;  //���ӳɹ�
    OLED_ShowString(0,0,"WiFi-Connected..");
    OLED_ShowString(0,4,"                ");
    Delay(10000);
    UART1_SendString(Wifi_va0, sizeof(Wifi_va0));
    UART1_SendString(Wifi_t7, sizeof(Wifi_t7));
    UART1_SendString(Wifi_t7_c, sizeof(Wifi_t7_c));
    UART1_SendString(Wifi_Icon, sizeof(Wifi_Icon));
    OLED_ShowString(0,6,"Success!");
    Delay(150000);
    OLED_Clear();
  }
  else 
  {
    OLED_ShowString(0,0,"WiFi-Connecting.");
    for(j=0;j<8;j++) //OLED��ʾ �ն��뷵��������
    OLED_ShowCHinese(j*16,4,j+6);
    Connect_flag=0;  //����ʧ��
  }
}

void main(void)
{   
  All_Init();
  ESP_8266_Init();//ESP_8266����
  while(1)
  {
    while(!Connect_flag)//�ȴ�ȷ������.....��Connect_flag=1  Wifi����  ������ѭ��
    {
       Connect_Check();
       OLED_ShowString(0,6,"Failed!");
    }
    Enter_Page(); //����ҳ���ַ�
    u8 Command;
    Command = UART1_ReceiveData8();
    OLED_ShowNum(96,4,Command,3,16);

    switch(Command)
    {
        case 0x01:UART1_SendString(Replace_Array(N1,0x31),20); GPIO_WriteHigh(GPIOD, GPIO_PIN_3);OLED_ShowString(96,6,"OFF");break;//01�ѹر�
        case 0x02:UART1_SendString(Replace_Array(N2,0x31),20);  GPIO_WriteLow(GPIOD, GPIO_PIN_3);OLED_ShowString(96,6,"ON ");break;//01�Ѵ�
        case 0x03:UART1_SendString(Replace_Array(N1,0x32),20); GPIO_WriteHigh(GPIOD, GPIO_PIN_2);OLED_ShowString(96,6,"OFF");break;//02
        case 0x04:UART1_SendString(Replace_Array(N2,0x32),20);  GPIO_WriteLow(GPIOD, GPIO_PIN_2);OLED_ShowString(96,6,"ON ");break;
        case 0x05:UART1_SendString(Replace_Array(N1,0x33),20); GPIO_WriteHigh(GPIOD, GPIO_PIN_4);OLED_ShowString(96,6,"OFF");break;//03
        case 0x06:UART1_SendString(Replace_Array(N2,0x33),20);  GPIO_WriteLow(GPIOD, GPIO_PIN_4);OLED_ShowString(96,6,"ON ");break;//----------------------
        case 0x07:UART1_SendString(Replace_Array(N1,0x34),20); GPIO_WriteHigh(GPIOA, GPIO_PIN_2);OLED_ShowString(96,6,"OFF");break;//04
        case 0x08:UART1_SendString(Replace_Array(N2,0x34),20);  GPIO_WriteLow(GPIOA, GPIO_PIN_2);OLED_ShowString(96,6,"ON ");break;
        case 0x09:UART1_SendString(Replace_Array(N1,0x35),20); GPIO_WriteHigh(GPIOA, GPIO_PIN_3);OLED_ShowString(96,6,"OFF");break;//05
        case 0x0a:UART1_SendString(Replace_Array(N2,0x35),20);  GPIO_WriteLow(GPIOA, GPIO_PIN_3);OLED_ShowString(96,6,"ON ");break;
        case 0xbb:All_OFF();OLED_ShowString(96,6,"OFF");break;
        case 0xcc:All_ON(); OLED_ShowString(96,6,"ON ");break;
        case 0xdd:All_OFF();OLED_ShowString(96,6,"OFF");//��break;
        default : break; 
    }   
   }
}

void Delay(uint32_t nCount) //�ӳٺ��� //ms����
{
  /* Decrement nCount value */
  while (nCount != 0)
  {
    nCount--;
  }
}

void All_ON() //ȫ����
{
  GPIO_WriteLow(GPIOD, GPIO_PIN_3);
  GPIO_WriteLow(GPIOD, GPIO_PIN_2);
  GPIO_WriteLow(GPIOD, GPIO_PIN_4);
  GPIO_WriteLow(GPIOA, GPIO_PIN_3);
  GPIO_WriteLow(GPIOA, GPIO_PIN_2);
}

void All_OFF()//ȫ���ر�
{
  GPIO_WriteHigh(GPIOD, GPIO_PIN_3);
  GPIO_WriteHigh(GPIOD, GPIO_PIN_2);
  GPIO_WriteHigh(GPIOD, GPIO_PIN_4);
  GPIO_WriteHigh(GPIOA, GPIO_PIN_3);
  GPIO_WriteHigh(GPIOA, GPIO_PIN_2);
}

void Tim1_Init(void)
{
  TIM1_TimeBaseInit(16,TIM1_COUNTERMODE_UP,1000,0);
  TIM1_ARRPreloadConfig(ENABLE);
  TIM1_ITConfig(TIM1_IT_UPDATE , ENABLE);
  TIM1_Cmd(ENABLE);
}

void ESP_8266_Init()//ESP8266��ʼ����  ��Ϊ�ͻ��� ��WIFIģ�飺USR-C215Ϊ��������
{
  UART1_SendString("AT+CIPSTART=\"TCP\",\"10.10.100.254\",8899\r\n",46);
  Delay(20000);
  UART1_SendString("AT+CIPMODE=1\r\n",16);
  Delay(20000);
  UART1_SendString("AT+CIPSEND\r\n",14);
  Delay(20000);
}

void All_Init()
{
  /*�����ڲ�����ʱ��16MΪ��ʱ��*/ 
  //CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
  OLED_Init();		
  OLED_Clear();
  Uart_Init();
  UART1_SendString("TEST 001\r\n",12);
  GPIO_Init(GPIOA, GPIO_PIN_1, GPIO_MODE_OUT_PP_HIGH_SLOW);//����2
  GPIO_Init(GPIOA, GPIO_PIN_2, GPIO_MODE_OUT_PP_HIGH_SLOW);//����3
  
  GPIO_Init(GPIOD, GPIO_PIN_3, GPIO_MODE_OUT_PP_HIGH_SLOW);//������
  GPIO_Init(GPIOD, GPIO_PIN_2, GPIO_MODE_OUT_PP_HIGH_SLOW);//������  
  GPIO_Init(GPIOD, GPIO_PIN_4, GPIO_MODE_OUT_PP_HIGH_SLOW);//������  //����1
  GPIO_Init(GPIOA, GPIO_PIN_2, GPIO_MODE_OUT_PP_HIGH_SLOW);//������  //����2
  GPIO_Init(GPIOA, GPIO_PIN_3, GPIO_MODE_OUT_PP_HIGH_SLOW);//������
  Tim1_Init();
  enableInterrupts();                                    //ʹ���ж�*/
}

void Enter_Page()
{
  OLED_ShowCHinese(0,0,15);//WIFIͼ��
  OLED_ShowCHinese(112,0,14);//����ͼ��
  OLED_ShowCHinese(0,4,1);//��     
  OLED_ShowCHinese(16,4,2);//ǰ
  OLED_ShowCHinese(32,4,17);//ָ
  OLED_ShowCHinese(48,4,18);//��
  OLED_ShowString(64,4,":");//��
  
  OLED_ShowCHinese(0,6,2);//ǰ
  OLED_ShowCHinese(16,6,3);//��
  OLED_ShowCHinese(32,6,19);//״
  OLED_ShowCHinese(48,6,20);//̬
  OLED_ShowString(64,6,":");//��
}