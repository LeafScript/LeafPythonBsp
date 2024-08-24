/***********************************************
*	���������ذ��������ļ�
* ����				�޸���				�޸���Ϣ
--20210409		Magnin				�����޸�
************************************************/

/**************�������Ӧ��������***************
			KEY1 -------------------------- PC7
			KEY2 -------------------------- PC8
			KEY3 -------------------------- PC9
			KEY4 -------------------------- PA0
***********************************************/
#include "key_exti.h"
#include "share.h"
#include "cm32m101a_conf.h"

#define KEY_SCAN_DELAY			100	//���������ʱʱ��

typedef struct{
	sp_key_value_t value;
	GPIO_Module* GPIOx;
	uint16_t Pin;
	uint8_t PortSource;
	uint8_t PinSource;
	uint32_t EXTI_Line;
	uint8_t NVIC_IRQChannel;
}sp_key_t;

static sp_key_t spKey[] = {
	{SP_KEY_PRESS_KEY1, GPIOC,	GPIO_PIN_7,	GPIOC_PORT_SOURCE,	GPIO_PIN_SOURCE7,	EXTI_LINE7,	EXTI9_5_IRQn},
	{SP_KEY_PRESS_KEY2,	GPIOC,	GPIO_PIN_8,	GPIOC_PORT_SOURCE,	GPIO_PIN_SOURCE8,	EXTI_LINE8,	EXTI9_5_IRQn},
	{SP_KEY_PRESS_KEY3,	GPIOC,	GPIO_PIN_9,	GPIOC_PORT_SOURCE,	GPIO_PIN_SOURCE9,	EXTI_LINE9,	EXTI9_5_IRQn},
	{SP_KEY_PRESS_KEY4,	GPIOA,	GPIO_PIN_0,	GPIOA_PORT_SOURCE,	GPIO_PIN_SOURCE0,	EXTI_LINE0,	EXTI0_IRQn},
};

static sp_key_value_t keyValue =SP_KEY_PRESS_NONE;

//�����жϳ�ʼ��
void Key_ExtiInit(void)
{
	GPIO_InitType GPIO_InitStructure;
	EXTI_InitType EXTI_InitStructure;
  NVIC_InitType NVIC_InitStructure;
	//����GPIO�˿�ʱ�Ӻ͸���ʱ��
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA| RCC_APB2_PERIPH_AFIO, ENABLE);
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC| RCC_APB2_PERIPH_AFIO, ENABLE);
	//��������Ϊ��������
	GPIO_InitStructure.GPIO_Pull   = GPIO_Pull_Up;		//����
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Input;	//����
	for(uint8_t i = 0;i < ARRAY_SIZE(spKey);i++)
	{		
		GPIO_InitStructure.Pin	= spKey[i].Pin;
		GPIO_InitPeripheral(spKey[i].GPIOx, &GPIO_InitStructure);
		
		GPIO_ConfigEXTILine(spKey[i].PortSource, spKey[i].PinSource);
		 /*key EXTI line*/
    EXTI_InitStructure.EXTI_Line    = spKey[i].EXTI_Line;
    EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; // �½��ش���
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_InitPeripheral(&EXTI_InitStructure);

    /*interrupt priority*/
    NVIC_InitStructure.NVIC_IRQChannel                   = spKey[i].NVIC_IRQChannel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x05;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	}
}

//������ѯ
sp_key_value_t Key_GetValue(void)
{
	sp_key_value_t value = keyValue;
	keyValue =SP_KEY_PRESS_NONE;
	return value;
}
//�ⲿ�ж���0������
void EXTI0_IRQHandler(void)
{
		if(RESET != EXTI_GetITStatus(spKey[3].EXTI_Line))		//��ȡ�ⲿ�ж���״̬
		{		
			if(GPIO_ReadInputDataBit(spKey[3].GPIOx,spKey[3].Pin) == Bit_RESET) keyValue = spKey[3].value;
			EXTI_ClrITPendBit(spKey[3].EXTI_Line);	//��������־
		}
}
//�ⲿ�ж���5��9������
void EXTI9_5_IRQHandler(void)
{
	for(uint8_t i = 0;i < 3; i++)
	{
		if(RESET != EXTI_GetITStatus(spKey[i].EXTI_Line))
		{		
			if(GPIO_ReadInputDataBit(spKey[i].GPIOx,spKey[i].Pin) == Bit_RESET)	keyValue = spKey[i].value;
			EXTI_ClrITPendBit(spKey[i].EXTI_Line);
		}
	}
}
