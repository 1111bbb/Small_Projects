#include "stm8s.h"

#define BEEP_PORT  (GPIOD)          //��������������
#define BEEP_PINS  (GPIO_PIN_3)

void display(unsigned char i);    //��ʾ����ܺ���