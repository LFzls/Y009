#ifndef _LEDFUNCTION_H
#define _LEDFUNCTION_H
/*----------------------------------------------------------------------------*/
#include "Global.h"
/*-------------------------------------------------------------------------*/
extern	uint8_t LedMode,LedCounter,LedStep;
extern	uint8_t LedPeriod,LedDuty,LedDutyTime,LedScanT;
extern	uint8_t LedPeriod1,LedDuty1;
extern	uint8_t LedPeriod2,LedDuty2;
extern	uint8_t LedOffDelayCnt1;
extern	uint8_t LedOffDelayCnt2;

extern	uint8_t LedRenewDelay,LedOffDelayCnt;
extern	uint16_t LedDelayCnt;

extern	uint8_t LedPMode,LedPCounter,LedPStep,LedPStep1,LedPRenewFlag,LedPRenewDelay;

extern	uint16_t LedPDelay;
//extern const uint8_t LedDigTab[];

#if(LedPComN<=8)
extern uint8_t LedPBufferData[LedPComN];
extern uint8_t LedPScanData[LedPComN];
#else
extern uint16_t LedPBufferData[LedPComN];
extern uint16_t LedPScanData[LedPComN];
#endif

/*-------------------------------------------------------------------------*/
extern ByteBit     				LedPFlag;
#define bLedPFlash				LedPFlag.Bits.Bit0		//Led panel flash flag
#define bLedPPorS				LedPFlag.Bits.Bit1		//0=power,1=second
#define bLedPRenewD				LedPFlag.Bits.Bit2		//Scan data renew flag
#define bLedPStepID				LedPFlag.Bits.Bit3		//Step is inc or dec

/*-------------------------------------------------------------------------*/
#define LedPSolidOff			0
#define LedPSolidOn				1
#define LedPPowerOn				2
#define LedPSmoking				3
#define LedPUsbIn			    4
#define LedPCharging			5
#define LedPStandby				6
#define LedPBatLow				7
#define LedPShortC				8
#define LedPTimeOver			9
#define LedPSmokeOver			10
#define LedPLoadCon				11
#define LedPLoadNC				12
#define LedPWarning				13
#define LedPOilPercent			15
#define LedPAllFlash			16
#define LedPTurnOn				17
#define LedPTurnOff				18
#define LedPScreenOn			19
#define LedPOilLow			    20
#define LedPDebug				0xff

#define LEDP_DEBUG 				InitializeLedPMode(LedPDebug,0)
#define LEDP_ALLON				InitializeLedPMode(LedPSolidOn,0);IniLedPBreathe(0)
#define LEDP_ALLOFF				InitializeLedPMode(LedPSolidOff,0);IniLedPBreathe(0)
#define LEDP_POWERON			InitializeLedPMode(LedPSolidOn,0);IniLedPBreathe(0)
#define LEDP_STANDBY			InitializeLedPMode(LedPStandby,0);IniLedPBreathe(1)
#define LEDP_STANDBY1			InitializeLedPMode(LedPStandby,0);IniLedPBreathe(1)
#define LEDP_SMOKING			InitializeLedPMode(LedPSmoking,0);IniLedPBreathe(1)
#define LEDP_SMOKEOVER		    InitializeLedPMode(LedPSmokeOver,0);IniLedPBreathe(0)
#define LEDP_TIMEOVER			InitializeLedPMode(LedPTimeOver,2);IniLedPBreathe(0)		//超时闪2次
#define LEDP_LOADNC				InitializeLedPMode(LedPWarning,3);IniLedPBreathe(0)     //开路闪3次
#define LEDP_LOADSC				InitializeLedPMode(LedPWarning,5);IniLedPBreathe(0)     //负载1短路，闪5次
#define LEDP_LOADSC1			InitializeLedPMode(LedPWarning,5);IniLedPBreathe(0)     //负载2短路，闪5次
#define LEDP_CHARGE				InitializeLedPMode(LedPCharging,0);IniLedPBreathe(0)
#define LEDP_BATLOW				InitializeLedPMode(LedPBatLow,10);IniLedPBreathe(0)      //低电闪10次
#define LEDP_TURNON				InitializeLedPMode(LedPTurnOn,0);bLedPStepID=1;IniLedPBreathe(0)
#define LEDP_TURNOFF			InitializeLedPMode(LedPTurnOff,0);bLedPStepID=0;LedPStep=10;IniLedPBreathe(0)
#define LEDP_SCREENON			InitializeLedPMode(LedPScreenOn,0)
#define LEDP_OILLOW;            InitializeLedPMode(LedPOilLow,10);IniLedPBreathe(0)      //低油闪10次

