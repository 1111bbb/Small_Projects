/**
   ��ʼ��Ϊ ֹͣ״̬����ҡ��Ϊ����ģʽ
	 2018.6.10
	 ҡ�˲��ݷ����� ���ű��Vx,Vy�෴
**/

#include "include.h"



int main(void)
{ 
	
  Perpheral_Init();      //�ⲿ��ʼ��
	Begin_Show();          //��������
	TIM_Cmd(TIM3, ENABLE); //ʹ��TIMx����
	my_OLED();
	while(1)
	{ 
			CMD_Send();
			My_Show_OLED();
	}											    
}	




