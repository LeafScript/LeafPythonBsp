/***********************************************
*	����������LED�����ļ�
* ����				�޸���				�޸���Ϣ
--20210409		Magnin				�����޸�
************************************************/

/**************�������Ӧ��������***************
		LED1 -------------------------- PC12
		LED2 -------------------------- PC11
		LED3 -------------------------- PC10
		LED4 -------------------------- PA15
***********************************************/

#include "led.h"
#include "cm32m101a_conf.h"
#include "share.h"

//����LED�Ʋ�������
typedef struct{
	sp_led_t led;
	GPIO_Module* GPIOx;
	uint16_t Pin;
}sp_led_param_t;

//����LED�Ʋ�������
static sp_led_param_t ledParam[] = {
	{SP_LED1,GPIOC,GPIO_PIN_12},
	{SP_LED2,GPIOC,GPIO_PIN_11},
	{SP_LED3,GPIOC,GPIO_PIN_10},
	{SP_LED4,GPIOA,GPIO_PIN_15},

};
//��ʼ��LED
void Led_Init(void)
{
	GPIO_InitType GPIO_InitStructure;
	//����GPIO�˿�ʱ��
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);
	//��������Ϊ�������
	GPIO_InitStructure.GPIO_Current = GPIO_DC_8mA;		//������С
	GPIO_InitStructure.GPIO_Pull    = GPIO_No_Pull;		//������������
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;	//�������
	
	for(uint8_t i = 0;i < ARRAY_SIZE(ledParam);i++)
	{		
		GPIO_InitStructure.Pin	= ledParam[i].Pin;
		GPIO_InitPeripheral(ledParam[i].GPIOx, &GPIO_InitStructure);
		//��ʼ���ر�LED
		Led_SetState(ledParam[i].led,SP_LED_STATE_CLOSE);
	}
	
}
//����LED״̬
void Led_SetState(sp_led_t led,sp_led_State_t state)
{
	for(uint8_t i = 0;i < ARRAY_SIZE(ledParam);i++)
	{		
		if(ledParam[i].led == led)	//�ҵ���ӦLED
		{
			if(state == SP_LED_STATE_OPEN)	GPIO_SetBits(ledParam[i].GPIOx,ledParam[i].Pin);		//�ߵ�ƽ����
			else 									GPIO_ResetBits(ledParam[i].GPIOx,ledParam[i].Pin);	
		}
	}
}
//��תLED
void Led_Toggles(sp_led_t led)
{
	for(uint8_t i = 0;i < ARRAY_SIZE(ledParam);i++)
	{		
		if(ledParam[i].led == led)	//�ҵ���ӦLED
		{
			ledParam[i].GPIOx->POD ^= ledParam[i].Pin;	//��ת��ƽ
		}
	}

}
//��ȡLED״̬
sp_led_State_t Led_GetState(sp_led_t led)
{
	for(uint8_t i = 0;i < ARRAY_SIZE(ledParam);i++)
	{		
		if(ledParam[i].led == led)	//�ҵ���ӦLED
		{
			//��ȡLED״̬
			if(GPIO_ReadOutputDataBit(ledParam[i].GPIOx,ledParam[i].Pin))	return SP_LED_STATE_OPEN;		
			else 	return SP_LED_STATE_CLOSE;	
		}
	}
	//LED�����ڷ��عر�
	return SP_LED_STATE_CLOSE;
}


