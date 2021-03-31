/****************************************************************************************
@file     led.c
@brief    �����������ļ�
@author   ʢ��
@version  V1.0
@introduction STM32F407�����Դ�LED�Ƶĳ�ʼ��
@pin LED0->GPIOE_P0 LED1->GPIOE_P1 LED2->GPIOE_P2 LED3->GPIOE_P3
@function �������100MHz
*****************************************************************************************/

#include "led.h"


void LED_Init(void){
	GPIO_InitTypeDef  GPIO_InitStructure;                                             //����GPIO_InitTypeDef�ṹ��
	                                                                                  
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);                             //ʹ��GPIOEʱ��
	                                                                                  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;  //����LED����
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                                    //�������	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;                                //100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;                                      //����
	GPIO_Init(GPIOE, &GPIO_InitStructure);                                            //��ʼ��GPIO
}

