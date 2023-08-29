/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
osThreadId SK6812Handle;
osThreadId HX711Handle;
osThreadId UserHandle;
osThreadId COMMHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void SK6812_LEDS_Task(void const * argument);
void HX711_Task(void const * argument);
void User_Task(void const * argument);
void Comm_Task(void const * argument);

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

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of SK6812 */
  osThreadDef(SK6812, SK6812_LEDS_Task, osPriorityHigh, 0, 128);
  SK6812Handle = osThreadCreate(osThread(SK6812), NULL);

  /* definition and creation of HX711 */
  osThreadDef(HX711, HX711_Task, osPriorityRealtime, 0, 128);
  HX711Handle = osThreadCreate(osThread(HX711), NULL);

  /* definition and creation of User */
  osThreadDef(User, User_Task, osPriorityRealtime, 0, 128);
  UserHandle = osThreadCreate(osThread(User), NULL);

  /* definition and creation of COMM */
  osThreadDef(COMM, Comm_Task, osPriorityAboveNormal, 0, 128);
  COMMHandle = osThreadCreate(osThread(COMM), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_SK6812_LEDS_Task */
/**
  * @brief  Function implementing the SK6812 thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_SK6812_LEDS_Task */

/* USER CODE BEGIN Header_HX711_Task */
/**
* @brief Function implementing the HX711 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_HX711_Task */


/* USER CODE BEGIN Header_User_Task */
/**
* @brief Function implementing the User thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_User_Task */


/* USER CODE BEGIN Header_Comm_Task */
/**
* @brief Function implementing the COMM thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Comm_Task */


/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

