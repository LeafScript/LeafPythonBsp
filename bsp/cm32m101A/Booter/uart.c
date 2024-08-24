/***********************************************
*	�����c���������ļ�
* ����				�޸���				�޸���Ϣ
--20210409		Magnin				�����޸�
************************************************/

/**************�������Ӧ��������***************
			UART1 TX -------------------------- PA9
			UART1 RX -------------------------- PA10
***********************************************/
#include "uart.h"
#include "share.h"
#include "cm32m101a_conf.h"
#include <stdio.h>

static USART_InitType USART_InitStructure;

void Usart1_Init(void)
{		
	GPIO_InitType GPIO_InitStructure;
	//����GPIO��ʱ��
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
	//����USARTʱ��
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_USART1, ENABLE);
	// ��ʼ��GPIO�ṹ
	GPIO_InitStruct(&GPIO_InitStructure);
	//���� USARTx Tx
	GPIO_InitStructure.Pin            = GPIO_PIN_9;
	GPIO_InitStructure.GPIO_Mode      = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Alternate = GPIO_AF4_USART1;	//����Ϊ����
	GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
	//���� USARTx Rx
	GPIO_InitStructure.Pin            = GPIO_PIN_10;
	GPIO_InitStructure.GPIO_Pull      = GPIO_Pull_Up;
	GPIO_InitStructure.GPIO_Alternate = GPIO_AF4_USART1;	//����Ϊ����
	GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
	//���ô��ڲ���
	USART_InitStructure.BaudRate            = USART1_BANDRATE;	//������
	USART_InitStructure.WordLength          = USART_WL_8B;			//����λ
	USART_InitStructure.StopBits            = USART_STPB_1;			//ֹͣλ
	USART_InitStructure.Parity              = USART_PE_NO;			//У��λ
	USART_InitStructure.HardwareFlowControl = USART_HFCTRL_NONE;	//�ر�Ӳ����ʹ��
	USART_InitStructure.Mode                = USART_MODE_RX | USART_MODE_TX;	//���ͽ���ģʽ
	//��ʼ��USART1
	USART_Init(USART1, &USART_InitStructure);
	//ʹ��USART1
	USART_Enable(USART1, ENABLE);
}
//�ض���fputc
int fputc(int ch, FILE* f)
{
	USART_SendData(USART1, (uint8_t)ch);	//��USART1��������
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXDE) == RESET)	;	//�ȴ��������
	return (ch);
}

