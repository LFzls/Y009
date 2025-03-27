/*--------------------------------------------------------------*/
#ifndef _SMOKEFUNCTION_H
#define _SMOKEFUNCTION_H
/*--------------------------------------------------------------*/
/******************************************************************************
 ** Include files
 ******************************************************************************/
#include "Global.h"
/*--------------------------------------------------------------*/
extern uint8_t SmokeMode,ChanNum;
extern uint16_t RefVolValue;

extern uint8_t	PwmPeriodCnt,PwmDuty;
extern uint16_t AdOutValue,AdOutValueSum;


extern uint8_t	Pwm2PeriodCnt,Pwm2Duty;
extern uint16_t AdOut2Value,AdOut2ValueSum;
extern const uint16_t code RefVolTab[];
extern const uint16_t code  RefVolFallTab[];
extern const uint8_t  code  RefPowerTab[];
/*--------------------------------------------------------------*/
extern ByteBit      SmokeFlag;
/*-------------------------------------------------*/
#define bWorkStart			SmokeFlag.Bits.Bit0
#define bShortC					SmokeFlag.Bits.Bit1
#define bShortC2				SmokeFlag.Bits.Bit2
#define bOutCheck				SmokeFlag.Bits.Bit3

#define bOut2Check			SmokeFlag.Bits.Bit4
#define bSmokeOut				SmokeFlag.Bits.Bit5
#define bSmokeOut2			SmokeFlag.Bits.Bit6
#define bBatCheck				SmokeFlag.Bits.Bit7
/*-------------------------------------------------*/
extern ByteBit  		 	SmokeFlag1;
#define bMosOn				SmokeFlag1.Bits.Bit0
#define bMos2On				SmokeFlag1.Bits.Bit1

#define bPowerFall		SmokeFlag1.Bits.Bit2
/*-------------------------------------------------*/
//SmokeMode
#define ModeECO				0
#define ModeNORM			1
#define ModeMAX				2



/*-------------------------------------------------*/
extern void ReadRefOutValue(void);
extern uint8_t CalOutPwmDuty(uint16_t VSource,uint16_t VRef);

extern void IniSmokeMode(void);
extern void	MainSmokeMode(void);
extern void StopOutput(void);


extern void ShortCheck(void);

extern void CheckLoadVoltage(void);
extern void AdjustLoadVoltage(void);
extern void CheckLoad2Voltage(void);
extern void AdjustLoad2Voltage(void);
extern void MainPreHeatFunction(void);
extern void CheckSmokeBatState(void);
extern void CheckHeatOutput(void);
extern void SwitchChannelHeat(void);
/*--------------------------------------------------------------*/
#endif
