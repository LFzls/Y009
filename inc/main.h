#ifndef __MAIN_H__
#define __MAIN_H__
/*----------------------------------------------------------------------------*/

#define	MaxGear					5//9
#define	MaxMode					8
#define TurnOffMode					0
#define WorkingMode					1
#define	WaitingFireMode				2
#define	FireingMode					3
#define	AgingMode					4
#define	WarningMode					5
#define WaitTurnOffMode				6

#define	VinVolError		1
#define	FanVError		2
#define	CapError		3
#define	NtcError		4
#define	LeakError		5
#define	OverError		6

#define	FireTimes			500000
#define	AgingTimes			10
#define	PageEPTimes			10
#define	StopTime			60

/*--------------------------------------------------------------*/\

#define	TurnOffMode				0
#define	StandbyMode				1
#define	WaitDischargeMode	2
#define	DisChargingMode		3
#define	AgingMode					4
#define	WarningMode				5




#define WaitCapChargeMode	10

#define	ReBoostVol		2000//1500
#define	SleepCapVol		360
//PSState define
#define	PSLow					0
#define	PSDc					1
#define	PSBattery			2

#define	VinVolError		1
#define	FanVError		2
#define	CapError		3
#define	NtcError		4
#define	LeakError		5
#define	OverError		6

#define	LedSolidOff		0
#define	LedSolidOn		1
#define	LedFlash		2

//output mode define
#define	LaserMode				0
#define	LaserCoolMode		1
#define	CoolMode				2
//cool mode
#define	CoolOn			1
#define	CoolOff			0

#define	Delay5M			300
#define	Delay30M		1800


/*----------------------------------------------------------------------------*/
#endif
