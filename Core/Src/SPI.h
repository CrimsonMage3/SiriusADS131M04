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
#ifndef __SPI_H
#define __SPI_H

#include "main.h"

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_spi.h"

#define word_lenght 18
#define LENGTH_WRITE 4
#define LENGTH_READ 2

extern SPI_HandleTypeDef hspi1;
extern UART_HandleTypeDef huart2;

extern  uint8_t data_out_buffer[word_lenght];
extern uint16_t data_out;


HAL_StatusTypeDef  spi_write(uint8_t* message);
HAL_StatusTypeDef spi_read(uint8_t* message);

#endif /* __MAIN_H */
