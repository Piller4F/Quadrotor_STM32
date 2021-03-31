/****************************************************************************************
@file     uart.h
@brief    串口通信文件
@author   石国强
@version  V1.0
@introduction TLV协议 STM32F407UART1初始化 数据帧解包
@pin USART1_TX->PB6 USART1_RX->PB7
*****************************************************************************************/

#ifndef __UART_H__
#define __UART_H__

#include "stm32f4xx_usart.h"

#define UART1_BUF_SIZE 255            //最大数据长度

//7   表示数据接受完毕
//6   表示遇到帧头
//5   表示遇到数据长度标志
extern u8 UART1_STA;                     //UART1协议状态寄存器
extern u8 UART1_LEN;                     //UART1协议数据长度寄存器
extern u8 UART1_BUF[UART1_BUF_SIZE];     //UART1协议缓存寄存器

void UART1_Init(u32 bound);              //UART初始化
void UART1_Send_Data(USART_TypeDef *USARTx,u8 *str,u8 len);  //数据发送

#endif

