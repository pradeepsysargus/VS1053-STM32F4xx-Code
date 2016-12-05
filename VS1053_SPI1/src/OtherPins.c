
#include "stm32f4xx_conf.h"

void SetupPins()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); //168MHz frequency

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; //(MP3_XCS,MP3_XDCS)
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; 		// we want the pins to be an output
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; 	// this sets the GPIO modules clock speed
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP; 	// this sets the pin type to push / pull (as opposed to open drain)
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL; 	// this sets the pullup / pulldown resistors to be inactive
	GPIO_Init(GPIOB, &GPIO_InitStruct); 			// this finally passes all the values to the GPIO_Init function which takes care of setting the corresponding bits.
    
	GPIOB->BSRRL |= GPIO_Pin_0; // set PB0 high (MP3_XCS)
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE); //168MHz frequency

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;         // (MP3_RESET)
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; 		// we want the pins to be an output
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; 	// this sets the GPIO modules clock speed
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP; 	// this sets the pin type to push / pull (as opposed to open drain)
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL; 	// this sets the pullup / pulldown resistors to be inactive
	GPIO_Init(GPIOF, &GPIO_InitStruct); 			// this finally passes all the values to the GPIO_Init function which takes care of setting the corresponding bits.
	
	
	
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	
	/* Here the GPIOF module is initialized.
	 * We want to use PF11 as an input because
	 * the USER button on the board is connected
	 * between this pin and VCC.
	 */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;		  // (MP3_DREQ_IN) we want to configure PF11
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN; 	  // we want it to be an input
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;//this sets the GPIO modules clock speed
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;   // this sets the pin type to push / pull (as opposed to open drain)
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;   // this enables the pulldown resistor --> we want to detect a high level
	GPIO_Init(GPIOF, &GPIO_InitStruct);			  // this passes the configuration to the Init function which takes care of the low level stuff


	
}

void MP3_XCS(uint8_t state) // PB0
{
    if(state)
    {
        GPIOB->BSRRL = 0x0001; // ON OR SET PB0 
    }
    else
    {
        GPIOB->BSRRH = 0x0001; // OFF OR RESET PB0
    }
}
/* ------------------------------------------------------------------------- */
void MP3_XDCS(uint8_t state) // PB1
{
    if(state)
    {
		//USART_puts(USART1, "CSN is HIGH\r\n");
        GPIOB->BSRRL = 0x0002; // ON OR SET PB1
    }
    else
    {
		//USART_puts(USART1, "CSN is LOW\r\n");
       GPIOB->BSRRH = 0x0002; // OFF OR RESET PB1
    }
}


/* ------------------------------------------------------------------------- */
void MP3_RESET(uint8_t state) // PF12
{
    if(state)
    {
		//USART_puts(USART1, "CSN is HIGH\r\n");
        GPIOF->BSRRL = 0x1000; // ON OR SET PF12
    }
    else
    {
		//USART_puts(USART1, "CSN is LOW\r\n");
       GPIOF->BSRRH = 0x1000; // OFF OR RESET PF12
    }
}