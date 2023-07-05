/**
  ******************************************************************************
  * @file           : convolution.c
  * @brief          : Convolution Operation
  ******************************************************************************
  */
#include "convolution.h"

/*
 ******************************************************************************
 * function  : convolution
 * purpose   : This function performs discrete convolution with two arrays. It was
 * 			   adapted from code generated on ChatGPT. As parameters, it takes the
 * 			   two input arrays, which represent the two keys pressed. It also
 * 			   takes a defined output array which will be iterated through with new
 * 			   values.
 * params in : input1, input2, output (arrays)
 * ret vals  : none
 * project   : P4 - Synthezizer Keyboard
 ******************************************************************************
 */
void* convolution(uint16_t input1[], uint16_t input2[]) {
    int i, j;
    uint16_t output[sizeof(input1)+sizeof(input2)-1];

    // Initialize output array with zeros
    for (i = 0; i < sizeof(input1) + sizeof(input2) - 1; i++) {
        output[i] = 0;
    }

    // Perform convolution
    for (i = 0; i < sizeof(input1); i++) {
        for (j = 0; j < sizeof(input2); j++) {
            output[i + j] += input1[i] * input2[j];
        }
    }
}
