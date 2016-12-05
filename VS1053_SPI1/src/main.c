#include <stdio.h>
#include <string.h>
#include "common_api.h"
//#include "LoggerInterface.h"
//#include "RFTagInterface.h"
#include "DebugPort.h"
//#include "nrf24_1.h"
//#include "GainSwitchPins.h"
#include "stm32f4xx_conf.h"



volatile int DelayTimer = 0;
volatile int testCounter = 0;
volatile int oneSecTimer = 0;
volatile int oneSecAction = 0;



uint8_t i = 0;

  
 
void DelayHandler(void)
{
	if (DelayTimer != 0x00)
	{ 
		DelayTimer--;
	}
}


void TestTimer(void)
{
     
	  // printf(" Test Timer function ");
		oneSecTimer++;
        if(oneSecTimer == 2000) { // for  2 sec .
          oneSecTimer = 0;
          oneSecAction = 1;
        }
		
}

void TickHandler(uint32_t data)
{
	// Blocking Timer Handling
		DelayHandler();
		//RFTagInterfaceEOPHandler();
        TestTimer();
}

void Delay(uint32_t nTime)
{ 
	DelayTimer = nTime;	
	while(DelayTimer != 0);
}

 /* void init_GPIO(void){
	
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_6 | GPIO_Pin_5 | GPIO_Pin_4; // we want to configure all LED GPIO pins
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; 		// we want the pins to be an output
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; 	// this sets the GPIO modules clock speed
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP; 	// this sets the pin type to push / pull (as opposed to open drain)
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL; 	// this sets the pullup / pulldown resistors to be inactive
	GPIO_Init(GPIOA, &GPIO_InitStruct); 			// this finally passes all the values to the GPIO_Init function which takes care of setting the corresponding bits.
}
   */


   /*
	void init_USART1(uint32_t baudrate){
	
	GPIO_InitTypeDef GPIO_InitStruct; // this is for the GPIO pins used as TX and RX
	USART_InitTypeDef USART_InitStruct; // this is for the USART1 initilization
	NVIC_InitTypeDef NVIC_InitStructure; // this is used to configure the NVIC (nested vector interrupt controller)
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; // Pins 9 (TX) and 10 (RX) are used
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF; 			// the pins are configured as alternate function so the USART peripheral has access to them
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;		// this defines the IO speed and has nothing to do with the baudrate!
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;			// this defines the output type as push pull mode (as opposed to open drain)
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;			// this activates the pullup resistors on the IO pins
	GPIO_Init(GPIOA, &GPIO_InitStruct);					// now all the values are passed to the GPIO_Init() function which sets the GPIO registers
	
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1); //
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
	
	
	USART_InitStruct.USART_BaudRate = baudrate;				// the baudrate is set to the value we passed into this init function
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;// we want the data frame size to be 8 bits (standard)
	USART_InitStruct.USART_StopBits = USART_StopBits_1;		// we want 1 stop bit (standard)
	USART_InitStruct.USART_Parity = USART_Parity_No;		// we don't want a parity bit (standard)
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // we don't want flow control (standard)
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; // we want to enable the transmitter and the receiver
	USART_Init(USART1, &USART_InitStruct);					// again all the properties are passed to the USART_Init function which takes care of all the bit setting
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); // enable the USART1 receive interrupt 
	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;		 // we want to configure the USART1 interrupts
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;// this sets the priority group of the USART1 interrupts
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		 // this sets the subpriority inside the group
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			 // the USART1 interrupts are globally enabled
	NVIC_Init(&NVIC_InitStructure);							 // the properties are passed to the NVIC_Init function which takes care of the low level stuff	

	// finally this enables the complete USART1 peripheral
	USART_Cmd(USART1, ENABLE);
} */

/*
void USART_puts(USART_TypeDef* USARTx, volatile char *s){

	while(*s){
		// wait until data register is empty
		while( !(USARTx->SR & 0x00000040) ); 
		USART_SendData(USARTx, *s);
		*s++;
	}
}  */


 int main()
 {
	    uint16_t a=0;
	
	Debug_uart1_Init();
 	if (SysTick_Config(SystemCoreClock / 1000))
	{ 
		/* Capture error */ 
		while (1);
	}       // Intializing DelayTimer to Zero
	Delay(0);
	
        
        // turn off buffers, so IO occurs immediately
        setvbuf(stdin, NULL, _IONBF, 0);
        setvbuf(stdout, NULL, _IONBF, 0);
        setvbuf(stderr, NULL, _IONBF, 0);
      
		printf("Hello World Again\r\n");        
       
		//init_USART1(9600); // initialize USART1 @ 9600 baud
        
       // USART_puts(USART1, "Init complete! Hello World!\r\n"); // just send a message to indicate that it works
       
		SetupPins();

		spi1Init();     
        printf("SPI1 Init\r\n");
		
		vs1053_setup();
		printf("After vs1053_setup()..\r\n");
		vs1053_sayHello();
	    printf("After vs1053_sayHello()..\r\n");
		
		while (1) 
	{
				vs1053_sayHello();
                Delay(1000);
		
	} // end of while loop

	return 0;
}
  


