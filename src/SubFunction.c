/******************************************************************************
 ** Function :	task.c
 ******************************************************************************/

/******************************************************************************
 ** Include files
 ******************************************************************************/
#include "Global.h"
/*--------------------------------------*/
/*--------------------------------------------------------------*/
void CheckBatPercent(void)  //检查电池电量百分比并根据需要调整 BatPowPercent（电池功率百分比）
{
	uint8_t TempR;
	TempR = CalBatPercent(BatVolValue);  //计算电池电量，赋值给TemR
	if(TempR<BatPowPercent)   //如果当前实际测量电压小于当前的 BatPowPercent
	{
		if(PuffTime >= TimePerPuffMin) // PuffTime(吸烟时间) 是否大于设定的最小吸烟时间   PuffTime：每次吸烟中断中都会累加
		{
			PuffTime =0;
			if(BatPowPercent > BatPerStep)
			{
				BatPowPercent -=BatPerStep;   //电量格数减1
				//CalBatLevel();  //
			}
		}
	}

	else
	{
		if(PuffTime >= TimePerPuffMax)  //如果 TempR 没有小于当前的 BatPowPercent，并且吸烟超过设定的最大吸烟时间
		{
			PuffTime =0;
			if(BatPowPercent > BatPerStep)
			{
				BatPowPercent -=BatPerStep;
				//CalBatLevel();  //
			}
		}
	}
}
/*--------------------------------------------------------------*/
void CheckLoadState(void)    //先关掉
{
	LoadIOInput;   //ADC1设置为输出口
	DelayNuS(10);	//延迟 10 微秒，确保输入稳定
	if(LOAD_FALSE) {SetLoadNC;ClrLoadSC;}   //负载1开路
	else
	{
		PwmLow;  //打开负载1输出
		DelayNuS(20);
		if(LOAD_TRUE) {ClrLoadNC;SetLoadSC;}   //负载1短路
		else
		{
			LoadADInput;
			DelayNuS(30);
			AdOutValue=ReadAdResult(AD_VolChannel);//清除负载1开路和短路标志
			if(AdOutValue > LoadRSCAdValue) {ClrLoadNC;ClrLoadSC;} 	
			else
			{
				AdOutValue=ReadAdResult(AD_VolChannel);//
				if(AdOutValue > LoadRSCAdValue) {ClrLoadNC;ClrLoadSC;}  //清除负载1开路和短路标志
				else {ClrLoadNC;SetLoadSC;}
			}
		}
		PwmHigh;
	}
	if(bLoadSC)
	{
		IniWarningMode();
		LEDP_LOADSC;
		return;
	}
	#if(TwoLoadForT==1)
	Load2IOInput;
	DelayNuS(10);
	if(LOAD2_FALSE) {SetLoad2NC;ClrLoad2SC;}
	else
	{
		Pwm2Low;
		DelayNuS(20);
		if(LOAD2_TRUE) {ClrLoad2NC;SetLoad2SC;}
		else
		{
			Load2ADInput;
			DelayNuS(30);
			AdOut2Value=ReadAdResult(AD_Vol2Channel);
			if(AdOut2Value > LoadRSCAdValue) {ClrLoad2NC;ClrLoad2SC;}
			else
			{
				AdOut2Value=ReadAdResult(AD_Vol2Channel);//
				if(AdOut2Value > LoadRSCAdValue) {ClrLoad2NC;ClrLoad2SC;}
				else {ClrLoad2NC;SetLoad2SC;}
			}
		}
		Pwm2High;
	}
	if(bLoad2SC)   //负载2短路
	{
		IniWarningMode();
		LEDP_LOADSC;
		return;
	}
	#endif
	#if(SwitchTorF== 1)
	if(ChanNum==1)
	{
	   if(bLoadNC==1)
	   {
	       LEDP_LOADNC;
	       IniWarningMode();
	   }
	}
	else if(ChanNum==1)
	{
	   if(bLoad2NC==1)
	   {
	       LEDP_LOADNC;
	       IniWarningMode();
	   }
	}
	else
	{
	   if(bLoadNC==1 || bLoad2NC==1)
	   {
	       LEDP_LOADNC;
	       IniWarningMode();
	   }	
	}
	#endif
   if(bLoad2NC==1 || bLoad2NC==1)
   {
	   LEDP_LOADNC;
	   IniWarningMode();
   }	
}
/*--------------------------------------------------------------*/
void IniMainPowerOn(void)
{
	bBatOD=0; bBatLow = 0;
	DelayState = 0;
	StateStep = 0;
	LEDP_ALLON;//LEDP_POWERON;
//	bKeyEnable =0;  //关闭按键功能
	ReadBatteryVoltage();
	BatPowPercent=CalBatPercent(BatVolValue);   //计算电池的电量百分比
	BatCounter = 0;
	LowBatCounter = 90;
	BatODCounter = 90;
	MainState = MainPowerOn;
}
/*--------------------------------------*/
void MainPoweronFunction(void)
{
    uint8_t TempR0,TempR1;
    if(MainState != MainPowerOn) //如果当前状态不是开机，则退出函数，不执行任何操作
		 return;
    switch(StateStep)
    {
        case 0:
        {
            if(bTime100mS)        //定时器中断中累加        
            {
							ClrTime100mS;
							ReadBatteryVoltage();   //读取电池电压
							CheckBatteryState();	//检查过电压状态
							CheckBatODState();		//每100毫秒检查一次电池电压并更新电池状态
							TempR0=CalBatPercent(BatVolValue+BalVolOffset);//TempR0 被赋值为 CalBatPercent(BatVolValue + BalVolOffset) 的返回值，这个函数计算当前电池电量的百分比，并考虑了电压补偿
							if(TempR0>BatPowPercent) TempR1=TempR0-BatPowPercent;
							else TempR1=BatPowPercent-TempR0;
							if(TempR1<10)     //电压补偿，屏幕亮屏有压差   如果 TempR1（电压差）小于 10（表示电池电量变化较小），则认为电池电量稳定
							{
								BatCounter++;
								if(BatCounter>=20)
								{
									//CalBatLevel();  //
									StateStep=1;   //跳进case1
									DelayState = 0;
								}
							}
							else //如果 TempR1 大于10，则认为电池电量发生了较大变化
							{
								BatPowPercent=TempR0;  //更新 BatPowPercent 为 TempR0
								BatCounter=0;
							}
			}            
            break;
        }
        /*-----------------------*/
        case 1:
        {
						bSysOn = 1;
						ClrHeat;
						PuffTime = 0;
						StoreFlag = 0x5AA5;
						SmokeTimeCnt = 0;
						SmokeTimeCnt1 = 0;
						SmokeTimeCnt2 = 0;
						SmokeMode = 1;   //抽烟状态
						// ChanNum =0;
						FlagSmoke0 = 0x00;
						FlagSmoke1 = 0x00;
						bSmokeOut=0;
						bSmokeOut2=0;
						if(BatPowPercent==0) {bBatLow = 1;bBatStateOld=0;bBatStateNew=0;}
						else { bBatLow = 0;bBatStateOld=1;bBatStateNew=1;}
						LowBatCounter=0;
						MicIni();
						//KeyIni();
						//bKeyEnable =1;   //打开按键使能
						#if(SwitchTorF==1)
						SwitchIni();
						#endif
						CalOilPercent();
						//CalOilLevel();					
						IniMainStandby();
						DelayState = 0;   //
            break;
        }
        /*-----------------------*/
        case 2:
        {
            break;
        }    
        /*-----------------------*/
        default:{break;}
    }
}
/*--------------------------------------*/
void IniMainStandby(void)
{
    DelayState = 0;
    LEDP_STANDBY;
    MainState = MainStandby;
}
/*--------------------------------------*/
void MainStandbyFunction(void)
{
    if(MainState != MainStandby) return;
    if(bMicOld) 
    {
       if(bBatLow==1 || BatPowPercent == 0 || bBatOD==1)
       {
           LEDP_BATLOW;
           IniWarningMode();
           return;
       }
	   	if( OilPercent == 0)   //低油量，停止输出，油量数字0和油量图标闪烁十次
		{
		LEDP_OILLOW;
		IniWarningMode();
		return;
		}
       /*--------------------------------------*/
       CheckLoadState();   //检阻，先关掉
      if(MainState != MainStandby) return;
       /*--------------------------------------*/
        CheckBatPercent();
		CalOilPercent();

       /*--------------------------------------*/
        IniSmokeMode();
        return;
    }
    if(bUsbOld && DelayState>100)   //USB接入
    {
        IniChargeMode();
        return;
    }
    if(LedPMode!=LedPSolidOff)
    {
		if(LedPMode==LedPSmokeOver && DelayState>200) {LEDP_STANDBY;}
        if(DelayState>300) { LEDP_ALLOFF;DelayState=0; }   //DelayState:300*10ms
      	return;
    }
   if(bMicOld==0 && MIC_FALSE &&(SwStateNew == SwStateOld)  /*&& UsbState==UsbNc /* && KEY_FALSE */ && (DelayState >300))    //为什么没进睡眠
    {
       IniMainSleep();    
    }
}
/*--------------------------------------*/
/*-------------------------------------------------*/
void IniWarningMode(void)
{
	StopOutput();
	DelayState=0;
	MainState=MainWarning;
} 

 
/*-------------------------------------------------*/
void MainWarningFunction(void)
{
    if((LedPMode==LedPSolidOff) || (LedPMode==LedPStandby))
    {
        if(!bMicOld)  //未吸烟
        {
            DelayState = 0;
            MainState = MainStandby;
        }    
    }
}
/*--------------------------------------*/
void IniMainSleep(void)
{
    DelayState = 0;
    LEDP_ALLOFF;
//	bKeyEnable =0;  //关闭按键功能
    MainState = MainSleep;
}
/*--------------------------------------*/




