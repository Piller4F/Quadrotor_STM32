/****************************************************************************************
@file     uart.c
@brief    ����ͨ���ļ�
@author   ʯ��ǿ
@version  V1.0
@introduction TLVЭ�� STM32F407UART1��ʼ�� ����֡���
@TLVЭ�� Tag:0xFD Length<=255 
@pin USART1_TX->PB6 USART1_RX->PB7
*****************************************************************************************/

#include "uart.h"

u8 UART1_LEN;                                                   //UART1Э�����ݳ��ȼĴ���
u8 UART1_STA=0;                                                 //UART1Э��״̬�Ĵ���
u8 UART1_BUF[UART1_BUF_SIZE];                                   //UART1Э�黺��Ĵ���

void UART1_Init(u32 bound) {
	//GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	//ʱ��ʹ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);        //ʹ��GPIOʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);       //��UART1ʱ��	
	//����ӳ��                                                  
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);   //PB6ӳ��ΪUSART1_TX
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);   //PB7ӳ��ΪUSART1_RX
	//USART1�˿�����
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;          //GPIO6/7
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;                  //���ù���
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;             //�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;                //���츴�����
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;                  //����
	GPIO_Init(GPIOB,&GPIO_InitStructure);                       //��ʼ��PB6,PB7
	//USART1��ʼ������
	USART_InitStructure.USART_BaudRate=bound;                   				  //����������
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;   				  //8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits=USART_StopBits_1;       					  //һ��ֹͣλ
	USART_InitStructure.USART_Parity=USART_Parity_No;          					  //��żУ��λ
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None; //������������
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;					  //�շ�ģʽ
	USART_Init(USART1,&USART_InitStructure);
	//ʹ�ܴ���1
	USART_Cmd(USART1,ENABLE); 
	//USART1 NVIC����
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);                 //��ͨ����ж�
	//�ж�����
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;              //����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;      //��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		     //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;			     //IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);                       	     //��ʼ���ж�
}

//UART TLVЭ��
//���ɽ���31�ֽڳ�������
void USART1_IRQHandler(void) {
	u8 Res;
	static u8 len=0;
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET) {        //�����ж�
		Res=USART_ReceiveData(USART1);                          //��ȡ���ܵĵ�����
		if((UART1_STA&0x80)==0) {                               //����δ���ܵ�
			if((UART1_STA&0x40)==0) {                           //��û����֡ͷ
				if(Res==0xFD) UART1_STA|=1<<6;                  //�жϵ�ǰ�Ƿ���֡ͷ
			} else {                                            //�Ѿ�������֡ͷ
				if((UART1_STA&0x20)==0) {                       //��δ����֡����
					UART1_STA|=1<<5;                            //��־����֡���� 
					UART1_LEN=Res;                              //��ȡ���� 
					len=0;                                      //��ʼ������
				} else {
					UART1_BUF[len++]=Res;                       //�洢��Ч����
					if(len==UART1_LEN) UART1_STA|=0x80;         //���ݽ������
				}
			}
		}
	}
}

//���ͺ���
void UART1_Send_Data(USART_TypeDef *USARTx,u8 *str,u8 len) {
	u8 i;
	for(i=0;i<len;++i) {
		USART_SendData(USARTx,str[i]);                        //����һ���ֽ�
		while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)!=SET);//�ȴ��������
	}
}

