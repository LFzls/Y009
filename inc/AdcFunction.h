#ifndef __ADCFUNCTION_H__
#define __ADCFUNCTION_H__
/*----------------------------------------------------------------------------*/
#include "Global.h"
/*----------------------------------------------------------------------------*/
//extern	uint8_t	TemState,TemCounter;
//extern uint16_t	VinVoltageValue,VinCurrentValue,ResNtcValue,FanVoltageValue,VoutVoltageValue;
/*----------------------------------------------------------------------------*/


//Ntc value define
#define	NtcTemHigh					0
#define	NtcTemNormal				1
#define	TemLow							0
#define	TemNormal						1
#define	TemHigh							2

#define NtcResHigh	2070//85 //7078//110C 9544//100 15323//85C 
#define NtcResHighR	3053//55 //43902//55C 

/*----------------------------------------------------------------------------*/
extern void AdcInitialize(void);
extern uint16_t ReadAdResult(uint8_t AdcChannel);
extern uint16_t ADCRead(uint8_t AdcNumber);
extern uint16_t  ADCModule(uint8_t AdcChannel,uint8_t AdcNumber);
extern unsigned int  HAL_ADC_Sample(unsigned char ADC_CHx,unsigned char Filter);
/*----------------------------------------------------------------------------*/
#endif
