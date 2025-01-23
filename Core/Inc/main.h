/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define MCU_STATUS_LED_Pin GPIO_PIN_13
#define MCU_STATUS_LED_GPIO_Port GPIOC
#define ENC_DT_Pin GPIO_PIN_6
#define ENC_DT_GPIO_Port GPIOA
#define ENC_CLK_Pin GPIO_PIN_7
#define ENC_CLK_GPIO_Port GPIOA
#define ENC_BT_Pin GPIO_PIN_0
#define ENC_BT_GPIO_Port GPIOB
#define BT_LEFT_Pin GPIO_PIN_12
#define BT_LEFT_GPIO_Port GPIOB
#define BT_SEL_CC_CV_Pin GPIO_PIN_13
#define BT_SEL_CC_CV_GPIO_Port GPIOB
#define BT_RIGHT_Pin GPIO_PIN_14
#define BT_RIGHT_GPIO_Port GPIOB
#define BT_OUT_STATE_Pin GPIO_PIN_15
#define BT_OUT_STATE_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
