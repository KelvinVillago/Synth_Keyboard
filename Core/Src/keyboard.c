/*
 * keyboard.c
 *
 *  Created on: Jun 5, 2023
 *      Author: zakth
 *
 *
 *
 *																				____	____	____
 *      |C4	|Cs4|D4	|Ds4|E4	|F4	|Fs4|G4	|Gs4|A4	|As4|B4	|C5	|Cs5|D5	|Ds5|E5	|	| +	|	|wv |	| - |
 *      |	|___|	|___|	|	|___|	|___|	|___|	|	|___|	|___|	|	|___| 	|___|	|___|
 *      |___|	|___|	|___|___|	|___|	|___|	|___|___|	|___|	|___|
 *      PC0	PC1	PC2	PC3	PC4	PC5	PC8	PC9	PC10PC11PD0	PD1	PD2	PD3	PD4	PD5 PD6		PD7		PD8		PD9
 */

#include "keyboard.h"



void init_keyboard(void){
	/* @params: none; @retvals: none
	 * Initializes the keyboard as described in the header
	 */
	RCC->AHB2ENR |= KP_CLK;	//enable all pushbuttons!!
	KP_PIN->MODER   &= ~(GPIO_MODER_MODE0 | GPIO_MODER_MODE1 |
						 GPIO_MODER_MODE2 | GPIO_MODER_MODE3 |
						 GPIO_MODER_MODE4 | GPIO_MODER_MODE5 |
						 GPIO_MODER_MODE6 | GPIO_MODER_MODE7 |
						 GPIO_MODER_MODE8 | GPIO_MODER_MODE9);
	KP_PIN->MODER    &= ~(GPIO_MODER_MODE0 | GPIO_MODER_MODE1|
						 GPIO_MODER_MODE2 | GPIO_MODER_MODE3 |
						 GPIO_MODER_MODE4 | GPIO_MODER_MODE5 |
						 GPIO_MODER_MODE6 | GPIO_MODER_MODE7 |
						 GPIO_MODER_MODE8 | GPIO_MODER_MODE9);
	KP_PIN->PUPDR   &=  ~(GPIO_PUPDR_PUPD0 | GPIO_PUPDR_PUPD1 |
							GPIO_PUPDR_PUPD2 | GPIO_PUPDR_PUPD3 |
							GPIO_PUPDR_PUPD4 | GPIO_PUPDR_PUPD5 |
							GPIO_PUPDR_PUPD6 | GPIO_PUPDR_PUPD7 |
							GPIO_PUPDR_PUPD8 | GPIO_PUPDR_PUPD9);
	KP_PIN->PUPDR   |=  (GPIO_PUPDR_PUPD0_1 | GPIO_PUPDR_PUPD1_1 |
						GPIO_PUPDR_PUPD2_1 | GPIO_PUPDR_PUPD3_1 |
						GPIO_PUPDR_PUPD4_1 | GPIO_PUPDR_PUPD5_1 |
						GPIO_PUPDR_PUPD6_1 | GPIO_PUPDR_PUPD7_1 |
						GPIO_PUPDR_PUPD8_1 | GPIO_PUPDR_PUPD9_1);

	RCC->AHB2ENR |= KP_CLK2;	//enable all pushbuttons!!
	KP_PIN2->MODER   &= ~(GPIO_MODER_MODE0 | GPIO_MODER_MODE1 |
						 GPIO_MODER_MODE2 | GPIO_MODER_MODE3 |
						 GPIO_MODER_MODE4 | GPIO_MODER_MODE5 |
						 GPIO_MODER_MODE8 | GPIO_MODER_MODE9 |
						 GPIO_MODER_MODE10 | GPIO_MODER_MODE11);
	KP_PIN2->MODER    &= ~(GPIO_MODER_MODE0 | GPIO_MODER_MODE1|
						 GPIO_MODER_MODE2 | GPIO_MODER_MODE3 |
						 GPIO_MODER_MODE4 | GPIO_MODER_MODE5 |
						 GPIO_MODER_MODE8 | GPIO_MODER_MODE9 |
						 GPIO_MODER_MODE10 | GPIO_MODER_MODE11);
	KP_PIN2->PUPDR   &=  ~(GPIO_PUPDR_PUPD0 | GPIO_PUPDR_PUPD1 |
							GPIO_PUPDR_PUPD2 | GPIO_PUPDR_PUPD3 |
							GPIO_PUPDR_PUPD4 | GPIO_PUPDR_PUPD5 |
							GPIO_PUPDR_PUPD8 | GPIO_PUPDR_PUPD9 |
							GPIO_PUPDR_PUPD10 | GPIO_PUPDR_PUPD11);
	KP_PIN2->PUPDR   |=  (GPIO_PUPDR_PUPD0_1 | GPIO_PUPDR_PUPD1_1 |
						GPIO_PUPDR_PUPD2_1 | GPIO_PUPDR_PUPD3_1 |
						GPIO_PUPDR_PUPD4_1 | GPIO_PUPDR_PUPD5_1 |
						GPIO_PUPDR_PUPD8_1 | GPIO_PUPDR_PUPD9_1 |
						GPIO_PUPDR_PUPD10_1 | GPIO_PUPDR_PUPD11_1);
}

uint32_t check_keys(void){
	/*@params: none; @retvals: button_states (uint32_t)
	 * returns the states of the keys as one uint32, with c4 being the first
	 * bit and each key being the next bit. There are 17 keys so this is only
	 * scalable to 32.
	 */
	uint32_t button_states = 0;
	for (int i=0; i<6; i++){	//first chunk of buttons
		if (KP_PIN2 -> IDR &= POW2(i))	//checks each key to see if it's on
			button_states += POW2(i);	//if on, add its bit to button_states
	}
	for (int j=8; j<12; j++){	//second chunk
		if (KP_PIN2 -> IDR &= POW2(j))
			button_states += POW2(j-2);
	}
	for (int k=0; k<7; k++){	//third chunk
		if(KP_PIN -> IDR &= POW2(k))
			button_states += POW2(k+10);
	}
	return button_states;

}
int check_vol(void){
	/*@params: none; @retvals: vol (int)
	 * returns 1 if minus vol pressed, 2 if plus vol pressed,
	 * 3 if waveform select pressed, 0 otherwise
	 */
	if(KP_PIN -> IDR &= POW2(7))	//minus vol
		return 1;
	if(KP_PIN -> IDR &= POW2(9))	//plus vol
		return 2;
	if(KP_PIN -> IDR &= POW2(8))	//waveform
		return 3;
	return 0;
}
int get_num_keys(int prev_buttons){
	int num_keys = 0;
	for (int i=0; i<17; i++){
		if (prev_buttons & POW2(i)){
			num_keys ++;
		}
	}
	return num_keys;
}
int find_note(int prev_buttons){
	for (int i=0; i<17; i++){
			if (prev_buttons & POW2(i)){
				return i;
			}
		}
}
int* find_notes(int prev_buttons, int num_buttons){
	int* result = malloc(num_buttons * sizeof(int));
	int temp;
	int counter = 0;
	while (prev_buttons !=0){
		temp = find_note(prev_buttons);
		result[counter] = temp;
		counter ++;
		prev_buttons ^ temp;
	}
	return result;
}




