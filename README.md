# VS1053-STM32F4xx-Code
VS1053 audio codec (SPI interface) with STM32F4xx(STM32F407ZET6 chipset) - Project template in Linux Platform.

This is the project template or a project example in Linux Platform that demonstrates the working of a vs1053 audio playing.
You need to have tool chain of the STM32F407ZET6 installed on your host linux PC to compile the project.


The audio that is played is in the array 'HelloMP3[]' which is defined in vs1053.c file.
You will get an output sound of a person saying 'hello' continuously every one second at the audio jack of the VS1053 board.


Following are the hardware connections between STM32F407ZET6 and VS1053:

STM32F407ZET6             VS1053
-------------             ------
PB0             --->      XCS
PB1             --->      XDCS
PF11            --->      DREQ-IN
PF12            --->      RESET
PA5             --->      SCK
PA6             --->      MISO
PA7             --->      MOSI

Note that PB0,PB1,PF12 are output pins, DREQ-IN is input to the STM32F4xx.
PA5,PA6,PA7 are SPI1 interface with VS1053.

printf() is used to display messages on the console.
It is using USART1 with baudrate of 115200. The files related to printf are DebugPort.c and newlib_stubs.c .
The Delay function is implemented using a systick handler.


You will get few warning messages about implicit declaration of the functions..!


