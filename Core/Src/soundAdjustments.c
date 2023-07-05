/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  **/

/* Includes ------------------------------------------------------------------*/
#include "soundAdjustments.h"


/*
 * This function is a general value updater. Given that volume and frequency are each changed by a set
 * of buttons, it makes sense to generalize the way in which they are changed. The parameters fed into
 * this function are the array, up state (0 or 1), down state, and the previous value.
 * The function assumes that a button press has already been detected.
 */

/*int getNew( const static array, int prevVal, int up, int down ) {
	if (up) {
		while (prevVal < (sizeof(array) - 1) ) {
			val = array[prevVol + 1];
		}
	}

	else if (down) {
		while (prevVal > array[0]) {
			val = array[prevVal - 1];
		}
	}

	else {
		val = prevVal; // stays the same
	}

	return val; // updated volume value
}*/


