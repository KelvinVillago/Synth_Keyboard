/**
  ******************************************************************************
  * @file           : soundAdjustments.h
  * @brief          : Header for soundAdjustments.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  **/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/*
const __flash static freq_array[5] =
	{	100, 200, 300, 400, 500	  };

const __flash static vol_array[5] =
	{	0, 1, 2, 3, 4	};
	*/

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);
int getNew();

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