/*-------------------------------------------------------------------------*/
extern	void IniLedPBreathe(uint8_t LedPF);
extern	void InitializeLedPMode(uint8_t DMode,uint8_t Counter);
extern	void SetLedPBuffer(uint16_t DData);
extern	void RenewLedPScanData(void);
extern	void LedPScan(void);
extern	void LedPComHighR(void);
extern	void LedPController(void);
extern	void HexToDec(uint16_t DData);
extern  void DisplayNumber(void);
extern  void DisplayNumber1(void);
extern  void Ledalloff1(void);
extern  void Led_Debug(void);

extern	void DisplaySmokeTime(void);
extern	void DisplayPowerLoop(uint8_t StepN);
extern	void DisplaySmokePower(uint8_t PData);
extern	void DisplayOilPower(uint8_t PData1);
// extern	void DisplaySmokeMode(void);
extern	void DisplayBatLevel(uint8_t BL);
extern	void DisplayOilLevel(uint8_t OL);
extern	void DisplayBatPercent(uint8_t BL1);
extern	void DisplayOilPercent(uint8_t OL1);
extern  void DisplaySmokeBeidou(void);

/****标志灯****/
extern void Displayflower(void);
extern void Displayflower1(void);
extern void Display_BeidouStar(void);
extern void Displaystar1on(void);
extern void Displaystar2on(void);
extern void Displaystar3on(void);
extern void Displaycityon(void);
extern void Displaystar1off(void);
extern void Displaystar2off(void);
extern void Displaystar3off(void);
extern void Displaycityoff(void);


extern	void LedPGroup4Run(uint8_t LedN);		//4 group
extern	void DisplayLeftDownCorner(void);
extern	void DisplayTurnOnOffUI(void);
/*-------------------------------------------------------------------------*/
extern ByteBit     			LedFlag,LedFlag1;
#define bDutyInc				LedFlag.Bits.Bit0
#define bLedOn					LedFlag.Bits.Bit1
#define bLedBreathe			LedFlag.Bits.Bit2
#define bLedFlash				LedFlag.Bits.Bit3

#define bLedBreathe2		LedFlag.Bits.Bit4
#define bDuty2Inc				LedFlag.Bits.Bit5
#define bLed2On					LedFlag.Bits.Bit6
#define bLedGrad				LedFlag.Bits.Bit7

#define bDuty1Inc				LedFlag1.Bits.Bit0
#define bLed1On					LedFlag1.Bits.Bit1

/*-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*/
#define	LedAllOff				0
#define	LedAllOn				1
#define	LedGradOn				2
#define	LedGradOff				3
#define	LedStandby				4
#define	LedBreatheState			5
#define	LedCharging				6
#define	LedWarning				7
#define	LedTimeOver				8
#define	LedSmoking				9
#define	LedBatLow				10
#define	LedOcWarning			11
#define	LedSmokeOver			12
#define	LedChargeStart			13
#define	LedScreenOn				14
#define	LedPowerOn				15
#define	LedGearFlash			16
#define	LedAllFlash				17
#define	LedTurnOn				18
#define	LedTurnOff				19
#define	LedLoadCon				20
#define	LedAltFlash				21
#define	LedDebug				0xff

/*-------------------------------------------------------------------------*/
#define LED_OFF						IniLedMode(LedAllOff,0)
#define LED_ON						IniLedMode(LedAllOn,0)
#define LED_STANDBY				IniLedMode(LedStandby,0)
#define LED_SMOKING				IniLedMode(LedSmoking,0)
#define LED_SMOKEOVER			IniLedMode(LedSmokeOver,0)
#define LED_TIMEOVER			IniLedMode(LedWarning,3)
#define LED_SCREENON			IniLedMode(LedScreenOn,0)
#define LED_CHARGE				IniLedMode(LedCharging,0)
#define LED_BATLOW				IniLedMode(LedAllOff,0)
#define LED_TURNON				IniLedMode(LedTurnOn,0)

/*-------------------------------------------------------------------------*/
#define	BLNDuty				100
#define	BLNPeriod			100
#define DutyInter			30		//5*30=150mS
#define	DutyUnitT			30		//30*0.1=3mS
#define	DutyUnitTS		50		//50*0.1=5mS
#define	ChgDutyUnitT	150		//150*0.1=15mS
/*-------------------------------------------------------------------------*/
extern	void IniLedMode(uchar LMode,uchar FTimes);

extern	void LedBreathe(void);
/*--------------------------------------------------------------*/
#endif
