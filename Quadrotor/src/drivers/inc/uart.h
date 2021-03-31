/****************************************************************************************
@file     uart.h
@brief    ����ͨ���ļ�
@author   ʯ��ǿ
@version  V1.0
@introduction TLVЭ�� STM32F407UART1��ʼ�� ����֡���
@pin USART1_TX->PB6 USART1_RX->PB7
*****************************************************************************************/

#ifndef __UART_H__
#define __UART_H__

#include "stm32f4xx_usart.h"

#define UART1_BUF_SIZE 255            //������ݳ���

//7   ��ʾ���ݽ������
//6   ��ʾ����֡ͷ
//5   ��ʾ�������ݳ��ȱ�־
extern u8 UART1_STA;                     //UART1Э��״̬�Ĵ���
extern u8 UART1_LEN;                     //UART1Э�����ݳ��ȼĴ���
extern u8 UART1_BUF[UART1_BUF_SIZE];     //UART1Э�黺��Ĵ���

void UART1_Init(u32 bound);              //UART��ʼ��
void UART1_Send_Data(USART_TypeDef *USARTx,u8 *str,u8 len);  //���ݷ���

#endif

