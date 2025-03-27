#ifndef _BATTERYFUNCTION_H
#define _BATTERYFUNCTION_H
/*----------------------------------------------------------------------------*/
#include "Global.h"

/*-------------------------------------------------------------------------*/
extern	uint8_t BatPowPercent,BatLevel;
extern	uint8_t BatState,LowBatCounter,BatCounter,BatPowCnt;
extern	uint16_t	RefVddValue,BatVolValue,UsbVolValue;
extern	uint8_t BatScanCnt,BatODCounter;


extern	uint8_t UsbState,UsbCounter,ChargeStep;
extern	uint8_t ChrgLevel;
extern	uint16_t ChargeTime;

extern ByteBit      BatFlag,UsbFlag,OilFlag;
/*--------------------------------------------------------------*/
//BatFlag
#define bBatOD				BatFlag.Bits.Bit0
#define bBatODNew			BatFlag.Bits.Bit1
#define bBatODOld			BatFlag.Bits.Bit2

#define bBatStateNew		BatFlag.Bits.Bit5
#define bBatStateOld		BatFlag.Bits.Bit6
#define bBatLow				BatFlag.Bits.Bit7
//OilFlag           //还没使用，等后续看要不要使用
#define OilStateNew		OilFlag.Bits.Bit0  
#define OilStateOld		OilFlag.Bits.Bit1
#define OilLow			OilFlag.Bits.Bit2

//UsbFlag
#define bUsbNew				UsbFlag.Bits.Bit0
#define bUsbOld				UsbFlag.Bits.Bit1
#define bUsbAD				UsbFlag.Bits.Bit2

/*--------------------------------------------------------------*/
#define UsbNcVol			4300
#define UsbOkVol			6150
#define UsbOvpVol			8000//7000
#define UsbNcAd				4000
#define UsbFullAd			282

#define UsbNc					0
#define UsbOk					1
#define UsbHigh				2
#define UsbOvp				3

/*--------------------------------------------------------------*/
/*--------------------------------------------------------------*/
/*--------------------------------------------------------------*/
/*--------------------------------------------------------------*/
#define BatPercentMax				100
#define BatPerStep					1
#define BatLevelMax         		4
#define ChargeTimeMax				4500	//75minutes
/*--------------------------------------------------------------*/
#define BatFullVol						4150
#define BatFullVol1						4000

#define LowBatVoltage					3400
#define LowBatVoltage1				3200
#define ODBatVoltage					2300
#define ShortBatVoltage				2600
#define BalVolOffset					145
#define BalVolChgOffset				45


/*--------------------------------------------------------------*/
extern	void ReadBatteryVoltage(void);
extern	void CheckBatteryState(void);
extern	void CheckBatODState(void);

extern void CheckChgBatPercent(void);
extern void CheckChargeState(void);
extern	void IniChargeMode(void);
extern	void CheckUsbState(void);

extern uint8_t CalBatPercent(uint16_t VData);
extern void CalBatLevel(void);
extern void BatChargeFunction(void);
/*--------------------------------------------------------------*/

/*--------------------------------------------------------------*/
#endif
