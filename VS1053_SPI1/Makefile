# put your *.o targets here, make should handle the rest!

#SRCS = main.c system_stm32f4xx.c stm32f4xx_it.c newlib_stubs.c DebugPort.c HostInterface.c rfid-host.c buz_led_orm.c
#SRCS = main.c system_stm32f4xx.c stm32f4xx_it.c DebugPort.c newlib_stubs.c LoggerInterface.c LoggerPacketHandler.c nrf24_1.c nrf24_2.c radioPinFunctions_1.c radioPinFunctions_2.c RFID1_SPI1.c RFID2_SPI2.c GainSwitchPins.c AttenuatorPins.c NordicIRQPins.c BuzzerPWMInit.c PWMLEDs.c
SRCS = main.c system_stm32f4xx.c stm32f4xx_it.c DebugPort.c newlib_stubs.c vs1053.c spi_lib.c OtherPins.c
# all the files will be generated with this name (main.elf, main.bin, main.hex, etc)

PROJ_NAME=main

# that's it, no need to change anything below this line!

###################################################

CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy

CFLAGS  = -g -O2 -Wall -Tstm32_flash.ld 
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m4 -mthumb-interwork
CFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16

ifeq ('$(RELEASE)','1')
	else
	CFLAGS += -DDEBUG
endif

###################################################

vpath %.c src
vpath %.a lib

ROOT=$(shell pwd)

CFLAGS += -Iinc -Ilib -Ilib/inc 
CFLAGS += -Ilib/inc/core -Ilib/inc/peripherals 

SRCS += lib/startup_stm32f4xx.s # add startup file to build

OBJS = $(SRCS:.c=.o)

###################################################

.PHONY: lib proj

all: lib proj

lib:
	$(MAKE) -C lib

proj: 	$(PROJ_NAME).elf

$(PROJ_NAME).elf: $(SRCS)
	$(CC) $(CFLAGS) $^ -Wl,-Map=$(PROJ_NAME).map -o $@ -Llib -lstm32f4
	$(OBJCOPY) -O ihex $(PROJ_NAME).elf $(PROJ_NAME).hex
	$(OBJCOPY) -O binary $(PROJ_NAME).elf $(PROJ_NAME).bin

clean:
	$(MAKE) -C lib clean
	rm -f $(PROJ_NAME).elf
	rm -f $(PROJ_NAME).hex
	rm -f $(PROJ_NAME).bin
