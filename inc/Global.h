
#ifndef _Global_H
#define _Global_H
/*--------------------------------------------------------------*/
/* Signed Types */
typedef signed char     int8_t;
typedef short           int16_t;
typedef long            int32_t;

/* Unsigned Types */
typedef	unsigned char 	uint8_t;
typedef	unsigned short 	uint16_t;
typedef	unsigned long 	uint32_t;
/*--------------------------------------------------------------*/
typedef union
{
  uint8_t Byte;
  struct
  {
    uint8_t Bit0 :1;  //
    uint8_t Bit1 :1;
    uint8_t Bit2 :1;
    uint8_t Bit3 :1;
    uint8_t Bit4 :1;
    uint8_t Bit5 :1;
    uint8_t Bit6 :1;
    uint8_t Bit7 :1;
  } Bits;
} ByteBit;
/*--------------------------------------------------------------*/
#include <intrins.h>
#include "REGtenxTM52F1376.h"
#include "TM52F1376_bsp.h"

#include "inc/Main.h"
#include "inc/Peripheral.h"
#include "inc/user_define.h"
#include "inc/AppConfig.h"
#include "inc/KeyMicFunction.h"
#include "inc/BatteryFunction.h"
#include "inc/SmokeFunction.h"
#include "inc/LedFunction.h"
#include "inc/SubFunction.h"
#include "inc/AdcFunction.h"



#define	WDT_Clear()		CLR_WDT

/*--------------------------------------------------------------*/
#endif

