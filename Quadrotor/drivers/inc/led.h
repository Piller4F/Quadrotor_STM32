/****************************************************************************************
@file     led.h
@brief    �����������ļ�
@author   ʢ��
@version  V1.0
@introduction LED�Ƶĺ꺯��
@function LED0(0) ���� LED0(1) ���� 
*****************************************************************************************/

#ifndef __LED_H_
#define __LED_H_

#include  "stm32f4xx_gpio.h"

//////////////////////////
#define ON 0
#define OFF 1


#define LED0(a) if(a)\
	GPIO_SetBits(GPIOE,GPIO_Pin_0);\
	else \
	GPIO_ResetBits(GPIOE,GPIO_Pin_0) //PE0=0

	
#define LED1(a) if(a)\
	GPIO_SetBits(GPIOE,GPIO_Pin_1);\
	else \
	GPIO_ResetBits(GPIOE,GPIO_Pin_1) //PE0=0
	
#define LED2(a) if(a)\
	GPIO_SetBits(GPIOE,GPIO_Pin_2);\
	else \
	GPIO_ResetBits(GPIOE,GPIO_Pin_2) //PE0=0
	
#define LED3(a) if(a)\
	GPIO_SetBits(GPIOE,GPIO_Pin_3);\
	else \
	GPIO_ResetBits(GPIOE,GPIO_Pin_3) //PE0=0

void LED_Init(void);//LED��ʼ��


#endif
