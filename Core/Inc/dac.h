#ifndef INC_DAC_H_
#define INC_DAC_H_
#include "stm32l4xx_hal.h"
#include "main.h"

void DAC_write(int value_12bit);
int DAC_volt_conv(int millivolts);
void DAC_setup(void);
void SPI_init( void );


// DAC ref voltage in millivolts
#define VREF_MV 2048

// SPI pins
#define SPI_GPIO_RCC RCC_AHB2ENR_GPIOAEN
#define SPI_GPIO GPIOA
#define SPI_PICO_PIN 7
#define SPI_POCI_PIN 6
#define SPI_SCK_PIN 5
#define SPI_CS_PIN 4

/* DAC wiring:
 * 		Vdd	|   v	|	VOUT
 * 		CS	|		|	VSS
 * 		SCK	|		|	SHDN
 * 		SDI	|		|	LDAC
 *
 *  	3.3	|   v	|	VOUT
 * 		PA4	|		|	GND
 * 		PA5	|		|	3.3
 * 		PA7	|		|	GND
 */

#endif
