/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "sapi.h"
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
UART_HandleTypeDef huart2;

/* Definitions for defaultTask */
/* USER CODE BEGIN PV */
TaskHandle_t task_handle_a;
TaskHandle_t task_handle_b;
TaskHandle_t task_handle_c;
TaskHandle_t task_handle_d;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);

/* USER CODE BEGIN PFP */
// Prototipo de funcion de la tarea
void tarea_A_code( void*  );
void tarea_B_code( void*  );
void tarea_C_code( void*  );
void tarea_D_code( void*  );
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();

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
  /* creation of defaultTask */

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* solo creo la tarea A */
  BaseType_t res;
  res = xTaskCreate(
            tarea_A_code,               // Funcion de la tarea a ejecutar
            ( const char * )"tarea_a",  // Nombre de la tarea como String amigable para el usuario
            configMINIMAL_STACK_SIZE*2, /* tamaño del stack de cada tarea (words) */
            NULL,                       // Parametros de tarea
            tskIDLE_PRIORITY+4,         // Prioridad de la tarea
            &task_handle_a            // Referencia a la tarea creada en el sistema
        );

  configASSERT( res == pdPASS );
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

  /* Start scheduler */

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  vTaskStartScheduler();
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PA0 PA4 PA5 PA6 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

void delay_con_while( uint32_t ms )
{
    volatile uint32_t dummy;
    /* obtengo el tick absoluto */
    TickType_t base = xTaskGetTickCount();
    /* calculo el tick absoluto para destrabar el while */
    TickType_t target = base  + ms ;   /* no esta contemplado el wrap arraond */
    while(  xTaskGetTickCount() < target   )
    {
        dummy++;
    }
}


void blink_n_500( uint32_t n, uint32_t led )
{
    /* genero 2 blinks*/
    int blink_count  = n;
    int cycles       = blink_count*2;

    for( ; cycles>0 ; cycles-- )
    {
        gpioToggle( led );
        delay_con_while( 500 );
    }
}

/*==================[definiciones de funciones externas]=====================*/
void tarea_A_code( void* taskParmPtr )
{
    BaseType_t res;

    mi_printf( "Tarea A\r\n","" );

    UBaseType_t my_prio = uxTaskPriorityGet( 0 );   /* se podria haber usado uxTaskPriorityGet( task_handle_task1 ) */

    /* creo la tarea B con mnor prioridad que la que esta corriendo actualmente
       No hay CC */
    res = xTaskCreate(
              tarea_B_code,                // Funcion de la tarea a ejecutar
              ( const char * )"tarea_b",   // Nombre de fantasia
              configMINIMAL_STACK_SIZE*2,  /* tamaño del stack de cada tarea (words) */
              NULL,                        // Parametros de tarea
              my_prio - 1,                 /* le doy menos prioridad que la tarea actual (la A) */
              &task_handle_b               // Referencia a la tarea creada en el sistema
          );

    configASSERT( res == pdPASS );

    /* creo la tarea C con mnor prioridad que la que esta corriendo actualmente
       No hay CC */
    res = xTaskCreate(
              tarea_C_code,                // Funcion de la tarea a ejecutar
              ( const char * )"tarea_c",   // Nombre de fantasia
              configMINIMAL_STACK_SIZE*2,  /* tamaño del stack de cada tarea (words) */
              NULL,                        // Parametros de tarea
              my_prio - 2,                 /* le doy menos prioridad que la tarea actual (la A) */
              &task_handle_c               // Referencia a la tarea creada en el sistema
          );

    configASSERT( res == pdPASS );

    /* creo la tarea D con mnor prioridad que la que esta corriendo actualmente
       No hay CC */
    res = xTaskCreate(
              tarea_D_code,                // Funcion de la tarea a ejecutar
              ( const char * )"tarea_d",   // Nombre de fantasia
              configMINIMAL_STACK_SIZE*2,  /* tamaño del stack de cada tarea (words) */
              NULL,                        // Parametros de tarea
              my_prio - 3,                 /* le doy menos prioridad que la tarea actual (la A) */
              &task_handle_d               // Referencia a la tarea creada en el sistema
          );

    configASSERT( res == pdPASS );

    /* suspendo la tarea actual */
    vTaskSuspend( NULL );                   /* se podria haber usado vTaskSuspend( task_handle_task1 ) */

    blink_n_500( 2, LEDB );

    /* suspendo la tarea actual */
    vTaskSuspend( task_handle_a );          /* se podria haber usado vTaskSuspend( 0 ) */

    /*...... en una one shot real, nunca retonar sin matar la tarea */
    //vTaskDelete(NULL);
}

void tarea_B_code( void* taskParmPtr )
{
    mi_printf( "Tarea B\r\n","" );

    blink_n_500( 3, LED1 );

    /* retomo tarea A, como tiene mayor prioridad, habra un cambio de contexto.*/
    vTaskResume( task_handle_a );

    /* suspendo la tarea actual, le va a dar el CPU a las tareas de menor prioridad (porque la tarea A esta suspendida) */
    vTaskSuspend( task_handle_b );   /* se podria haber usado vTaskSuspend( 0 ) */

    /*...... en una one shot real, nunca retonar sin matar la tarea */
    //vTaskDelete(NULL);
}

void tarea_C_code( void* taskParmPtr )
{
	mi_printf( "Tarea C\r\n","" );

    blink_n_500( 3, LED2 );

    /* suspendo la tarea actual, le va a dar el CPU a las tareas de menor prioridad (porque la tarea A esta suspendida) */
    vTaskSuspend( task_handle_c );      /* se podria haber usado vTaskSuspend( 0 ) */

    /*...... en una one shot real, nunca retonar sin matar la tarea */
    //vTaskDelete(NULL);
}

void tarea_D_code( void* taskParmPtr )
{
	mi_printf( "Tarea D\r\n","" );

    /* termino todas las tareas de mas prioridad */
    vTaskDelete( task_handle_a );
    vTaskDelete( task_handle_b );
    vTaskDelete( task_handle_c );

    while( 1 )
    {
        gpioToggle( LED3 );
        delay_con_while( 500 );
    }

    /*...... en una one shot real, nunca retonar sin matar la tarea */
    //vTaskDelete(NULL);
}
/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */

 /**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
