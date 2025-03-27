/*----------------------------------------------------------------------------*/
/******************************************************************************
 ** Include files
 ******************************************************************************/
#include "Global.h"
/*--------------------------------------------------------------*/
uint8_t SmokeMode,ChanNum;
uint16_t RefVolValue;

uint16_t AdBatValueSum;
uint8_t	AdBatCnt;

uint8_t	PwmPeriodCnt,PwmDuty;
uint16_t AdOutValue,AdOutValueSum;
uint8_t	AdOutCnt;

uint8_t	Pwm2PeriodCnt,Pwm2Duty;
uint16_t AdOut2Value,AdOut2ValueSum;
uint8_t	AdOut2Cnt;

ByteBit   SmokeFlag;
ByteBit   SmokeFlag1;
/*-------------------------------------------------*/
const uint16_t code  RefVolTab[3]={ 3300,3500,3400};
const uint16_t code  RefVolFallTab[3]={3150,3350,3250};
const uint8_t  code  RefPowerTab[3]={14,16,20};
#define RefVolPreheat       1000
/*-------------------------------------------------*/
void ReadRefOutValue(void)
{
//	if(BatVolValue<4000)
//	{
//		RefVolValue=RefVolTab[ChanNum];
//		bPowerFall =0;
//	}
//	else
//	{
//		RefVolValue=RefVolFallTab[SmokeMode];
//		bPowerFall = 1;
//	}
	if(ChanNum==1)
	{
		RefVolValue=3300;
	}
		if(ChanNum==2)
	{
		RefVolValue=3200;
	}
}

uint8_t CalOutPwmDuty(uint16_t VSource,uint16_t VRef)
{
	uint8_t TempR8;
	uint32_t m0,m1;
	m0 = (uint32_t)VRef;
	m1 = (uint32_t)VSource;
#if(WorkCwCv==0)
	m0 = m0 * m0;			
	m1 = m1 * m1;
#endif
	m0 = m0 * PwmDutyMax;
	m0 = m0/m1;
	TempR8=(uint8_t)m0;
	if(TempR8>PwmDutyMax) TempR8=PwmDutyMax;
	else if(TempR8<PwmDutyMin) TempR8=PwmDutyMin;
//	else TempR8=(uint8_t)m0;			
	return TempR8;	
}
/*-------------------------------------------------*/
void StopOutput(void)
{
	OutputOff;
	Output2Off;
	bSmokeOut=0;   //关闭左负载输出	
	bSmokeOut2=0;  //关闭右负载输出
	FlagSmoke0 = 0x00;
	FlagSmoke1 = 0x00;
	ClrHeat;
	CHRG_ENABLE;
}
/*-------------------------------------------------*/

/*****************************************************************************************/
	/*	选择输出通道，chanNum值为0,1,2，分别控制左单发，右单发，双发输出    */
	/*      油量低于5%，切换为单发输出，smokemode为2，为双发输出           */
