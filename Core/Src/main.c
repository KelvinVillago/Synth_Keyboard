/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
 * Wiring for 16x2 LCD
 *    DAC			NUCLEO
 * PIN	NAME	GPIO PORT	HEADER
 * 1	GND		GND			CN10-5
 * 2	VDD		3V3			CN8-7
 * 3	NC		DNC			DNC
 * 4	RS		PB0			CN10-21
 * 5	R/W		PB1			CN10-7
 * 6	EN		PB2			CN9-13
 * 7	DB0		DNC			DNC
 * 8	DB1		DNC			DNC
 * 9	DB2		DNC			DNC
 * 10	DB3		DNC			DNC
 * 11	DB4		PB3			CN7-15
 * 12	DB5		PB4			CN7-19
 * 13	DB6		PB5			CN7-13
 * 14	DB7		PB6			CN9-15
 * 15	A+		3V3			CN8-7
 * 16	K-		GND			CN10-5
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dac.h"
#include "delay.h"
#include "LCD.h"
#include "keyboard.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


char* note_name[17] = {"C4 ", "Cs4", "D4 ", "Ds4", "E4 ", "F4 ", "Fs4", "G4 ", "Gs4", "A4 ", "As4", "B4 ", "C5 ", "Cs5", "D5 ", "Ds5", "E5 "};
int notes[17] = {C4, Cs4,  D4, Ds4, E4, F4, Fs4, G4, Gs4, A4, As4, B4, C5, Cs5, D5, Ds5, E5};
int mega_array[17][1000];
int active_array[ACTIVE_LEN];	//5 buttons maximum
int conv_array1[1999];
int conv_array2[3997];

int waveIx = 0;
int waveIxMax;


int index_cnt = 0;	// Array index counter
uint16_t *ptrArray; // Pointer for ISR array
int stepSize = 1;	// Array step size variable




int main(void){
  init();
  uint32_t prev_buttons = 0;
  uint32_t curr_buttons = check_keys();
  int state = CHECKPRESS;
  int test= mega_array[5][15];
  int num_keys;
  int single_note;

  /*int arrTiming = 177 * 2 + 2;							  // Timing between ISR cycling through array
  int freqSel = 1;										  // Index for frequency or pulseWidth arrays
  int pointsCycle = 900;									  // Points per cycle for Sine wave
  int freq[5] = {100, 200, 300, 400, 500};				  // Frequencies for selection
  int volVal = 0;
  int waveForm;
  int keypadVal;*/

  while (1){
	 //memcpy(active_array, mega_array[5], 1000);
	  //waveIxMax = notes[5];			//delet dis

	  switch (state)
		{

		// Quickly check if button press
		case CHECKPRESS:
			  if (check_vol() != 0){
				 state = VOL;
			  }

			  curr_buttons = check_keys();

			  if (curr_buttons != prev_buttons){	//keys are different than last time
				  if (curr_buttons == 0){
					  __disable_irq();	//disable interrupts
					  memset(active_array, 0, ACTIVE_LEN);
					  LCD_command(0x80);
					  LCD_write_str("Press a button!!");
				  }
				  else{
					  state = INPUT; //XXXXXXXXXchange state or whatever
				  }
				  prev_buttons = curr_buttons;
			  }
			  break;

		case INPUT:
			// Disables interrupts
			//__disable_irq();
			//TIM2->DIER &= ~(TIM_DIER_CC1IE | TIM_DIER_UIE);

			num_keys = get_num_keys(prev_buttons);
			if (num_keys == 1){
				single_note = find_note(prev_buttons);
				memset(active_array, 0, ACTIVE_LEN);
				memcpy(active_array, mega_array[single_note], 1000);
				waveIxMax = notes[single_note];
				LCD_command(0x80);
				LCD_write_str("Note: ");
				LCD_write_str(note_name[single_note]);
				LCD_write_str("       ");
				__enable_irq();
			}
			else if (num_keys == 2){
				int temp1, temp2;
				temp1 = find_note(prev_buttons);
				temp2 = find_note(prev_buttons-POW2(temp1));
				__disable_irq();
				convolution(mega_array[temp1], mega_array[temp2], conv_array1);
				memcpy(active_array, conv_array1, 1999);
				__enable_irq();
			}

			state = CHECKPRESS;
			/*
			// this is where a for loop that specifies the key would be helpful

			// this statement should be adjusted
			// can use enum with all the GPIO pins for buttons and use a for loop to iterate
			// the index of the enumerated values can be manipulated more easily than the GPIO names
			// Changing frequency of system
			if ((volVal == 1) | (volVal == 2) | (volVal == 3) | (volVal == 4) | (volVal == 5))
			{
				volSel = keypadVal;
			}

			// Return to idle state
			else
			{
				state = CHECKPRESS;
			}

			// value used for P2 but will change depending on which key is pressed
			// Determine points/cycle for sin wave
			pointsCycle = 900 / freqSel;

			// Display proper P4 LCD requirements
			// we want volume, key (note, chord, whatever), and maybe wave type?


			//lcd_print(freq[freqSel - 1], keypadVal, waveForm, pointsCycle);

			// Changing step size
			if (waveForm == RECT)
				stepSize = 1;
			else
				stepSize = freq[freqSel - 1] / 100;

			// Reset counter
			TIM2->CNT = 0;
			break;

		/*
		case SINE:
			state = CHECKPRESS;
			// Disable CCR1 since won't use
			TIM2->DIER &= ~(TIM_DIER_CC1IE);

			// Enable ARR as interrupt
			TIM2->DIER |= (TIM_DIER_UIE);

			// Set ARR count
			TIM2->ARR = arrTiming;

			// generate sine array based on key

			// Set array pointer to sin wave
			//ptrArray = &sineWave;

			// Resets timer count
			TIM2->CNT = 0;

			// Resets ISR array index to 0
			index_cnt = 0;

			// Re-enable interrupts
			__enable_irq();
			break;*/
		}
   }
}



