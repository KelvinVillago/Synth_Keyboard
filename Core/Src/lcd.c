#include <stdint.h>
#include <string.h>
#include "delay.h"
#include "lcd.h"
#include "main.h"

void LCD_config(){
	RCC->AHB2ENR |= (RCC_AHB2ENR_GPIOEEN);
	LCD_PORT->MODER   &= ~(GPIO_MODER_MODE0 | GPIO_MODER_MODE2 | GPIO_MODER_MODE3 | GPIO_MODER_MODE4
			  | GPIO_MODER_MODE5 | GPIO_MODER_MODE6 | GPIO_MODER_MODE7);
	LCD_PORT->MODER   |=  (GPIO_MODER_MODE0_0 | GPIO_MODER_MODE2_0 | GPIO_MODER_MODE3_0 | GPIO_MODER_MODE4_0
		  | GPIO_MODER_MODE5_0 | GPIO_MODER_MODE6_0 | GPIO_MODER_MODE7_0);
	LCD_PORT->OTYPER  &= ~(GPIO_OTYPER_OT0 | GPIO_OTYPER_OT2 | GPIO_OTYPER_OT3 | GPIO_OTYPER_OT4
		  | GPIO_OTYPER_OT5 | GPIO_OTYPER_OT6 | GPIO_OTYPER_OT7);

	SysTick_Init();
}

void LCD_init( void )  {   // RCC & GPIO config removed - leverage A1, A2 code

    LCD_PORT->BRR = 0xFF;
    delay_us(40000*10);                    // power-up wait 40 ms
    LCD_PORT->ODR = 0x30;               // HI 4b of 8b cmd, low nibble = X
    delay_us(5000*10);
    Nybble();
    delay_us(2000*10);                     //must wait 160us, busy flag not available
    Nybble();                           //command 0x30 = Wake up #2
    delay_us(2000*10);                     //must wait 160us, busy flag not available
    Nybble();							//command 0x30 = Wake up #3
    delay_us(2000*10); 					//can check busy flag now instead of delay
    LCD_PORT->ODR = 0x20;
    Nybble();

    LCD_command(0x28);
    LCD_command(0x10);
    LCD_command(0x0F);
    LCD_command(0x06);
    LCD_command(0x02);
}

void Nybble()
// function from datasheet
{
	LCD_PORT->BSRR = LCD_EN;
	delay_us(1000*10);
	LCD_PORT->BRR = LCD_EN;
}

void LCD_pulse_ENA( void )  {
// ENAble line sends command on falling edge
// set to restore default then clear to trigger
   LCD_PORT->ODR   |= ( LCD_EN );         	// ENABLE = HI
   delay_us( 200 );                           // TDDR > 320 ns
   LCD_PORT->ODR   &= ~( LCD_EN );          // ENABLE = LOW
   delay_us( 200 );
}

void LCD_4b_command(uint8_t command)  {
// LCD command using high nibble only - used for 'wake-up' 0x30 commands
   LCD_PORT->ODR   &= ~( LCD_DATA_BITS ); 		// clear DATA bits
   LCD_PORT->ODR   |= ( command >> 4 );  		// DATA = command
   delay_us( 200 );
   LCD_pulse_ENA( );
}

void LCD_command(uint8_t command)  {
// send command to LCD in 4-bit instruction mode
// HIGH nibble then LOW nibble, timing sensitive
   LCD_PORT->BRR   = ( LCD_DATA_BITS );             		  // isolate cmd bits
   LCD_PORT->BRR   = (LCD_RS);
   LCD_PORT->ODR   |= ( command & LCD_DATA_BITS ); 			  // HIGH shifted low
   delay_us( 200 );
   LCD_pulse_ENA( );                                   		  // latch HIGH NIBBLE

   LCD_PORT->BRR   = ( LCD_DATA_BITS );             		  // isolate cmd bits
   LCD_PORT->ODR   |= ( (command<<4) & LCD_DATA_BITS );       // LOW nibble
   delay_us( 200 );
   LCD_pulse_ENA( );                                  		  // latch LOW NIBBLE
}

void LCD_write_char( uint8_t letter )  {
// calls LCD_command() w/char data; assumes all ctrl bits set LO in LCD_init()
	LCD_PORT->BRR   = ( LCD_DATA_BITS );              		 // isolate cmd bits
	LCD_PORT->BSRR   = (LCD_RS);
	LCD_PORT->ODR   |= ( letter & LCD_DATA_BITS ); 			 // HIGH shifted low
	delay_us( 200 );
	LCD_pulse_ENA( );                                   	 // latch HIGH NIBBLE

	LCD_PORT->BRR   = ( LCD_DATA_BITS );              		 // isolate cmd bits
	LCD_PORT->ODR   |= ( (letter<<4) & LCD_DATA_BITS );      // LOW nibble
	delay_us( 200 );
	LCD_pulse_ENA( );
}

void LCD_write_str(char *str)
{
	if(strlen(str) <= 16){									// max length is 16 characters
		for(int i = 0; i < strlen(str); i++){
			LCD_write_char((uint8_t) str[i]);				// call write_str as many times as char array
		}
	}
}


