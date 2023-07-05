/*
 * keyboard.h
 *
 *  Created on: Jun 5, 2023
 *      Author: zakth
 */

#include "main.h"

#ifndef INC_KEYBOARD_H_
#define INC_KEYBOARD_H_

uint32_t check_buttons(void);
int check_vol(void);
void init_keyboard(void);
/*
#define char* notes[20]  {"C4", "Cs4", "D4", "Ds4", "E4", "F4", "Fs4", "G4", "Gs4", "A4", "As4", "B4", "C5", "Cs5", "D5", "Ds5", "E5", "F5", "Fs5", "G5"}
#define float freqs[20]  {261.6256, 277.1826, 293.6648, 311.1270, 329.6276, 349.2282, 369.9944, 391.9954, 	415.3047, 440.0000, 466.1638, 493.8833, 523.2511, 554.3653, 587.3295, 622.2540, 659.2551, 698.4565, 739.9888, 830.6094}
*/
#define KP_PIN GPIOD
#define KP_CLK RCC_AHB2ENR_GPIODEN
#define KP_PIN2 GPIOC
#define KP_CLK2 RCC_AHB2ENR_GPIOCEN

#define POW2(X) 		(1<<X)	//Power of 2



#endif /* INC_KEYBOARD_H_ */
