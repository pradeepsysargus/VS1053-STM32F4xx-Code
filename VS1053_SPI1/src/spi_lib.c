/*
NVIS Inc.
Jianyi Liu
Created		Jul 1, 2010
Modified	Jul 1, 2010
source for spi device drivers
*/
#include "spi_lib.h"
//#include <p24hj128gp202.h>
//#include "delay.h"
//#include "spi.h"

//write using selectable ports
unsigned char spiWrite( unsigned port, unsigned char i)
{
    switch(port){
        default:
            case 1: return spi1Write(i);
        #if defined(spi_v1_1) || defined (spi_v1_3)
            case 2: return spi2Write(i);
        #endif
        #if defined (spi_v1_3)
            case 3: return spi3Write(i);
        #endif
    }		
}	

//init Spis
void spi1Init(){
   // OpenSPI1(0x0120 | prescale, 0x0000, 0x8000);

   	GPIO_InitTypeDef GPIO_InitStruct;
	SPI_InitTypeDef SPI_InitStruct;
	
	// enable clock for used IO pins
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	/* configure pins used by SPI1
	 * PA5 = SCK
	 * PA6 = MISO
	 * PA7 = MOSI
	 */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_6 | GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	// connect SPI1 pins to SPI alternate function
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);
	
	// enable clock for used IO pins
	/* RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	// Configure the chip select pin
	//   in this case we will use PE7, Now PA4. 
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	GPIOE->BSRRL |= GPIO_Pin_4; // set PA4 high */
	
	// enable peripheral clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	
	/* configure SPI1 in Mode 0 
	 * CPOL = 0 --> clock is low when idle
	 * CPHA = 0 --> data is sampled at the first edge
	 */
	SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex; // set to full duplex mode, seperate MOSI and MISO lines
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;     // transmit in master mode, NSS pin has to be always high
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b; // one packet of data is 8 bits wide
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;        // clock is low when idle
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;      // data sampled at first edge
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft | SPI_NSSInternalSoft_Set; // set the NSS management to internal and pull internal NSS high
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16; // SPI frequency is APB2 frequency / 16 = 84 /16 =  5.25 Mhz.
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;// data is transmitted MSB first
	SPI_Init(SPI1, &SPI_InitStruct); 
	
	SPI_Cmd(SPI1, ENABLE); // enable SPI1
   
 }	

// send one byte of data and receive one back at the same time
uint8_t spi1Write( uint8_t data )
{
    // write to buffer for TX, wait for transfer, read
   // SPI1BUF = i;

   // while(!SPI1STATbits.SPIRBF);
   // return SPI1BUF;
    SPI1->DR = data; // write data to be transmitted to the SPI data register
	while( !(SPI1->SR & SPI_I2S_FLAG_TXE) ); // wait until transmit complete
	while( !(SPI1->SR & SPI_I2S_FLAG_RXNE) ); // wait until receive complete
	while( SPI1->SR & SPI_I2S_FLAG_BSY ); // wait until SPI is not busy anymore
	return SPI1->DR; // return received data from SPI data register
   
}

void spi2Init(unsigned int prescale){
    //OpenSPI2(0x0120 | prescale, 0x0000, 0x8000);
}	

// send one byte of data and receive one back at the same time
unsigned char spi2Write( unsigned char i )
{
    // write to buffer for TX, wait for transfer, read
    //SPI2BUF = i;
    //while(!SPI2STATbits.SPIRBF);
    //return SPI2BUF;
}//spiWrite2