/*******************************************************************************
 * \brief   void  EnterSleep(void)
 ******************************************************************************/
void EnterSleep(void)
{
    //return;
	EA = 0;
	//bKeyEnable =0;            //关闭按键
	TR0 = 0;                    // TIMER0 STOP
	ET0 = 0;                    // Interrupt disable
	PwmInitialize();
	PortInitialize();
	LED_GP1_OFF;
	LED_GP2_OFF;
	LED_GP3_OFF;
	LED_GP4_OFF;
	LED_COM1_LOW;
	LED_COM2_LOW;
	LED_COM3_LOW;
	LED_COM4_LOW;
	LED_COM5_LOW;
	LED_COM6_LOW;
	LED_COM7_LOW;
	PDOWN_LVD_DISABLE;
	LVRPD = 0;
	VBGEN_DISABLE;
	SwInIO;//将波动开关设置为IO输入脚
	
	P3 |= 0x03;
	PORTIDX = 3;		//PORT3
	PINMOD10 = (PINMOD10 & 0x0f | PIN_H_MODE_OD_IPD_WAKEUP);//PIN_H_MODE_OD_IPD_WAKEUP);   //MIC KEY要改为波动开关
	
	PIN_USB = 1;
	PORTIDX = 0;		//PORT0
//	PINMOD76 = (PINMOD76&0xf0 | PIN_L_MODE_OD_WAKEUP);//P0.7,P0.6   //USBIN
	PINMOD32 = (PINMOD32 & 0xf0 | PIN_L_MODE_OD_WAKEUP);
	SET_REG_BITS(INTE1,PCIE,1);	//开启引脚变化中断 
	INTFLG = 0x00;
	EA=1;
	/*-------------------------------*/
//ENTER_STOP_MODE;
//	STPSCK = 1;                      //停止慢钟
	SET_REG_BITS(AUX2, PWRSAV, 1);     //PWRSAV置一，进一步降低功耗
	SET_REG_BITS(PCON, PD, 1);         //停止位,如果置 1 进入停止模式。
	SET_REG_BITS(AUX2, PWRSAV, 0);     //pwrsav = 0；
//	STPSCK = 0;                      //慢钟打开
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	SET_REG_BITS(INTE1,PCIE,0);	//Disable IO level change interrupt.
	INTFLG = 0x00;
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
	//KeyIni();
	SwitchIni();	  //关掉，不关掉置中档的时候，会触发开机
	EA=1;
}

