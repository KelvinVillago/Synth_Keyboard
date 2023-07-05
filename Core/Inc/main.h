/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32l4xx_hal.h"


/*Function protoypes*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
void Error_Handler(void);
void SystemClock_Config(void);
void configurePin(uint8_t pin, GPIO_TypeDef *GPIO_port,
                  uint8_t MODE, uint8_t OTYPE,uint8_t OSPEED,uint8_t PUPD);
void setup_TIM2();
void setup_MCO_CLK(void);
void SysTick_Init(void);
void init(void);





/*Private defines */
// roughly 1 / 30us
#define SAMPLE_RATE 33333
#define SAMPLE_PERIOD 150 //change this later maybe
#define CLKSpeed 32000000

#define ACTIVE_LEN 16000


enum waveType {
  SINE, SAW, SQUARE
};
enum sampleSize {
	C4 = (int)(CLKSpeed / (float)(261.6256 * SAMPLE_PERIOD)), // 4Mhz / (100 * 120)
	Cs4 = (int)(CLKSpeed / (float)(277.1826 * SAMPLE_PERIOD)),
	D4 = (int)(CLKSpeed / (float)(293.6648 * SAMPLE_PERIOD)),
	Ds4 = (int)(CLKSpeed / (float)(311.1270 * SAMPLE_PERIOD)),
	E4 = (int)(CLKSpeed / (float)(329.6276 * SAMPLE_PERIOD)),
	F4 = (int)(CLKSpeed / (float)(349.2282 * SAMPLE_PERIOD)),
	Fs4 = (int)(CLKSpeed / (float)(369.9944 * SAMPLE_PERIOD)),
	G4 = (int)(CLKSpeed / (float)(391.9954 * SAMPLE_PERIOD)),
	Gs4 = (int)(CLKSpeed / (float)(415.3047 * SAMPLE_PERIOD)),
	A4 = (int)(CLKSpeed / (float)(440.0000 * SAMPLE_PERIOD)),
	As4 = (int)(CLKSpeed / (float)(466.1638 * SAMPLE_PERIOD)),
	B4 = (int)(CLKSpeed / (float)(493.8833 * SAMPLE_PERIOD)),
	C5 = (int)(CLKSpeed / (float)(523.2511 * SAMPLE_PERIOD)),
	Cs5 = (int)(CLKSpeed / (float)(554.3653 * SAMPLE_PERIOD)),
	D5 = (int)(CLKSpeed / (float)(587.3295 * SAMPLE_PERIOD)),
	Ds5 = (int)(CLKSpeed / (float)(622.2540 * SAMPLE_PERIOD)),
	E5 = (int)(CLKSpeed / (float)(659.2551 * SAMPLE_PERIOD))
};




#define noteC4 mega_array[0]
#define noteCs4 mega_array[1]
#define noteD4 mega_array[2]
#define noteDs4 mega_array[3]
#define noteE4 mega_array[4]
#define noteF4 mega_array[5]
#define noteFs4 mega_array[6]
#define noteG4 mega_array[7]
#define noteGs4 mega_array[8]
#define noteA4 mega_array[9]
#define noteAs4 mega_array[10]
#define noteB4 mega_array[11]
#define noteC5 mega_array[12]
#define noteCs5 mega_array[13]
#define noteD5 mega_array[14]
#define noteDs5 mega_array[15]
#define noteE5 mega_array[16]


// general pin configurations
#define CONFIG_MODE_INPUT 0
#define CONFIG_MODE_OUTPUT 1
#define CONFIG_MODE_ALT 2
#define CONFIG_MODE_ANALOG 3

#define CONFIG_TYPE_PUSHPULL 0
#define CONFIG_TYPE_OPENDRAIN 1

#define CONFIG_SPEED_LOW 0
#define CONFIG_SPEED_MED 1
#define CONFIG_SPEED_HIGH 2
#define CONFIG_SPEED_VHIGH 3

#define CONFIG_PUPD_NONE 0
#define CONFIG_PUPD_PULLUP 1
#define CONFIG_PUPD_PULLDOWN 2

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define NUM_KEYS 20


#define INPUT 0
#define RECT 8
#define RAMP 7
#define SINE 6
#define SQUARE 9
#define CHECKPRESS 1
#define TRUE 1
#define FALSE 0
#define VOL 10



#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define LD3_Pin GPIO_PIN_14
#define LD3_GPIO_Port GPIOB
#define USB_OverCurrent_Pin GPIO_PIN_5
#define USB_OverCurrent_GPIO_Port GPIOG
#define USB_PowerSwitchOn_Pin GPIO_PIN_6
#define USB_PowerSwitchOn_GPIO_Port GPIOG
#define STLK_RX_Pin GPIO_PIN_7
#define STLK_RX_GPIO_Port GPIOG
#define STLK_TX_Pin GPIO_PIN_8
#define STLK_TX_GPIO_Port GPIOG
#define USB_SOF_Pin GPIO_PIN_8
#define USB_SOF_GPIO_Port GPIOA
#define USB_VBUS_Pin GPIO_PIN_9
#define USB_VBUS_GPIO_Port GPIOA
#define USB_ID_Pin GPIO_PIN_10
#define USB_ID_GPIO_Port GPIOA
#define USB_DM_Pin GPIO_PIN_11
#define USB_DM_GPIO_Port GPIOA
#define USB_DP_Pin GPIO_PIN_12
#define USB_DP_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define LD2_Pin GPIO_PIN_7
#define LD2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
