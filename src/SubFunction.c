/******************************************************************************
 ** Function :	task.c
 ******************************************************************************/

/******************************************************************************
 ** Include files
 ******************************************************************************/
#include "Global.h"
/*--------------------------------------*/
/*--------------------------------------------------------------*/
void CheckBatPercent(void)  //����ص����ٷֱȲ�������Ҫ���� BatPowPercent����ع��ʰٷֱȣ�
{
	uint8_t TempR;
	TempR = CalBatPercent(BatVolValue);  //�����ص�������ֵ��TemR
	if(TempR<BatPowPercent)   //�����ǰʵ�ʲ�����ѹС�ڵ�ǰ�� BatPowPercent
	{
		if(PuffTime >= TimePerPuffMin) // PuffTime(����ʱ��) �Ƿ�����趨����С����ʱ��   PuffTime��ÿ�������ж��ж����ۼ�
		{
			PuffTime =0;
			if(BatPowPercent > BatPerStep)
			{
				BatPowPercent -=BatPerStep;   //����������1
				//CalBatLevel();  //
			}
		}
	}

	else
	{
		if(PuffTime >= TimePerPuffMax)  //��� TempR û��С�ڵ�ǰ�� BatPowPercent���������̳����趨���������ʱ��
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
void CheckLoadState(void)    //�ȹص�
{
	LoadIOInput;   //ADC1����Ϊ�����
	DelayNuS(10);	//�ӳ� 10 ΢�룬ȷ�������ȶ�
	if(LOAD_FALSE) {SetLoadNC;ClrLoadSC;}   //����1��·
	else
	{
		PwmLow;  //�򿪸���1���
		DelayNuS(20);
		if(LOAD_TRUE) {ClrLoadNC;SetLoadSC;}   //����1��·
		else
		{
			LoadADInput;
			DelayNuS(30);
			AdOutValue=ReadAdResult(AD_VolChannel);//�������1��·�Ͷ�·��־
			if(AdOutValue > LoadRSCAdValue) {ClrLoadNC;ClrLoadSC;} 	
			else
			{
				AdOutValue=ReadAdResult(AD_VolChannel);//
				if(AdOutValue > LoadRSCAdValue) {ClrLoadNC;ClrLoadSC;}  //�������1��·�Ͷ�·��־
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
	if(bLoad2SC)   //����2��·
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
//	bKeyEnable =0;  //�رհ�������
	ReadBatteryVoltage();
	BatPowPercent=CalBatPercent(BatVolValue);   //�����صĵ����ٷֱ�
	BatCounter = 0;
	LowBatCounter = 90;
	BatODCounter = 90;
	MainState = MainPowerOn;
}
/*--------------------------------------*/
void MainPoweronFunction(void)
{
    uint8_t TempR0,TempR1;
    if(MainState != MainPowerOn) //�����ǰ״̬���ǿ��������˳���������ִ���κβ���
		 return;
    switch(StateStep)
    {
        case 0:
        {
            if(bTime100mS)        //��ʱ���ж����ۼ�        
            {
							ClrTime100mS;
							ReadBatteryVoltage();   //��ȡ��ص�ѹ
							CheckBatteryState();	//������ѹ״̬
							CheckBatODState();		//ÿ100������һ�ε�ص�ѹ�����µ��״̬
							TempR0=CalBatPercent(BatVolValue+BalVolOffset);//TempR0 ����ֵΪ CalBatPercent(BatVolValue + BalVolOffset) �ķ���ֵ������������㵱ǰ��ص����İٷֱȣ��������˵�ѹ����
							if(TempR0>BatPowPercent) TempR1=TempR0-BatPowPercent;
							else TempR1=BatPowPercent-TempR0;
							if(TempR1<10)     //��ѹ��������Ļ������ѹ��   ��� TempR1����ѹ�С�� 10����ʾ��ص����仯��С��������Ϊ��ص����ȶ�
							{
								BatCounter++;
								if(BatCounter>=20)
								{
									//CalBatLevel();  //
									StateStep=1;   //����case1
									DelayState = 0;
								}
							}
							else //��� TempR1 ����10������Ϊ��ص��������˽ϴ�仯
							{
								BatPowPercent=TempR0;  //���� BatPowPercent Ϊ TempR0
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
						SmokeMode = 1;   //����״̬
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
						//bKeyEnable =1;   //�򿪰���ʹ��
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
	   	if( OilPercent == 0)   //��������ֹͣ�������������0������ͼ����˸ʮ��
		{
		LEDP_OILLOW;
		IniWarningMode();
		return;
		}
       /*--------------------------------------*/
       CheckLoadState();   //���裬�ȹص�
      if(MainState != MainStandby) return;
       /*--------------------------------------*/
        CheckBatPercent();
		CalOilPercent();

       /*--------------------------------------*/
        IniSmokeMode();
        return;
    }
    if(bUsbOld && DelayState>100)   //USB����
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
   if(bMicOld==0 && MIC_FALSE &&(SwStateNew == SwStateOld)  /*&& UsbState==UsbNc /* && KEY_FALSE */ && (DelayState >300))    //Ϊʲôû��˯��
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
        if(!bMicOld)  //δ����
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
//	bKeyEnable =0;  //�رհ�������
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
	//bKeyEnable =0;            //�رհ���
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
	SwInIO;//��������������ΪIO�����
	
	P3 |= 0x03;
	PORTIDX = 3;		//PORT3
	PINMOD10 = (PINMOD10 & 0x0f | PIN_H_MODE_OD_IPD_WAKEUP);//PIN_H_MODE_OD_IPD_WAKEUP);   //MIC KEYҪ��Ϊ��������
	
	PIN_USB = 1;
	PORTIDX = 0;		//PORT0
//	PINMOD76 = (PINMOD76&0xf0 | PIN_L_MODE_OD_WAKEUP);//P0.7,P0.6   //USBIN
	PINMOD32 = (PINMOD32 & 0xf0 | PIN_L_MODE_OD_WAKEUP);
	SET_REG_BITS(INTE1,PCIE,1);	//�������ű仯�ж� 
	INTFLG = 0x00;
	EA=1;
	/*-------------------------------*/
//ENTER_STOP_MODE;
//	STPSCK = 1;                      //ֹͣ����
	SET_REG_BITS(AUX2, PWRSAV, 1);     //PWRSAV��һ����һ�����͹���
	SET_REG_BITS(PCON, PD, 1);         //ֹͣλ,����� 1 ����ֹͣģʽ��
	SET_REG_BITS(AUX2, PWRSAV, 0);     //pwrsav = 0��
//	STPSCK = 0;                      //���Ӵ�
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
	SwitchIni();	  //�ص������ص����е���ʱ�򣬻ᴥ������
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
void CalOilPercent(void)   //���������ٷֱȣ�����OilPercent 
{
	uint8_t m;
	uint32_t m0,m1,m2;
	m0=(uint32_t)SmokeTimeCnt; //SmokeTimeCnt��ֵ��m0
	m1=(uint32_t)SmokeTimeCnt1;
	m1=(m1*100)/100;	
	m2=(uint32_t)SmokeTimeCnt2;
	m2=(m2*200)/100;
	m0 = m0+m1+m2;	//�� m0, m1, m2 ��ӣ��õ��ܵ�ʹ��ʱ��
	if(m0 >= OilTimeTotal) {OilPercent=0;} //��� m0 ���ڻ���� OilTimeTotal�������� OilPercent Ϊ 0����ʾ�����ľ�
	else  //���򣬼���ʣ������
	{
		m2 = OilTimeTotal-m0;  //����ʣ��ʱ�� m2������ OilTimeTotal ��ȥ m0��Ȼ����� OilTimePer
		m2 = m2/(OilTimePer);
		m = (uint8_t) (m2);
		m = m+1;  //�����ת��Ϊ uint8_t ���ͣ����� 1��ȷ�������� 1 ��ֵ��
		if(m>100) m=100;  //��������� m ���� 100����������Ϊ 100
		OilPercent = m;  //���� OilPercent ����
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