/*---------------------------------------------*/
void IniMainKeyScreenOn(void)
{
  DelayState = 0;
	StateStep = 0;
	LED_SCREENON;
  LEDP_SCREENON;
  MainState = MainKeyScreenOn;	
}
void MainKeyScreenOn(void)
{
	if(MainState != MainKeyScreenOn) return;
	
}

void IniMainTurnOn(void)
{   
	if(MainState != MainTurnOn) return;
    LEDP_STANDBY;
    DelayState = 0;
    MainState = MainStandby;
}
/*------------------------------------------*/
void IniMainTurnOff(void)
{
    LEDP_ALLOFF;
    DelayState = 0;
    MainState = MainTurnOff;
}

/*--------------------------------------------------------------*/
#if(OilPercentForT == 1)
void CalOilPercent(void)   //计算油量百分比，更新OilPercent 
{
	uint8_t m;
	uint32_t m0,m1,m2;
	m0=(uint32_t)SmokeTimeCnt; //SmokeTimeCnt赋值给m0
	m1=(uint32_t)SmokeTimeCnt1;
	m1=(m1*100)/100;	
	m2=(uint32_t)SmokeTimeCnt2;
	m2=(m2*200)/100;
	m0 = m0+m1+m2;	//将 m0, m1, m2 相加，得到总的使用时间
	if(m0 >= OilTimeTotal) {OilPercent=0;} //如果 m0 大于或等于 OilTimeTotal，则设置 OilPercent 为 0，表示油量耗尽
	else  //否则，计算剩余油量
	{
		m2 = OilTimeTotal-m0;  //计算剩余时间 m2，等于 OilTimeTotal 减去 m0，然后除以 OilTimePer
		m2 = m2/(OilTimePer);
		m = (uint8_t) (m2);
		m = m+1;  //将结果转换为 uint8_t 类型，并加 1，确保至少有 1 的值。
		if(m>100) m=100;  //如果计算结果 m 大于 100，则将其限制为 100
		OilPercent = m;  //更新 OilPercent 变量
	}
}
#if(OilLevelForT == 1)
void CalOilLevel(void)
{
	if(OilPercent == 0) OilLevel=0;
	else if(OilPercent <= 10) OilLevel=1;
	else if(OilPercent <= 35) OilLevel=2;
	else if(OilPercent <= 65) OilLevel=3;
	else OilLevel=4;
}
#endif
#endif
/*--------------------------------------------------------------*/
