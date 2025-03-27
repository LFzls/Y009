/******************************************************************************
 ** Define to prevent recursive inclusion
 ******************************************************************************/
#ifndef _KEYMICFUNCTION_H
#define _KEYMICFUNCTION_H
/*-------------------------------*/
#include "Global.h"
/*----------------------------------------------*/
extern uint8_t  MicScnCnt;
extern ByteBit MicInfoFlag;
#define bMicNew             MicInfoFlag.Bits.Bit0
#define bMicOld             MicInfoFlag.Bits.Bit1

extern void MicIni(void);
extern void MicScan(void);
/*-------------------------------*/
extern uint8_t KeyScanCnt,KeyCounter;
extern uint16_t KeyDelayCnt,KeyCntDelay;
/*-------------------------------*/
extern ByteBit KeyInfoFlag;
#define bKeyNew             KeyInfoFlag.Bits.Bit0
#define bKeyOld             KeyInfoFlag.Bits.Bit1
#define bKeySmoke           KeyInfoFlag.Bits.Bit2
#define bKeyEnable		    KeyInfoFlag.Bits.Bit3


extern void KeyIni(void);
extern void KeyScan(void);
/*-------------------------------*/
extern uint8_t SwScanCnt,SwCounter;
extern uint8_t SwStateNew,SwStateOld;

#define bSwNew             SwInfoFlag.Bits.Bit0
#define bSwOld             SwInfoFlag.Bits.Bit1
extern void SwitchIni(void);
extern void SwitchScan(void);
extern void IniMainTurnOn(void);
extern void IniMainTurnOff(void);
/*-------------------------------*/
#endif
