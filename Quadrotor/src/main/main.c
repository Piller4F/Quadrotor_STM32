/****************************************************************************************
@author   石国强
@version  V1.0
@introduction UART1测试 测试方法:
1.串口调试助手发送一个Tag(0xFD)。
2.发送数据长度(Length)16进制。
3.发送Length个字节的数据
4.主函数回显接受的数据
注意：回车是两个字符\r\n
*****************************************************************************************/

#include "led.h"
#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "uart.h"

int main(void) {
	u32 bound = 115200;
	UART1_Init(bound);         //配置波特率
	while(1) {
		if((UART1_STA&0x80)==0x80) {                      //接受到一个数据
			UART1_Send_Data(USART1,UART1_BUF,UART1_LEN);  //发送数据给上位机
			UART1_STA=0;                                  //维护UART1状态寄存器
		}
	}
}
