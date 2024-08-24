/*
 * mytask.c
 *
 *  Created on: Oct 27, 2021
 *      Author: derek
 */
 
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "mytask.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define START_TASK_PRIO		1		//�������ȼ�
#define START_STK_SIZE 		128 	//�����ջ��С	

#define TASK1_TASK_PRIO		2		//�������ȼ�
#define TASK1_STK_SIZE 		4096 	//�����ջ��С	

#define TASK2_TASK_PRIO		3		//�������ȼ�
#define TASK2_STK_SIZE 		128 	//�����ջ��С	

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
TaskHandle_t StartTask_Handler;		//������
TaskHandle_t Task1Task_Handler;		//������
TaskHandle_t Task2Task_Handler;		//������
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
//ָ��heap_5.c�õ����ڴ淶Χ
const HeapRegion_t xHeapRegions[] =  
{
	{ ( uint8_t * ) 0x20020000UL, 0x28000 }, 
	{ NULL, 0 }                
};
/* USER CODE END Variables */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void start_task(void *pvParameters);//������
void task1_task(void *pvParameters);//������
void task2_task(void *pvParameters);//������
/* USER CODE END FunctionPrototypes */

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */

/* USER CODE END GET_IDLE_TASK_MEMORY */

/* Create the thread(s) */
/* definition and creation of MX_FREERTOS_Init */
void MX_FREERTOS_Init(void)
{
	//ָ��heap_5.c�õ����ڴ淶Χ
	vPortDefineHeapRegions( xHeapRegions ); 

	//������ʼ����
    xTaskCreate((TaskFunction_t )start_task,            //������
                (const char*    )"start_task",          //��������
                (uint16_t       )START_STK_SIZE,        //�����ջ��С
                (void*          )NULL,                  //���ݸ��������Ĳ���
                (UBaseType_t    )START_TASK_PRIO,       //�������ȼ�
                (TaskHandle_t*  )&StartTask_Handler);   //������              
    vTaskStartScheduler();          //�����������
}

//��ʼ����������
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //�����ٽ���
    //����TASK1����
    xTaskCreate((TaskFunction_t )task1_task,             
                (const char*    )"task1_task",           
                (uint16_t       )TASK1_STK_SIZE,        
                (void*          )NULL,                  
                (UBaseType_t    )TASK1_TASK_PRIO,        
                (TaskHandle_t*  )&Task1Task_Handler);   
    //����TASK2����
    xTaskCreate((TaskFunction_t )task2_task,     
                (const char*    )"task2_task",   
                (uint16_t       )TASK2_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )TASK2_TASK_PRIO,
                (TaskHandle_t*  )&Task2Task_Handler); 
    vTaskDelete(StartTask_Handler); //ɾ����ʼ����
	printf("start_task del sucess!\r\n");
    taskEXIT_CRITICAL();            //�˳��ٽ���
}

/* USER CODE BEGIN task1_task */
/**
  * @brief  Function implementing the My freertos thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END task1_task */
void task1_task(void *pvParameters)
{
  /* USER CODE BEGIN task1_task */
  /* Infinite loop */
  uint8_t task1 = 0;
  printf("task python script is enter\r\n");
  
  
  for(;;)
  {
	task1++;
	pikaScriptShell(pikaScriptInit());
	vTaskDelay(10);
  }
  /* USER CODE task1_task */
}

/* USER CODE BEGIN task2_task */
/**
  * @brief  Function implementing the My freertos thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END task2_task */
void task2_task(void *pvParameters)
{
  /* USER CODE BEGIN task2_task */
  /* Infinite loop */
  uint8_t task2 = 0;
  for(;;)
  {
	task2++;
	//printf("task2_task:%d\r\n",task2);
	vTaskDelay(2000);
  }
  /* USER CODE task2_task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void vApplicationIdleHook( void )
{

}
/* USER CODE END Application */



