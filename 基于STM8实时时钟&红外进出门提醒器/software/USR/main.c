#include "pbdata.h"  //�����Զ��幫��ͷ�ļ�

u8 Time_Remind_CMD[]={0x7E,0x05,0x41,0x00,0x01,0x45,0xEF};//���㱨ʱ
u8 IN_CMD[]={0x7E,0x05,0x41,0x00,0x19,0x5D,0xEF};//������   0x19 -> 0025   
u8 OUT_CMD[]={0x7E,0x05,0x41,0x00,0x1A,0x5E,0xEF};//������  0x20 -> 0026

u8 IO_flag = 0;//������־λ
u8 status = 0;
u8 People_num=0;

BitStatus KEY1;
BitStatus IrDA_OUT;
BitStatus  IrDA_IN;

//volatile RTC_INDEX_e rtc_index; //����rtc_indexΪ    ö����RTC_INDEX_e
////volatile��ʾǿ�����η��������ڴ�����װ�����ݣ�������ֱ�ӴӼĴ�����������
extern u8 time_buf[];

void On_Time_Alarm(void);    //׼�㱨ʱ
void Detection_Number_Of_People(void);//�������


int main(void)
{
  Configuration_Init();//Ӳ�����ó�ʼ��

  while(1)
  {
    KEY1 = GPIO_ReadInputPin(GPIOC, GPIO_PIN_7);//����
    
//    if(KEY1 == 0)
//    {
//        UART1_SendString(IN_CMD,sizeof(IN_CMD));
//    }
    PCF8563_ShowTime();
    On_Time_Alarm();  
    Detection_Number_Of_People();
  }
}

void On_Time_Alarm(void)//׼�㱨ʱ
{
  static u8 once_flag = 0;
  if(time_buf[sec] ==0 && time_buf[min] == 0 )
  {
    if(once_flag == 0)
    {
      Time_Remind_CMD[4]=time_buf[hour]+1;  //ʱ���ѡ����
      Time_Remind_CMD[5]=0x05^0x41^0x00^(Time_Remind_CMD[4]);  //����У����
      UART1_SendString(Time_Remind_CMD,sizeof(Time_Remind_CMD));
      once_flag=1;
    }
    if(time_buf[day]==0){//���12����������
      People_num=0;  
    }
  }
  if(time_buf[min] == 1){once_flag = 0; }//ֻΪһ�η���
  
}

void Detection_Number_Of_People(void)//�������
{
  IrDA_OUT = GPIO_ReadInputPin(GPIOA, GPIO_PIN_1);//������Թ�    ��⵽Ϊ0
  IrDA_IN  = GPIO_ReadInputPin(GPIOA, GPIO_PIN_2);//�ڲ����Թ�    ��⵽Ϊ0
  
  if(IO_flag == NONE){ 
    if(IrDA_OUT == 0 && IrDA_IN != 0) { IO_flag = IN; }
    else if(IrDA_OUT != 0 && IrDA_IN == 0) { IO_flag = OUT; }  //������ ��־λ
  }
  
  if(IO_flag == IN){  
    if( (IrDA_OUT != 0 && IrDA_IN == 0 ) ||(IrDA_OUT == 0 && IrDA_IN == 0 )) { status = 2; }
  }
  
  else if(IO_flag == OUT){
    if( (IrDA_OUT == 0 && IrDA_IN != 0 ) ||(IrDA_OUT == 0 && IrDA_IN == 0 )) { status = 4; }
  }
  else {status = 0;}

    
  if(status == 2){
    UART1_SendString(IN_CMD,sizeof(IN_CMD));
    People_num++;
    status=0;
    IO_flag=NONE;
  }
  if(status == 4){
    UART1_SendString(OUT_CMD,sizeof(OUT_CMD));
    if(People_num==0){People_num=0;}
    else{People_num--;}
    status=0;
    IO_flag=NONE;

  }

   
  OLED_ShowNum(96,6,People_num,2,16);
  
}









/*���Ժ����������������ڱ�̵Ĺ�����Ϊ�����ṩ�������*/
#ifdef USE_FULL_ASSERT
void assert_failed(u8* file,u32 line)
{
  while(1)
  {
  }
}
#endif

/************************ ��̳��ַ www.zxkjmcu.com ******************************/