/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
uint32_t defaultTaskBuffer[ 128 ];
osStaticThreadDef_t defaultTaskControlBlock;
osThreadId Print1Handle;
osThreadId myPrint2Handle;
osThreadId LEDHandle;
osMessageQId QueuePrintHandle;
osMutexId USART1_MutexHandle;
osStaticMutexDef_t USART1_MutexControlBlock;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void StartPrint1(void const * argument);
void StartPrint2(void const * argument);
void StartLED(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */
  /* Create the mutex(es) */
  /* definition and creation of USART1_Mutex */
  osMutexStaticDef(USART1_Mutex, &USART1_MutexControlBlock);
  USART1_MutexHandle = osMutexCreate(osMutex(USART1_Mutex));

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* definition and creation of QueuePrint */
  osMessageQDef(QueuePrint, 16, uint16_t);
  QueuePrintHandle = osMessageCreate(osMessageQ(QueuePrint), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadStaticDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128, defaultTaskBuffer, &defaultTaskControlBlock);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of Print1 */
  osThreadDef(Print1, StartPrint1, osPriorityIdle, 0, 256);
  Print1Handle = osThreadCreate(osThread(Print1), NULL);

  /* definition and creation of myPrint2 */
  osThreadDef(myPrint2, StartPrint2, osPriorityIdle, 0, 512);
  myPrint2Handle = osThreadCreate(osThread(myPrint2), NULL);

  /* definition and creation of LED */
  osThreadDef(LED, StartLED, osPriorityIdle, 0, 512);
  LEDHandle = osThreadCreate(osThread(LED), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartPrint1 */
/**
* @brief Function implementing the Print1 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartPrint1 */
void StartPrint1(void const * argument)
{
  /* USER CODE BEGIN StartPrint1 */
  //uint32_t a = 0;
  /* Infinite loop */
  for(;;)
  {
    //xQueueReceive( QueuePrintHandle, &a, portMAX_DELAY );
    printf("StartPrint1\n");
    for(int i=0; i<1000; i++)
      Delay_us(1000);
  }
  /* USER CODE END StartPrint1 */
}

/* USER CODE BEGIN Header_StartPrint2 */
/**
* @brief Function implementing the myPrint2 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartPrint2 */
void StartPrint2(void const * argument)
{
  /* USER CODE BEGIN StartPrint2 */
  //uint32_t b = 0;
  /* Infinite loop */
  for(;;)
  {
    //b++;
    //printf("b : %ld\n", b);
    //xQueueGenericSend( QueuePrintHandle, &b, portMAX_DELAY, queueSEND_TO_BACK );
    osDelay(2000);
  }
  /* USER CODE END StartPrint2 */
}

/* USER CODE BEGIN Header_StartLED */
/**
* @brief Function implementing the LED thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartLED */
void StartLED(void const * argument)
{
  /* USER CODE BEGIN StartLED */
  /* Infinite loop */
  for(;;)
  {
    HAL_GPIO_TogglePin(LED_G_GPIO_Port, LED_B_Pin);
    osDelay(1000);
  }
  /* USER CODE END StartLED */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
