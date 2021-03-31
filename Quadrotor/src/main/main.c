/****************************************************************************************
@author   ʯ��ǿ
@version  V1.0
@introduction UART1���� ���Է���:
1.���ڵ������ַ���һ��Tag(0xFD)��
2.�������ݳ���(Length)16���ơ�
3.����Length���ֽڵ�����
4.���������Խ��ܵ�����
ע�⣺�س��������ַ�\r\n
*****************************************************************************************/

#include "led.h"
#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "uart.h"

int main(void) {
	u32 bound = 115200;
	UART1_Init(bound);         //���ò�����
	while(1) {
		if((UART1_STA&0x80)==0x80) {                      //���ܵ�һ������
			UART1_Send_Data(USART1,UART1_BUF,UART1_LEN);  //�������ݸ���λ��
			UART1_STA=0;                                  //ά��UART1״̬�Ĵ���
		}
	}
}
