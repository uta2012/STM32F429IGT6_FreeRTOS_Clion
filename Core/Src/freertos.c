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
osThreadId Print2Handle;
osThreadId LEDHandle;
osThreadId KEYHandle;
osThreadId DHT11Handle;
osThreadId OLEDHandle;
osThreadId ESP01SHandle;
osMessageQId TemperatureHandle;
osMessageQId HumidityHandle;
osMutexId USART1_MutexHandle;
osStaticMutexDef_t USART1_MutexControlBlock;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void StartPrint1(void const * argument);
void StartPrint2(void const * argument);
void StartLED(void const * argument);
void StartKEY(void const * argument);
void StartDHT11(void const * argument);
void StartOLED(void const * argument);
void StartESP01S(void const * argument);

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
  /* definition and creation of Temperature */
  osMessageQDef(Temperature, 4, uint8_t);
  TemperatureHandle = osMessageCreate(osMessageQ(Temperature), NULL);

  /* definition and creation of Humidity */
  osMessageQDef(Humidity, 4, uint8_t);
  HumidityHandle = osMessageCreate(osMessageQ(Humidity), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadStaticDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128, defaultTaskBuffer, &defaultTaskControlBlock);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of Print1 */
  osThreadDef(Print1, StartPrint1, osPriorityIdle, 0, 64);
  Print1Handle = osThreadCreate(osThread(Print1), NULL);

  /* definition and creation of Print2 */
  osThreadDef(Print2, StartPrint2, osPriorityIdle, 0, 64);
  Print2Handle = osThreadCreate(osThread(Print2), NULL);

  /* definition and creation of LED */
  osThreadDef(LED, StartLED, osPriorityLow, 0, 64);
  LEDHandle = osThreadCreate(osThread(LED), NULL);

  /* definition and creation of KEY */
  osThreadDef(KEY, StartKEY, osPriorityIdle, 0, 64);
  KEYHandle = osThreadCreate(osThread(KEY), NULL);

  /* definition and creation of DHT11 */
  osThreadDef(DHT11, StartDHT11, osPriorityIdle, 0, 80);
  DHT11Handle = osThreadCreate(osThread(DHT11), NULL);

  /* definition and creation of OLED */
  osThreadDef(OLED, StartOLED, osPriorityIdle, 0, 64);
  OLEDHandle = osThreadCreate(osThread(OLED), NULL);

  /* definition and creation of ESP01S */
  osThreadDef(ESP01S, StartESP01S, osPriorityIdle, 0, 512);
  ESP01SHandle = osThreadCreate(osThread(ESP01S), NULL);

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
  uint32_t task1, task2, task3, task4, task5, task6, task7, task8;
  /* Infinite loop */
  for(;;)
  {
      task1 = uxTaskGetStackHighWaterMark(NULL);
      task2 = uxTaskGetStackHighWaterMark(Print1Handle);
      task3 = uxTaskGetStackHighWaterMark(Print2Handle);
      task4 = uxTaskGetStackHighWaterMark(LEDHandle);
      task5 = uxTaskGetStackHighWaterMark(KEYHandle);
      task6 = uxTaskGetStackHighWaterMark(DHT11Handle);
      task7 = uxTaskGetStackHighWaterMark(OLEDHandle);
      task8 = uxTaskGetStackHighWaterMark(ESP01SHandle);
      printf("task1 : %ld\ntask2 : %ld\ntask3 : %ld\ntask4 : %ld\ntask5 : %ld\ntask6 : %ld\ntask7 : %ld\ntask8 : %ld\n",
             task1, task2, task3, task4, task5, task6, task7, task8);
    osDelay(100000);
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
//    uint32_t a = 0;
  /* Infinite loop */
  for(;;)
  {

//    printf("a : %d\n", a);
//    xQueueReceive( QueuePrintHandle, &a, 0 );
    osDelay(1000);
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
//    uint32_t b = 0;

  /* Infinite loop */
  for(;;)
  {
//    printf("b : %d\n", b++);
//    xQueueSend( QueuePrintHandle, &b, 0);
    osDelay(3000);
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
  uint32_t t;

  /* Infinite loop */
  for(;;)
  {

      for(t=0; t<1000; t++)
      {
          HAL_GPIO_WritePin(GPIOH, GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12, GPIO_PIN_SET);
          Delay_us(1000-t);
          HAL_GPIO_WritePin(GPIOH, GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12, GPIO_PIN_RESET);
          Delay_us(t);

      }
      for(t=0; t<1000; t++)
      {
          HAL_GPIO_WritePin(GPIOH, GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12, GPIO_PIN_RESET);
          Delay_us(1000-t);
          HAL_GPIO_WritePin(GPIOH, GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12, GPIO_PIN_SET);
          Delay_us(t);

      }

      osDelay(5000);

  }
  /* USER CODE END StartLED */
}

/* USER CODE BEGIN Header_StartKEY */
/**
* @brief Function implementing the KEY thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartKEY */
void StartKEY(void const * argument)
{
  /* USER CODE BEGIN StartKEY */
  /* Infinite loop */
  for(;;)
  {
      if(HAL_GPIO_ReadPin(KEY_2_GPIO_Port, KEY_2_Pin) == GPIO_PIN_SET)
      {
          //vTaskSuspendAll();
          HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_RESET);
      }
      if(HAL_GPIO_ReadPin(KEY_1_GPIO_Port, KEY_1_Pin) == GPIO_PIN_SET)
      {

          //xTaskResumeAll();
          HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_SET);
      }
    osDelay(20);
  }
  /* USER CODE END StartKEY */
}

