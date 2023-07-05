#ifndef INC_LCD_H_
#define INC_LCD_H_

#define LCD_PORT GPIOE

#define DB4 GPIO_PIN_4
#define DB5 GPIO_PIN_5
#define DB6 GPIO_PIN_6
#define DB7 GPIO_PIN_7
#define LCD_DATA_BITS (DB4 | DB5 | DB6 | DB7)

#define LCD_RS GPIO_PIN_0
#define LCD_RW GPIO_PIN_2
#define LCD_EN GPIO_PIN_3
#define LCD_PINS (DB4 | DB5 | DB6 | DB7 | LCD_RS | LCD_RW | LCD_EN)

void Nybble();
void LCD_init(void);
void LCD_config();
void LCD_pulse_ENA(void);
void LCD_4b_command(uint8_t command);
void LCD_command(uint8_t command);
void LCD_write_char(uint8_t command);
void LCD_write_str(char *str);

#endif /* INC_LCD_H_ */
