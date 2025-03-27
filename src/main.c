/**
******************************************************************************
* @file    main.c
* @brief   MAIN Source File.
******************************************************************************
*/
#include "inc/Global.h"
/*--------------------------------------------------------------*/
/*--------------------------------------------------------------*/

uint8_t data MainState,StateStep;
uint8_t data OilPercent,OilLevel;
uint8_t data  FlagSmoke0,FlagSmoke1;
uint32_t data StoreFlag;
uint16_t data  SmokeTimeCnt;
uint16_t data  SmokeTimeCnt1;
uint16_t data  SmokeTimeCnt2;
uint16_t data  Ref1V2;


//Time_TypeDef   data TimeCnt;
uint8_t  data  dataTimeBase;     //Inc 100uS
uint8_t  data  Time10mSCnt; //Inc 100uS
uint8_t  data  Time100mSCnt; //Inc 10mS

uint8_t  data  PuffTime;      //Inc 100mS
uint16_t data  SmokeTime;     //Inc 100mS
uint16_t data  TimeDelaymS;   //Inc 10mS
uint16_t data DelayState;

ByteBit data TimeFlag;
ByteBit data SysInfoFlag;
ByteBit data LoadInfoFlag;

/*--------------------------------------------------------------*/
void main()
{	
	PwmInitialize();
	Bsp_FastClock_Init(3);//SYSCLKPSC_Div1);  
	Bsp_delay_100us(10);	
	OPTION = (0x40 | WdtClkPsc_0| AdcClkPsc_8);
	PortInitialize();
	AdcInitialize();
	Lvd_Initialize();
	Timer0_Init();
	WDG_Init();	//240MS
	MicIni();
//	KeyIni();
//	bKeyEnable =1;
	bBatOD=0; bBatLow = 0;  //?
	LowBatCounter = 0; BatODCounter = 0;
	EA=1;
	/*-------------------------------------------*/
	
	//------------------------------------
#if(DebugForT==0)
	if((FlagSmoke0 == 0xA5) && (FlagSmoke1 == 0x5A))
	{
		FlagSmoke0 = 0x00;
		FlagSmoke1 = 0x00;
		if(StoreFlag != 0x5AA5)
		{
			StoreFlag = 0x5AA5;
			SmokeTimeCnt = 0;
			SmokeTimeCnt1 = 0;
			SmokeTimeCnt2 = 0;
		}
		LEDP_LOADSC;
		IniWarningMode();
	}
	else
	{		
		IniMainPowerOn();   //->LEDP_ALLON  , MainState = MainPowerOn
	}
	#endif
	/*--------------------------------------*/
/*--------------------------------------------------------------*/
//	/*
#if(DebugForT==1)
	bBatOD=0; bBatLow = 0;
	SmokeTimeCnt = 0;
	SmokeTimeCnt1 = 0;
	SmokeTimeCnt2 = 0;
	ChargeStep=1;
	ChargeTime=0;
	bHeat=0;
	SmokeMode = 1;
	MicIni();
	//KeyIni();
//	LEDP_SCREENON;//
	LEDP_STANDBY;//LEDP_ALLON;//LEDP_DEBUG;//LEDP_CHARGE;//LEDP_BATLOW;//LEDP_LOADNC;//LEDP_SMOKING;//LEDP_TURNON;//LEDP_TURNOFF;//LEDP_SMOKEOVER;//LEDP_SMOKING;//
	DelayState=0;	
	ReadBatteryVoltage();
	CalBatPercent(BatVolValue);
	CalBatLevel();
	CalOilPercent();
	CalOilLevel();
	SmokeTime = 0;
	MainState = MainDebug;
//	IniSmokeMode();
			OutputOn;
		  Output2On;
	
  while(1)
	{
		CLR_WDT;

		LedPController();
		
		if (bTime10mS == 1)
		{
			bTime10mS =0 ;
			
//			KeyScan();
//			MicScan();
//			CheckUsbState();
		}
		if(TimeDelaymS >= 100)
		{
		
			TimeDelaymS =0;		
	 AdOutValue=ReadAdResult(AD_VolChannel);
	 AdOut2Value=ReadAdResult(AD_Vol2Channel);
			CLR_WDT;
		}
	}
	#endif
//	*/
/*--------------------------------------------------------------*/
	/*-------------------------------------------------------------------------------------------*/
	#if(DebugForT==0)
  while(1)
	{
		CLR_WDT;
		LedPController();
		if (bTime10mS == 1)
		{
			bTime10mS =0;
			if(MainState!=MainPowerOn)
			{
				MicScan();
			//	KeyScan();
				#if(SwitchTorF == 1)
				SwitchScan();
				#endif
				CheckUsbState();
			}
			if(MainState!=MainSmoke &&  MainState!=MainPowerOn && MainState!=MainTurnOff)   //
			{
				ReadBatteryVoltage();
				CheckBatteryState();
				CheckBatODState();
			}
		}
		/*-----------------------------------------------*/
		switch(MainState)
		{
			/*-----------------------------------------------------------------------*/
		  case MainPowerOn:   //ио╣Г
		  {
		      MainPoweronFunction();
		      break;
		  }
		  case MainStandby:
		  {
		      MainStandbyFunction();
    		  break;
		  }
			#if(PreHeatForT == 1)
		  case MainPreHeat:
		  {
		      MainPreHeatFunction();
		      break;
		  }
			#endif
		  case MainSmoke:
		  {
			
		      MainSmokeMode();
    		  break;
		  }
		  case MainWarning:
		  {
		      MainWarningFunction(); 
    		  break;
		  }
		  case MainCharge:
		  {
		      BatChargeFunction();
		      if(bUsbOld==0)
		      {
		          IniMainStandby();
		      }
    		  break;
		  }
		  case MainOffCharge:
		  {
		      BatChargeFunction();		  
		      if(bUsbOld==0)
		      {
					IniMainTurnOff();
					LEDP_ALLOFF;
		      }
    		  break;
		  }
		  case MainSleep:
		  {
				EnterSleep();
				DelayState = 0;
//			  if(KEY_FALSE) bKeyEnable =1;
			  if(MIC_TRUE) {MainState = MainStandby;}
			  //else if(KEY_TRUE) {IniMainStandby();}//LEDP_SCREENON; MainState = MainScreenOn;}
			  else
			  {
					IniMainStandby();
			  }
   		    break;
		  }
			/*--------------------------------------------------------------*/
		  case MainTurnOn:
		  {
			  if(LedPMode == LedPStandby)
			  {
				  IniMainStandby();				  
			  }
			break;
		  }
			/*--------------------------------------------------------------*/
		  case MainTurnOff:
		  {
			  if(LedPMode!=LedPSolidOff) break;
		      if(DelayState>300)
		      {
		          EnterSleep();	
              DelayState = 0;	      
		      }
					if(bUsbOld)
					{
						IniChargeMode();
						MainState = MainOffCharge;
					}
    		  break;
		  }
			/*--------------------------------------------------------------*/
			case MainScreenOn:
			{
			  if(LedPMode == LedPStandby)
			  {
				  IniMainStandby();				  
			  }
    		  break;
		  }
			/*-----------------------------------------------------------------------*/
			default:
			{ break; }
		}
	}
	#endif
	/*--------------------------------------------------------------*/
}