/* USER CODE BEGIN Header_StartDHT11 */
/**
* @brief Function implementing the DHT11 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartDHT11 */
void StartDHT11(void const * argument)
{
  /* USER CODE BEGIN StartDHT11 */

    DHT11_DATA_TypeDef DHT11_data = {0};
  /* Infinite loop */
  for(;;)
  {
    DHT11_Read_Temperature_and_Humidity(&DHT11_data);
    xQueueSend(TemperatureHandle, &DHT11_data.temperature_int, 0);
    //printf("T : %d.%d\n", DHT11_data.temperature_int, DHT11_data.temperature_float);
    xQueueSend(HumidityHandle, &DHT11_data.humidity_int, 0);
    //printf("H : %d.%d\t\n", DHT11_data.humidity_int, DHT11_data.humidity_float);
    osDelay(5000);
  }
  /* USER CODE END StartDHT11 */
}

/* USER CODE BEGIN Header_StartOLED */
/**
* @brief Function implementing the OLED thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartOLED */
void StartOLED(void const * argument)
{
  /* USER CODE BEGIN StartOLED */
    uint8_t T_int = 0;
    uint8_t T_float = 0;

    uint8_t H_int = 0;
    uint8_t H_float = 0;

    //title
    for(int i=0; i<7; i++)
    {
        OLED_Put_Char(i+1, 0, title[i]);
    }


    //temp
    OLED_Put_Char(2, 5, Characters[0]);//T
    OLED_Put_Char(3, 5, Characters[1]);//:
    //OLED_Put_Char(6, 5, Characters[3]);//.
    OLED_Put_Char(8, 5, Characters[4]);//°
    OLED_Put_Char(9, 5, Characters[5]);//C
    //he
    OLED_Put_Char(2, 6, Characters[2]);//H
    OLED_Put_Char(3, 6, Characters[1]);//:
    //OLED_Put_Char(6, 6, Characters[3]);//.
    OLED_Put_Char(9, 6, Characters[6]);//%

  /* Infinite loop */
  for(;;)
  {
      xQueueReceive(TemperatureHandle, &T_int, 0);
      xQueueReceive(HumidityHandle, &H_int, 0);


      //温度�??�?
      OLED_Put_Char(6, 5, Numbers[T_int/10]);
      //温度个�?
      OLED_Put_Char(7, 5, Numbers[T_int%10]);

      //湿度个�?
      OLED_Put_Char(6, 6, Numbers[H_int/10]);
      //湿度�??�?
      OLED_Put_Char(7, 6, Numbers[H_int%10]);


    osDelay(5000);
  }
  /* USER CODE END StartOLED */
}

/* USER CODE BEGIN Header_StartESP01S */
/**
* @brief Function implementing the ESP01S thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartESP01S */
void StartESP01S(void const * argument)
{
  /* USER CODE BEGIN StartESP01S */

  uint8_t s[128];
  /* Infinite loop */
  for(;;)
  {
    //printf("send:");
    //HAL_UART_Transmit(&huart2, (uint8_t *)"AT+CGMI\n", 8, 0x99);
    //printf("ESP01S : %s\n", s);


    osDelay(1000);
  }
  /* USER CODE END StartESP01S */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
