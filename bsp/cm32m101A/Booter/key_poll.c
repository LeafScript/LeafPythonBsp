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
#include "key_poll.h"
#include "share.h"
#include "cm32m101a_conf.h"

#define KEY_SCAN_DELAY			100	//���������ʱʱ��

typedef struct{
	sp_key_value_t value;
	GPIO_Module* GPIOx;
	uint16_t Pin;
}sp_key_t;

static sp_key_t spKey[] = {
	{SP_KEY_PRESS_KEY1,GPIOC,GPIO_PIN_7},
	{SP_KEY_PRESS_KEY2,GPIOC,GPIO_PIN_8},
	{SP_KEY_PRESS_KEY3,GPIOC,GPIO_PIN_9},
	{SP_KEY_PRESS_KEY4,GPIOA,GPIO_PIN_0},
};
//������ѯ��ʼ��
void Key_PollInit(void)
{
	GPIO_InitType GPIO_InitStructure;
	//����GPIO�˿�ʱ��
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);
	//��������Ϊ��������
	GPIO_InitStructure.GPIO_Pull   = GPIO_Pull_Up;		//����
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Input;	//����
	for(uint8_t i = 0;i < ARRAY_SIZE(spKey);i++)
	{		
		GPIO_InitStructure.Pin	= spKey[i].Pin;
		GPIO_InitPeripheral(spKey[i].GPIOx, &GPIO_InitStructure);
	}
}
//������ѯ
sp_key_value_t Key_Poll(void)
{
	for(uint8_t i = 0;i < ARRAY_SIZE(spKey);i++)
	{		
		if(GPIO_ReadInputDataBit(spKey[i].GPIOx,spKey[i].Pin) == Bit_RESET)
		{
			//��ʱ����
			Delay_Ms(KEY_SCAN_DELAY);
			if(GPIO_ReadInputDataBit(spKey[i].GPIOx,spKey[i].Pin) == Bit_RESET)
			{
#ifdef SP_KEY_POLL_LOOSE_CHECK
				while(GPIO_ReadInputDataBit(spKey[i].GPIOx,spKey[i].Pin) == Bit_RESET) ;
#endif
				return spKey[i].value;
			}				
		}
	}
	return SP_KEY_PRESS_NONE;
}

