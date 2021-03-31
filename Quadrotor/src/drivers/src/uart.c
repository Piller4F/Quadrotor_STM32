/****************************************************************************************
@file     uart.c
@brief    串口通信文件
@author   石国强
@version  V1.0
@introduction TLV协议 STM32F407UART1初始化 数据帧解包
@TLV协议 Tag:0xFD Length<=255 
@pin USART1_TX->PB6 USART1_RX->PB7
*****************************************************************************************/

#include "uart.h"

u8 UART1_LEN;                                                   //UART1协议数据长度寄存器
u8 UART1_STA=0;                                                 //UART1协议状态寄存器
u8 UART1_BUF[UART1_BUF_SIZE];                                   //UART1协议缓存寄存器

void UART1_Init(u32 bound) {
	//GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	//时钟使能
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);        //使能GPIO时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);       //打开UART1时钟	
	//复用映射                                                  
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);   //PB6映射为USART1_TX
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);   //PB7映射为USART1_RX
	//USART1端口设置
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;          //GPIO6/7
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;                  //复用功能
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;             //速度50MHz
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;                //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;                  //上拉
	GPIO_Init(GPIOB,&GPIO_InitStructure);                       //初始化PB6,PB7
	//USART1初始化设置
	USART_InitStructure.USART_BaudRate=bound;                   				  //波特率设置
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;   				  //8位数据格式
	USART_InitStructure.USART_StopBits=USART_StopBits_1;       					  //一个停止位
	USART_InitStructure.USART_Parity=USART_Parity_No;          					  //奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None; //无数据流控制
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;					  //收发模式
	USART_Init(USART1,&USART_InitStructure);
	//使能串口1
	USART_Cmd(USART1,ENABLE); 
	//USART1 NVIC配置
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);                 //开通相关中断
	//中断配置
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;              //串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;      //抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		     //子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;			     //IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);                       	     //初始化中断
}

//UART TLV协议
//最多可接受31字节长度数据
void USART1_IRQHandler(void) {
	u8 Res;
	static u8 len=0;
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET) {        //接受中断
		Res=USART_ReceiveData(USART1);                          //读取接受的的数据
		if((UART1_STA&0x80)==0) {                               //数据未接受到
			if((UART1_STA&0x40)==0) {                           //还没遇到帧头
				if(Res==0xFD) UART1_STA|=1<<6;                  //判断当前是否是帧头
			} else {                                            //已经遇到了帧头
				if((UART1_STA&0x20)==0) {                       //还未遇到帧长度
					UART1_STA|=1<<5;                            //标志遇到帧长度 
					UART1_LEN=Res;                              //获取长度 
					len=0;                                      //初始化长度
				} else {
					UART1_BUF[len++]=Res;                       //存储有效数据
					if(len==UART1_LEN) UART1_STA|=0x80;         //数据接受完毕
				}
			}
		}
	}
}

//发送函数
void UART1_Send_Data(USART_TypeDef *USARTx,u8 *str,u8 len) {
	u8 i;
	for(i=0;i<len;++i) {
		USART_SendData(USARTx,str[i]);                        //发送一个字节
		while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)!=SET);//等待发送完成
	}
}

