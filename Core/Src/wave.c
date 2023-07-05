/*
 * wave.c
 *
 *  Created on: Jun 6, 2023
 *      Author: zakth
 */
#include "wave.h"
#include <math.h>
int waveSamples[10000];
int waveIx = 0;
int waveIxMax;
int period = 0;
int step = 0;
int polarity; // set to 0 for positive, 1 for negative
int squOut; // If square wave, then set to 0 to output LO, 1 for HI.

void clearWave() {
	memset(waveSamples, 0, sizeof(waveSamples)); // writes 0 to all values of the wave array
}

void createWave(int freq, int waveType, int duty)
// Supplemental function to write the array for the waves. Parameters passed in
//	are the type of wave to generate and the frequency of the wave as well as
//	duty cycle for square wave. The saw wave is determined by a gloabl polarity variable
{
  clearWave();
	switch (freq) { // Determine sample amounts for different frequencies
	case 100:
	  waveIxMax = 0;
		break;
	case 200:
	  waveIxMax = 1;
		break;
	case 300:
	  waveIxMax = 2;
		break;
	case 400:
	  waveIxMax = 3;
		break;
	case 500:
	  waveIxMax = 4;
		break;
	default:
	  waveIxMax = 0;
		break;
	}
	switch (freq) {	//type
	case 0: {
		for (int i = 0; i < waveIxMax; i++) {
			waveSamples[i] = (1500 * sin(2 * M_PI * ((float)i / waveIxMax)))
					+ 1500;
		}
	}
	break;
	case 1: {
		switch (polarity) {
		case 0: {
			for (int i = 0; i < waveIxMax; i++) {
				waveSamples[i] = (3 * i * 1000) / waveIxMax;
			}
		}
		break;
		case 1: {
			for (int i = 0; i < waveIxMax; i++) {
				waveSamples[i] = ((-3 * 1000 * i) / waveIxMax) + 3000;
			}
		}
		break;
		}
	}
	break;
	case 2: {
		int samples = (waveIxMax * duty) / 100;
		for (int i = 0; i < samples; i++) {
			waveSamples[i] = 3000;
		}
	}
	break;
	}
}
