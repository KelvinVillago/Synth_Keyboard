#include "dac.h"

int DAC_volt_conv(int millivolts)
{
  // tuning for voltage to code
  millivolts = MIN(millivolts, 3300);
  int value = ((millivolts * 4107) / (2 * VREF_MV))-4;
  value = MAX(value, 0);
  return value;
}

void DAC_write(int value_12bit)
{
  uint16_t cmd = value_12bit;
  cmd |= 0 << 13;  // set gain
  cmd |= (0x1) << 12;         // make vout available

  // wait for tx buff to be empty
  while (!(SPI1->SR & 0x2));
  SPI1->DR = cmd;
}

void DAC_setup()
{
  // setup bus
  RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

  RCC->AHB2ENR |= SPI_GPIO_RCC;

  // config SPI to alt function modes
  configurePin(SPI_CS_PIN, SPI_GPIO, CONFIG_MODE_ALT, CONFIG_TYPE_PUSHPULL,
                         CONFIG_SPEED_LOW, CONFIG_PUPD_NONE);
  configurePin(SPI_SCK_PIN, SPI_GPIO, CONFIG_MODE_ALT, CONFIG_TYPE_PUSHPULL,
                         CONFIG_SPEED_LOW, CONFIG_PUPD_NONE);
  configurePin(SPI_PICO_PIN, SPI_GPIO, CONFIG_MODE_ALT, CONFIG_TYPE_PUSHPULL,
                         CONFIG_SPEED_LOW, CONFIG_PUPD_NONE);
  configurePin(SPI_POCI_PIN, SPI_GPIO, CONFIG_MODE_ALT, CONFIG_TYPE_PUSHPULL,
                         CONFIG_SPEED_LOW, CONFIG_PUPD_NONE);

  // specify SPI as alt function
  SPI_GPIO->AFR[0] &= ~(0x000F << (SPI_PICO_PIN * 4)); // clear nibble for bit 7 AF
  SPI_GPIO->AFR[0] |=  (0x0005 << (SPI_PICO_PIN * 4)); // set b7 AF to SPI1 (fcn 5)

  SPI_GPIO->AFR[0] &= ~(0x000F << (SPI_POCI_PIN * 4));
  SPI_GPIO->AFR[0] |=  (0x0005 << (SPI_POCI_PIN * 4));

  SPI_GPIO->AFR[0] &= ~(0x000F << (SPI_SCK_PIN * 4));
  SPI_GPIO->AFR[0] |=  (0x0005 << (SPI_SCK_PIN * 4));

  SPI_GPIO->AFR[0] &= ~(0x000F << (SPI_CS_PIN * 4));
  SPI_GPIO->AFR[0] |=  (0x0005 << (SPI_CS_PIN * 4));

  SPI_init();
}

void SPI_init( void ) {
   // SPI config as specified @ STM32L4 RM0351 rev.9 p.1459
   // called by or with DAC_init()
   // build control registers CR1 & CR2 for SPI control of peripheral DAC
   // assumes no active SPI xmits & no recv data in process (BSY=0)
   // CR1 (reset value = 0x0000)
   SPI1->CR1 &= ~( SPI_CR1_SPE );               // disable SPI for config
   SPI1->CR1 &= ~( SPI_CR1_RXONLY );            // recv-only OFF
   SPI1->CR1 &= ~( SPI_CR1_LSBFIRST );          // data bit order MSb:LSb
   SPI1->CR1 &= ~( SPI_CR1_CPOL | SPI_CR1_CPHA ); // SCLK polarity:phase = 0:0
   SPI1->CR1 |=  SPI_CR1_MSTR;                // MCU is SPI controller
   // CR2 (reset value = 0x0700 : 8b data)
   SPI1->CR2 &= ~( SPI_CR2_TXEIE | SPI_CR2_RXNEIE ); // disable FIFO intrpts
   SPI1->CR2 &= ~( SPI_CR2_FRF);                // Moto frame format
   SPI1->CR2 |=  SPI_CR2_NSSP;                // auto-generate NSS pulse
   SPI1->CR2 |=  SPI_CR2_DS;                  // 16-bit data
   SPI1->CR2 |=  SPI_CR2_SSOE;                // enable SS output
   // CR1
   SPI1->CR1 |=  SPI_CR1_SPE;                 // re-enable SPI for ops
}
