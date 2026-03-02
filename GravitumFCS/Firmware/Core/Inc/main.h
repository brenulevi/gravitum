/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SPI1_CS_GYRO_Pin GPIO_PIN_4
#define SPI1_CS_GYRO_GPIO_Port GPIOA
#define SPI1_CS_ACCEL_Pin GPIO_PIN_4
#define SPI1_CS_ACCEL_GPIO_Port GPIOC
#define BOOT1_Pin GPIO_PIN_2
#define BOOT1_GPIO_Port GPIOB
#define SPI2_CS_FLASH_Pin GPIO_PIN_12
#define SPI2_CS_FLASH_GPIO_Port GPIOB
#define LED_F_Pin GPIO_PIN_12
#define LED_F_GPIO_Port GPIOD
#define LED_E_Pin GPIO_PIN_13
#define LED_E_GPIO_Port GPIOD
#define LED_D_Pin GPIO_PIN_14
#define LED_D_GPIO_Port GPIOD
#define LED_C_Pin GPIO_PIN_15
#define LED_C_GPIO_Port GPIOD
#define LED_B_Pin GPIO_PIN_6
#define LED_B_GPIO_Port GPIOC
#define LED_A_Pin GPIO_PIN_7
#define LED_A_GPIO_Port GPIOC
#define GNSS_PSS_Pin GPIO_PIN_8
#define GNSS_PSS_GPIO_Port GPIOC
#define GNSS_LNA_EN_Pin GPIO_PIN_0
#define GNSS_LNA_EN_GPIO_Port GPIOD
#define GNSS_NRST_Pin GPIO_PIN_1
#define GNSS_NRST_GPIO_Port GPIOD
#define ACCEL_INT_Pin GPIO_PIN_7
#define ACCEL_INT_GPIO_Port GPIOD
#define GYRO_INT_Pin GPIO_PIN_3
#define GYRO_INT_GPIO_Port GPIOB
#define MAG_INT_Pin GPIO_PIN_4
#define MAG_INT_GPIO_Port GPIOB
#define BARO_INT_Pin GPIO_PIN_5
#define BARO_INT_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
