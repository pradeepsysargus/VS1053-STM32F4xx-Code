#ifndef __COMMON_API_H
#define __COMMON_API_H

#include <stdio.h>
#include <string.h>

#include "stm32f4xx.h"
#include "misc.h"

#define SYSTEM_CONFIG_MAGIC_NUMBER      0xBEEF
#define SYSTEM_CONFIG_CURRENT_VERSION_NUMBER 0x0001

#define SYSTEM_COMMAND_FAILURE_REASON_CRC_FAIL                  0x01
#define SYSTEM_COMMAND_FAILURE_REASON_UNKNOWN_COMMND    0x02

#ifdef DEBUG
#define APP_PRINTF  printf
#else
#define APP_PRINTF 
#endif

typedef struct {
        uint16_t                MagicNumber; // 0xBEEF
        uint16_t                versionStr;  // 0x0001
        uint8_t                 readerName[8];
        uint8_t                 parameterArray[52]; // Change as per application
}tSystemConfiguration;

extern tSystemConfiguration gSystemConfiguration;

extern void fSystemConfigurationToDefault(void);
extern uint16_t calculateCRC(uint8_t *ptr, uint8_t len);

extern void LoggerStuffBytes(uint8_t count);
extern void LoggerPacketHandler(void);

extern void RFTagStuffBytes(uint8_t count);
extern void RFTagPacketHandler(void);
extern void dumpPacket(char* buffer,int count);

#endif
