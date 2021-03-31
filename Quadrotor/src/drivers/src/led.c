/****************************************************************************************
@file     led.c
@brief    工程主函数文件
@author   盛洁
@version  V1.0
@introduction STM32F407板内自带LED灯的初始化
@pin LED0->GPIOE_P0 LED1->GPIOE_P1 LED2->GPIOE_P2 LED3->GPIOE_P3
@function 推挽输出100MHz
*****************************************************************************************/

#include "led.h"


void LED_Init(void){
	GPIO_InitTypeDef  GPIO_InitStructure;                                             //定义GPIO_InitTypeDef结构体
	                                                                                  
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);                             //使能GPIOE时钟
	                                                                                  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;  //定义LED引脚
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                                    //推挽输出	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;                                //100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;                                      //上拉
	GPIO_Init(GPIOE, &GPIO_InitStructure);                                            //初始化GPIO
}

