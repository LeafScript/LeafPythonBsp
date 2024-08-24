/***********************************************
*	�������̵��������ļ�
* ����				�޸���				�޸���Ϣ
--20210409		Magnin				�����޸�
************************************************/

/**************�������Ӧ��������***************
			RELAY -------------------------- PD2
***********************************************/
#include "relay.h"
#include "share.h"
#include "cm32m101a_conf.h"

//����Relay�Ʋ�������
typedef struct{
	sp_relay_t relay;
	GPIO_Module* GPIOx;
	uint16_t Pin;
}sp_led_param_t;

//����Relay�Ʋ�������
static sp_led_param_t relayParam[] = {
	{SP_RELAY1,GPIOD,GPIO_PIN_2}
};
//��ʼ��Relay
void Relay_Init(void)
{
	GPIO_InitType GPIO_InitStructure;
	//����GPIO�˿�ʱ��
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOD, ENABLE);
	//��������Ϊ�������
	GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;		//������С
	GPIO_InitStructure.GPIO_Pull    = GPIO_No_Pull;		//������������
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;	//�������
	
	for(uint8_t i = 0;i < ARRAY_SIZE(relayParam);i++)
	{		
		GPIO_InitStructure.Pin	= relayParam[i].Pin;
		GPIO_InitPeripheral(relayParam[i].GPIOx, &GPIO_InitStructure);
		//��ʼ���ر�Relay
		Relay_SetState(relayParam[i].relay,SP_RELAY_STATE_CLOSE);
	}
	
}
//����Relay״̬
void Relay_SetState(sp_relay_t relay,sp_relay_state_t state)
{
	for(uint8_t i = 0;i < ARRAY_SIZE(relayParam);i++)
	{		
		if(relayParam[i].relay == relay)	//�ҵ���ӦLED
		{
			if(state == SP_RELAY_STATE_OPEN)	GPIO_SetBits(relayParam[i].GPIOx,relayParam[i].Pin);		//�ߵ�ƽ����
			else 									GPIO_ResetBits(relayParam[i].GPIOx,relayParam[i].Pin);	
		}
	}
}
//��תRelay
void Relay_Toggles(sp_relay_t relay)
{
	for(uint8_t i = 0;i < ARRAY_SIZE(relayParam);i++)
	{		
		if(relayParam[i].relay == relay)	//�ҵ���ӦLED
		{
			relayParam[i].GPIOx->POD ^= relayParam[i].Pin;	//��ת��ƽ
		}
	}

}
//��ȡRelayD״̬
sp_relay_state_t Relay_GetState(sp_relay_t relay)
{
	for(uint8_t i = 0;i < ARRAY_SIZE(relayParam);i++)
	{		
		if(relayParam[i].relay == relay)	//�ҵ���ӦRelay
		{
			//��ȡRelay״̬
			if(GPIO_ReadOutputDataBit(relayParam[i].GPIOx,relayParam[i].Pin))	return SP_RELAY_STATE_OPEN;		
			else 	return SP_RELAY_STATE_CLOSE;	
		}
	}
	//Relay�����ڷ��عر�
	return SP_RELAY_STATE_CLOSE;
}


