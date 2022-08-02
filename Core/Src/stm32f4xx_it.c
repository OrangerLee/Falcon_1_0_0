/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
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
#include "main.h"
#include "stm32f4xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
uint16_t CH1,CH2,CH3,CH4,CH5,CH6,CH7,CH8;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim4;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles TIM1 capture compare interrupt.
  */
void TIM1_CC_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_CC_IRQn 0 */
	static uint16_t cnt1_1,cnt1_2;
	static uint16_t cnt2_1,cnt2_2;
	static uint16_t cnt3_1,cnt3_2;
	static uint16_t cnt4_1,cnt4_2;
	
/**********************CH5************************/	
	if(TIM1->SR & TIM_IT_CC1) 
	{
			TIM1->SR = ~TIM_IT_CC1;
			TIM1->SR = ~TIM_FLAG_CC1OF;
			if(GPIOA->IDR & GPIO_PIN_8)
			{
				cnt1_1 = HAL_TIM_ReadCapturedValue(&htim1, TIM_CHANNEL_1);
			}
			else
			{
				cnt1_2 = HAL_TIM_ReadCapturedValue(&htim1, TIM_CHANNEL_1);
				if(cnt1_2>=cnt1_1)
					CH5 = cnt1_2-cnt1_1;
			}
	}
/**********************CH5************************/	
	
/**********************CH6************************/
	if(TIM1->SR & TIM_IT_CC2) 
	{
			TIM1->SR = ~TIM_IT_CC2;
			TIM1->SR = ~TIM_FLAG_CC1OF;
			if(GPIOA->IDR & GPIO_PIN_9)
			{
				cnt2_1 = HAL_TIM_ReadCapturedValue(&htim1, TIM_CHANNEL_2);
			}
			else
			{
				cnt2_2 = HAL_TIM_ReadCapturedValue(&htim1, TIM_CHANNEL_2);
				if(cnt2_2>=cnt2_1)
					CH6 = cnt2_2-cnt2_1;
			}
	}	
/**********************CH6************************/	
	
/**********************CH7************************/	
		if(TIM1->SR & TIM_IT_CC3) 
	{
		TIM1->SR = ~TIM_IT_CC3;//TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);
		TIM1->SR = ~TIM_FLAG_CC1OF;
		if(GPIOA->IDR & GPIO_PIN_10)
		{
			cnt3_1 = HAL_TIM_ReadCapturedValue(&htim1, TIM_CHANNEL_3);
		}
		else
		{
			cnt3_2 = HAL_TIM_ReadCapturedValue(&htim1, TIM_CHANNEL_3);
			if(cnt3_2>=cnt3_1)
				CH7 = cnt3_2-cnt3_1;
			else
				CH7 = 0xffff-cnt3_1+cnt3_2+1;
		}
	}
/**********************CH7************************/	
	
/**********************CH8************************/	
		if(TIM1->SR & TIM_IT_CC4) 
	{
		TIM1->SR = ~TIM_IT_CC4;//TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);
		TIM1->SR = ~TIM_FLAG_CC1OF;
		if(GPIOA->IDR & GPIO_PIN_11)
		{
			cnt4_1 = HAL_TIM_ReadCapturedValue(&htim1, TIM_CHANNEL_4);
		}
		else
		{
			cnt4_2 = HAL_TIM_ReadCapturedValue(&htim1, TIM_CHANNEL_4);
			if(cnt4_2>=cnt4_1)
				CH8 = cnt4_2-cnt4_1;
			else
				CH8 = 0xffff-cnt4_1+cnt4_2+1;
		}
	}
/**********************CH8************************/	
	
  /* USER CODE END TIM1_CC_IRQn 0 */
  HAL_TIM_IRQHandler(&htim1);
  /* USER CODE BEGIN TIM1_CC_IRQn 1 */

		
		
  /* USER CODE END TIM1_CC_IRQn 1 */
}

/**
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */

  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */

  /* USER CODE END TIM2_IRQn 1 */
}

/**
  * @brief This function handles TIM4 global interrupt.
  */
void TIM4_IRQHandler(void)
{
  /* USER CODE BEGIN TIM4_IRQn 0 */
	static uint16_t cnt1_1,cnt1_2;
	static uint16_t cnt2_1,cnt2_2;
	static uint16_t cnt3_1,cnt3_2;
	static uint16_t cnt4_1,cnt4_2;
	
/**********************CH1************************/
	if(TIM4->SR & TIM_IT_CC1) 
	{
		TIM4->SR = ~TIM_IT_CC1;//TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);
		TIM4->SR = ~TIM_FLAG_CC1OF;
		if(GPIOD->IDR & GPIO_PIN_12)
		{
			cnt1_1 = HAL_TIM_ReadCapturedValue(&htim4, TIM_CHANNEL_1);
		}
		else
		{
			cnt1_2 = HAL_TIM_ReadCapturedValue(&htim4, TIM_CHANNEL_1);
			if(cnt1_2>=cnt1_1)
				CH1 = cnt1_2-cnt1_1;
			else
				CH1 = 0xffff-cnt1_1+cnt1_2+1;
		}
	}
/**********************CH1************************/
	
/**********************CH2************************/
		if(TIM4->SR & TIM_IT_CC2) 
	{
		TIM4->SR = ~TIM_IT_CC2;//TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);
		TIM4->SR = ~TIM_FLAG_CC1OF;
		if(GPIOD->IDR & GPIO_PIN_13)
		{
			cnt2_1 = HAL_TIM_ReadCapturedValue(&htim4, TIM_CHANNEL_2);
		}
		else
		{
			cnt2_2 = HAL_TIM_ReadCapturedValue(&htim4, TIM_CHANNEL_2);
			if(cnt2_2>=cnt2_1)
				CH2 = cnt2_2-cnt2_1;
			else
				CH2 = 0xffff-cnt2_1+cnt2_2+1;
		}
	}
/**********************CH2************************/
	
/**********************CH3************************/
		if(TIM4->SR & TIM_IT_CC3) 
	{
		TIM4->SR = ~TIM_IT_CC3;//TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);
		TIM4->SR = ~TIM_FLAG_CC1OF;
		if(GPIOD->IDR & GPIO_PIN_14)
		{
			cnt3_1 = HAL_TIM_ReadCapturedValue(&htim4, TIM_CHANNEL_3);
		}
		else
		{
			cnt3_2 = HAL_TIM_ReadCapturedValue(&htim4, TIM_CHANNEL_3);
			if(cnt3_2>=cnt3_1)
				CH3 = cnt3_2-cnt3_1;
			else
				CH3 = 0xffff-cnt3_1+cnt3_2+1;
		}
	}
/**********************CH3************************/
	
/**********************CH4************************/
if(TIM4->SR & TIM_IT_CC4) 
	{
		TIM4->SR = ~TIM_IT_CC1;
		TIM4->SR = ~TIM_FLAG_CC1OF;
		if(GPIOD->IDR & GPIO_PIN_15)
		{
			cnt4_1 = HAL_TIM_ReadCapturedValue(&htim4, TIM_CHANNEL_4);
		}
		else
		{
			cnt4_2 = HAL_TIM_ReadCapturedValue(&htim4, TIM_CHANNEL_4);
			if(cnt4_2>=cnt4_1)
				CH4 = cnt4_2-cnt4_1;
			else
				CH4 = 0xffff-cnt4_1+cnt4_2+1;
		}
	}
/**********************CH4************************/
  /* USER CODE END TIM4_IRQn 0 */
  HAL_TIM_IRQHandler(&htim4);
  /* USER CODE BEGIN TIM4_IRQn 1 */

  /* USER CODE END TIM4_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
