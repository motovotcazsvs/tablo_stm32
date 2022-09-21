/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "matrix_tablo_tpic.h"
#include "rtc.h"
#include "PressKey.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
_Bool controlTickTime(uint16_t fixed_tick, uint16_t value_tick);
uint16_t getCurrentTick(void);
void outputMainScreen(void);
void outputSettingsScreen(void);
void twoPoints(void);
void functionGetRTC(void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define KEY_NEXT_Pin GPIO_PIN_4
#define KEY_NEXT_GPIO_Port GPIOA
#define KEY_PREV_Pin GPIO_PIN_5
#define KEY_PREV_GPIO_Port GPIOA
#define KEY_SET_Pin GPIO_PIN_6
#define KEY_SET_GPIO_Port GPIOA
#define String0_Pin GPIO_PIN_9
#define String0_GPIO_Port GPIOA
#define String1_Pin GPIO_PIN_10
#define String1_GPIO_Port GPIOA
#define String2_Pin GPIO_PIN_11
#define String2_GPIO_Port GPIOA
#define String3_Pin GPIO_PIN_12
#define String3_GPIO_Port GPIOA
#define String4_Pin GPIO_PIN_15
#define String4_GPIO_Port GPIOA
#define String5_Pin GPIO_PIN_3
#define String5_GPIO_Port GPIOB
#define String6_Pin GPIO_PIN_4
#define String6_GPIO_Port GPIOB
#define String7_Pin GPIO_PIN_6
#define String7_GPIO_Port GPIOB
#define Strobe_Pin GPIO_PIN_7
#define Strobe_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