void convolution(uint16_t input1[], uint16_t input2[], uint16_t output[]) {
    int i, j;
    // Initialize output array with zeros
    memset(output, 0, sizeof(output));
    // Perform convolution
    for (i = 0; i < sizeof(input1); i++) {
        for (j = 0; j < sizeof(input2); j++) {
            output[i + j] += (input1[i] * input2[j])/3000;
        }
    }
}



void init(void){
	HAL_Init();
	SystemClock_Config();
	DAC_setup();
	SysTick_Init();
	LCD_config();
	LCD_init();
	init_keyboard();
	mega_array_setup();
	setup_TIM2();
}
void mega_array_setup(){
	for (int i=0; i<17; i++)
		make_array(notes[i], mega_array[i]);
}

void make_array(int samples, int * array){
	for (int i=0; i<samples+1; i++){			//samples+1???
		array[i] = (1500*sin(2*M_PI*(float)i/(samples+1)))+1500;
	}
}




void TIM2_IRQHandler(void) {
	if (TIM2->SR & TIM_SR_UIF) {     // ARR int'pt -> End of period of the wave.
		TIM2->SR &= ~(TIM_SR_UIF);   // manage the flag
		waveIx++;

		if (waveIx >= waveIxMax)	 // reset wave index if max
		    waveIx = 0;

    int millivolts = active_array[waveIx];
    uint16_t data_word = DAC_volt_conv(millivolts);

    __disable_irq();
    DAC_write(data_word);			 // IRQ is disabled as it will call during DAC_write()
    __enable_irq();
	}
}



void configurePin(uint8_t pin, GPIO_TypeDef *GPIO_port, uint8_t MODE,
		uint8_t OTYPE, uint8_t OSPEED, uint8_t PUPD) {
	// set field to 0, shifting mask by pinNumber*fieldWidth
	GPIO_port->MODER &= ~(GPIO_MODER_MODE0 << (pin * GPIO_MODER_MODE1_Pos));
	// OR in value ANDed with mask
	GPIO_port->MODER |= (MODE & GPIO_MODER_MODE0)
			<< (pin * GPIO_MODER_MODE1_Pos);

	GPIO_port->PUPDR &= ~(GPIO_PUPDR_PUPD0 << (pin * GPIO_PUPDR_PUPD1_Pos));
	GPIO_port->PUPDR |= (PUPD & GPIO_PUPDR_PUPD0)
			<< (pin * GPIO_PUPDR_PUPD1_Pos);

	GPIO_port->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEED0
			<< (pin * GPIO_OSPEEDR_OSPEED1_Pos));
	GPIO_port->OSPEEDR |= (OSPEED & GPIO_OSPEEDR_OSPEED0)
			<< (pin * GPIO_OSPEEDR_OSPEED1_Pos);

	GPIO_port->OTYPER &= ~(GPIO_OTYPER_OT0 << (pin * GPIO_OTYPER_OT1_Pos));
	GPIO_port->OTYPER |= (OTYPE & GPIO_OTYPER_OT0)
			<< (pin * GPIO_OTYPER_OT1_Pos);
}





void setup_TIM2() {									//////////////////////need to setup the clk here i think
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;           // enable clock for TIM2
	TIM2->DIER |= TIM_DIER_UIE;  // enable event gen, rcv CCR1
	TIM2->ARR = SAMPLE_PERIOD;   // ARR = T = counts @4MHz, init freq = 100HZ
	TIM2->SR &= ~TIM_SR_UIF;       // clr IRQ flag in status reg
	NVIC->ISER[0] |= (1 << (TIM2_IRQn & 0x1F));     // set NVIC interrupt: 0x1F
	__enable_irq();// global IRQ enable
	TIM2->CR1 |= TIM_CR1_CEN;                       // start TIM2 CR1
}



void SystemClock_Config(void){
	/*initializes SYSCLK @ 48MHz
	 *
	 */
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_10;	//sets SYSCLK to 32MHz
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}



static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  HAL_PWREx_EnableVddIO2();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LD3_Pin|LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(USB_PowerSwitchOn_GPIO_Port, USB_PowerSwitchOn_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD3_Pin LD2_Pin */
  GPIO_InitStruct.Pin = LD3_Pin|LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_OverCurrent_Pin */
  GPIO_InitStruct.Pin = USB_OverCurrent_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USB_OverCurrent_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_PowerSwitchOn_Pin */
  GPIO_InitStruct.Pin = USB_PowerSwitchOn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(USB_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : STLK_RX_Pin STLK_TX_Pin */
  GPIO_InitStruct.Pin = STLK_RX_Pin|STLK_TX_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF8_LPUART1;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : USB_SOF_Pin USB_ID_Pin USB_DM_Pin USB_DP_Pin */
  GPIO_InitStruct.Pin = USB_SOF_Pin|USB_ID_Pin|USB_DM_Pin|USB_DP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF10_OTG_FS;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}



void Error_Handler(void)
{
  __disable_irq();
  while (1){}
}



#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t *file, uint32_t line){}
#endif
