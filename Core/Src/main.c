/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "multi_button.h"
#include "string.h"
#include "stdio.h"
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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void BTN1_PRESS_DOWN_Handler(void* btn);
void BTN1_PRESS_UP_Handler(void* btn);
void BTN1_PRESS_REPEAT_Handler(void* btn);
void BTN1_SINGLE_Click_Handler(void* btn);
void BTN1_DOUBLE_Click_Handler(void* btn);
void BTN1_LONG_PRESS_START_Handler(void* btn);
void BTN1_LONG_PRESS_HOLD_Handler(void* btn);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
enum Button_IDs {
	btn1_id,
	btn2_id,
};

struct Button btn1;
struct Button btn2;

const char* multiButtonEventStrings[] = {
	"PRESS_DOWN\r\n",
	"PRESS_UP\r\n",
	"PRESS_REPEAT\r\n",
	"SINGLE_CLICK\r\n",
	"DOUBLE_CLICK\r\n",
	"LONG_PRESS_START\r\n",
	"LONG_PRESS_HOLD\r\n",
};

uint8_t read_button_GPIO(uint8_t button_id)
{
	// you can share the GPIO read function with multiple Buttons
	switch (button_id)
	{
	case btn1_id:
		return HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin);
	case btn2_id:
		return HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin);
	default:
		return 0;
	}
}

uint8_t key_state;
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
  MX_TIM17_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */

  button_init(&btn1, read_button_GPIO, 1, btn1_id);
  button_init(&btn2, read_button_GPIO, 1, btn2_id);

  button_attach(&btn1, PRESS_DOWN, BTN1_PRESS_DOWN_Handler);
  button_attach(&btn1, PRESS_UP, BTN1_PRESS_UP_Handler);
  button_attach(&btn1, PRESS_REPEAT, BTN1_PRESS_REPEAT_Handler);
  button_attach(&btn1, SINGLE_CLICK, BTN1_SINGLE_Click_Handler);
  button_attach(&btn1, DOUBLE_CLICK, BTN1_DOUBLE_Click_Handler);
  button_attach(&btn1, LONG_PRESS_START, BTN1_LONG_PRESS_START_Handler);
  button_attach(&btn1, LONG_PRESS_HOLD, BTN1_LONG_PRESS_HOLD_Handler);

//  button_attach(&btn2, PRESS_DOWN, BTN2_PRESS_DOWN_Handler);
//  button_attach(&btn2, PRESS_UP, BTN2_PRESS_UP_Handler);
//  button_attach(&btn2, PRESS_REPEAT, BTN2_PRESS_REPEAT_Handler);
//  button_attach(&btn2, SINGLE_CLICK, BTN2_SINGLE_Click_Handler);
//  button_attach(&btn2, DOUBLE_CLICK, BTN2_DOUBLE_Click_Handler);
//  button_attach(&btn2, LONG_PRESS_START, BTN2_LONG_PRESS_START_Handler);
//  button_attach(&btn2, LONG_PRESS_HOLD, BTN2_LONG_PRESS_HOLD_Handler);

  button_start(&btn1);
  button_start(&btn2);
  HAL_TIM_Base_Start_IT(&htim17);
  assert_param(0);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
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
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
  RCC_OscInitStruct.PLL.PLLN = 20;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
	if (htim->Instance == TIM17)
	{
		button_ticks();
	}
}

uint8_t tx_buffer[100];
void BTN1_PRESS_DOWN_Handler(void* btn)
{
	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 0);
	//do something...
	HAL_UART_Transmit(&huart3, (const uint8_t *)multiButtonEventStrings[0], strlen(multiButtonEventStrings[0]), 1000);
}

void BTN1_PRESS_UP_Handler(void* btn)
{
	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 1);
	//do something...
	HAL_UART_Transmit(&huart3, (const uint8_t *)multiButtonEventStrings[1], strlen(multiButtonEventStrings[1]), 1000);
}

void BTN1_PRESS_REPEAT_Handler(void* btn)
{
	HAL_UART_Transmit(&huart3, (const uint8_t*)multiButtonEventStrings[2], strlen(multiButtonEventStrings[2]), 1000);
}

void BTN1_SINGLE_Click_Handler(void* btn)
{
	HAL_UART_Transmit(&huart3, (const uint8_t*)multiButtonEventStrings[3], strlen(multiButtonEventStrings[3]), 1000);
}
void BTN1_DOUBLE_Click_Handler(void* btn)
{
	HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, 0);
	HAL_UART_Transmit(&huart3, (const uint8_t*)multiButtonEventStrings[4], strlen(multiButtonEventStrings[4]), 1000);
}
void BTN1_LONG_PRESS_START_Handler(void* btn)
{
	HAL_UART_Transmit(&huart3, (const uint8_t*)multiButtonEventStrings[5], strlen(multiButtonEventStrings[5]), 1000);
}
void BTN1_LONG_PRESS_HOLD_Handler(void* btn)
{
	HAL_UART_Transmit(&huart3, (const uint8_t*)multiButtonEventStrings[6], strlen(multiButtonEventStrings[6]), 1000);
}
/* USER CODE END 4 */

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
	uint8_t debug_data[100];
	sprintf((char*)debug_data, "Wrong parameters value: file %s on line %d\r\n", file, line);
	HAL_UART_Transmit(&huart3, debug_data, strlen((char*)debug_data), 1000);
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