/****************************************************************************************/
void SwitchChannelHeat(void)    
{
	#if(SwitchTorF == 1)
    if(ChanNum==1) {bSmokeOut=1;bSmokeOut2=0;}
//    else if(ChanNum==1) {bSmokeOut=0;bSmokeOut2=1;}
    else if (ChanNum==2){bSmokeOut=1;bSmokeOut2=1;}
	#else
		if(OilPercent<=5) 
		{
			ChanNum=1;bSmokeOut=0;bSmokeOut2=1; 		//负载1输出
		 }      	
		else
		{
			if(SmokeMode==2)	
			{
			bSmokeOut=1;bSmokeOut2=1;
			}    //双发
			else
			{
				if(ChanNum==0) {ChanNum=1;bSmokeOut=1;bSmokeOut2=0;}    		//负载1输出
				else if(ChanNum==1) {ChanNum=0;bSmokeOut=0;bSmokeOut2=1;}	  //负载2输出
			}
		}
	#endif
}
/*-------------------------------------------------*/
void IniHeatStart(void)   //吸烟
{
	CHRG_DISABLE;
	LowBatCounter=0;
	AdBatValueSum=0;
	AdBatCnt=0;
	bShortC =0;bShortC2 =0;
	PwmDuty=CalOutPwmDuty(BatVolValue,RefVolValue);
	PwmPeriodCnt=0;   //预热计时
	bOutCheck = 0;
	AdOutValueSum = 0;AdOutCnt = 0;
	#if(TwoLoadForT == 1)
	Pwm2Duty=PwmDuty;
	Pwm2PeriodCnt=20;
	bOut2Check = 0;
	AdOut2ValueSum = 0;AdOut2Cnt = 0;
	#endif
	bBatCheck = 0;
	bWorkStart = 1;
	DelayState=0;
	SmokeTime = 0;

	LEDP_SMOKING;
	SwitchChannelHeat();
	FlagSmoke0 = 0xA5;
	FlagSmoke1 = 0x5A;
	SetHeat;
}
/*-------------------------------------------------*/
void IniSmokeMode(void)
{
	ReadRefOutValue();
	IniHeatStart();
	StateStep = 0;

	MainState=MainSmoke;
}
/*-------------------------------------------------*/
void MainSmokeMode(void)
{
	if(MainState!=MainSmoke) return;
	if(SmokeTime >= SmokeTimeMax)  //10s
	{
		StopOutput();
		LEDP_TIMEOVER;
		IniWarningMode();
		return;
	}
	/*------------------------------------*/
	if(!bMicOld)   
	{		
		StopOutput();			
		// LEDP_SMOKEOVER;
		LEDP_STANDBY;
		DelayState =0;   //每次吸烟之后清零
		MainState=MainStandby;
		return;
	}
//	#if(SwitchTorF == 1)
//	SwitchChannelHeat();
//	#endif
	ShortCheck();if(MainState!=MainSmoke) {return;} 
//	if(bWorkStart==1)
//	{
//		if(SmokeMode==2)   //双发模式
//		{
//			if(SmokeTime >= 30)
//			{
//				bWorkStart =0;
//				if(OilPercent<=5) {ChanNum=1;bSmokeOut=0;bSmokeOut2=1;}
//				else
//				{
//					if(ChanNum==0) {ChanNum=1;bSmokeOut=1;bSmokeOut2=0;}
//					else if(ChanNum==1) {ChanNum=0;bSmokeOut=0;bSmokeOut2=1;}
//				}
//				if(bPowerFall==1)
//				{
//					RefVolValue=3350;
//				}
//				else RefVolValue=3500;
//			}
//		}
//		else bWorkStart=0;
//	}
	/*------------------------------------*/
	if(bSmokeOut==1)    //左单发
	{
		if(PwmPeriodCnt<PwmDuty) {PwmLow;}
		else {PwmHigh;}
	}
	else {PwmHigh;}
	#if(TwoLoadForT == 1)
	if(bSmokeOut2==1)   //右单发
	{
		if(Pwm2PeriodCnt<Pwm2Duty) {Pwm2Low;}
		else {Pwm2High;}
	}
	else {Pwm2High;}
	#endif
	/*------------------------------------*/
	ShortCheck();if(MainState!=MainSmoke) {return;} 
	CheckHeatOutput();
	CheckSmokeBatState();
   	/*------------------------------------*/
}
/*--------------------------------------------------------------*/
#if(PreHeatForT == 1)
void MainPreHeatFunction(void)
{
    if(MainState != MainPreHeat) return;
    switch(StateStep)
    {
        case 0:
        {
            if(bBatLow==1 || BatPowPercent==0)
            {
                LEDP_BATLOW;
                IniWarningMode();
                return;
            }
            /*--------------------------------------*/
            //CheckLoadState();
            if(MainState != MainPreHeat) return;
            /*--------------------------------------*/
            CheckBatPercent();
            /*--------------------------------------*/
            RefVolValue=RefVolPreheat;
            IniHeatStart();
	        StateStep = 1;
            break;
        }
        /*----------------------------------*/
        case 1:
        {
	       if(SmokeTime >= PreheatTime)
	       {
		      StopOutput();
		      LEDP_STANDBY;
		      MainState=MainStandby;
		      return;
	       }
					/*------------------------------------*/
	       if(bMicOld)
	       {		
		      IniSmokeMode();
		      return;
	       }
				#if(SwitchTorF == 1)
				SwitchChannelHeat();
				#endif
				 ShortCheck();if(MainState!=MainSmoke) {return;} 
	       /*------------------------------------*/
	       if(bSmokeOut==1)
	       {
		      if(PwmPeriodCnt<PwmDuty) {PwmLow;}
		      else {PwmHigh;}
	       }
	       else {PwmHigh;}
	       #if(TwoLoadForT == 1)
	       if(bSmokeOut2==1)
	       {
		      if(Pwm2PeriodCnt<Pwm2Duty) {Pwm2Low;}
		      else {Pwm2High;}
	       }
	       else {Pwm2High;}
    	   #endif
	       /*------------------------------------*/
				 ShortCheck();if(MainState!=MainSmoke) {return;} 
	       CheckHeatOutput();
	       CheckSmokeBatState();
	       /*------------------------------------*/
            break;
        }
    }
}
#endif
/*--------------------------------------------------------------*/
void CheckHeatOutput(void)
{
	CheckLoadVoltage();
	if(MainState!=MainSmoke) return;
	AdjustLoadVoltage();
	
	CheckLoad2Voltage();
	if(MainState!=MainSmoke) return;
	AdjustLoad2Voltage();
}
void CheckSmokeBatState(void)
{
	uint32_t m,n;
	if(!bBatCheck) return;
	bBatCheck =0;
	AdBatValueSum += ReadAdResult(AD_1V2);//
	AdBatCnt++;
	if(AdBatCnt<5) return;
	m =(uint32_t) (AdBatValueSum/5);
	n = 4915200 /m; // 1.20*1000*4096/AD值
	RefVddValue = (uint16_t) n;
	BatVolValue = RefVddValue + BalVolOffset;
    AdBatValueSum=0;
	AdBatCnt=0;
    if(BatVolValue < LowBatVoltage1)
    {
        if(++LowBatCounter > 30)	//300MS
        {
            StopOutput();
            LEDP_BATLOW;
            IniWarningMode();
            return;
        }
    }
    else LowBatCounter=0;
}
/*--------------------------------------------------------------*/
void CheckLoadVoltage(void)
{
	if(bSmokeOut==0) return;
	if(bMosOn==1)
	{
		LoadADInput;
		AdOutValue=ReadAdResult(AD_VolChannel);
		if(AdOutValue<LoadRSCAdValue)
		{
			AdOutValue=ReadAdResult(AD_VolChannel);
			if(AdOutValue<LoadRSCAdValue)
			{
				StopOutput();
				LEDP_LOADSC;
				IniWarningMode();
				return;
			}
		}
	}
}
void AdjustLoadVoltage(void)
{
	uint16_t TempR;
	uint32_t TempR32;
	if(bSmokeOut==0) return;
	if(bOutCheck == 0) return;
	bOutCheck = 0;
	AdOutValueSum += AdOutValue;
	AdOutCnt++;
	if(AdOutCnt<5) return;
	TempR = (AdOutValueSum/5);
	AdOutValueSum=0;
	AdOutCnt = 0;
	TempR32 =(uint32_t) TempR;
	TempR32 = TempR32*RefVddValue;
	TempR32 = TempR32/4096;
	TempR = (uint16_t)(TempR32);
	PwmDuty=CalOutPwmDuty(TempR,RefVolValue);	
}
/*--------------------------------------------------------------*/
#if(TwoLoadForT == 1)
void CheckLoad2Voltage(void)
{
	if(bSmokeOut2==0) return;
    if(bMos2On == 1)
	{
		Load2ADInput;
		AdOut2Value=ReadAdResult(AD_Vol2Channel);
		if(AdOut2Value<LoadRSCAdValue)
		{
			AdOut2Value=ReadAdResult(AD_Vol2Channel);
			if(AdOut2Value<LoadRSCAdValue)
			{
				StopOutput();
				LEDP_LOADSC;
				IniWarningMode();
				return;
			}
		}
	}
}
void AdjustLoad2Voltage(void)
{
	uint16_t TempR;
	uint32_t TempR32;
	if(bSmokeOut2==0) return;
	if(bOut2Check == 0) return;
	bOut2Check = 0;
	AdOut2ValueSum += AdOut2Value;
	AdOut2Cnt++;
	if(AdOut2Cnt<5) return;
	TempR = (AdOut2ValueSum/5);
	AdOut2ValueSum=0;
	AdOut2Cnt = 0;
	TempR32 =(uint32_t) TempR;
	TempR32 = TempR32*RefVddValue;
	TempR32 = TempR32/4096;
	TempR = (uint16_t)(TempR32);
	Pwm2Duty=CalOutPwmDuty(TempR,RefVolValue);	
}
#endif
/*--------------------------------------------------------------*/
/*---------------------------------------------------*/
void ShortCheck(void)
{
	if(bLoadSC==1 || bLoad2SC==1)   //负载1和负载2短路
	{
		bLoadSC =0;
		bLoad2SC =0;
		StopOutput();
		LEDP_LOADSC;
		IniWarningMode();
	}
}

/*---------------------------------------------------*/
/*-----------------------------------------------------------*/
/*--------------------------------------------------------------*/
/*--------------------------------------------------------------*/

/*--------------------------------------------------------------*/
/*--------------------------------------------------------------*/
/*--------------------------------------------------------------*/

/*--------------------------------------------------------------*/















