#include "inc/Global.h"
/*--------------------------------------------------------------*/
void PwmInitialize(void)
{
//	PWM_HIGH;
//	PWM2_HIGH;
	P2 |= 0x0C;	//0000 1100	P2第2位和第3位设置为1,其他位不变
	PORTIDX = 2;
	PINMOD32 = 0x66;//(PINMOD32 & 0x0f) | 0x60; 	//P2.2,3 is P.P. output.
					//等效为：PINMOD32 =  PINMOD32 & 0x00 | PIN_H_Mode_PP | PIN_L_Mode_PP;
//	PINMOD54 = (PINMOD32 & 0xf0) | 0x06;  //P2.4 is P.P. output.
}
/*--------------------------------------------------------------*/
void PortInitialize(void)
{
	//LedPComHighR();

	//LED1~4
	//LED :0 ,ADC:默认，可设为1，MIC：0，KEY：1，PWM（PMOS）：1（关),CC1,CC2:默认，可设为1
	P0 = 0X7b; 			//01111011
	PORTIDX = 0;		//PORT1
	PINMOD76 = (PINMOD76 & 0x00) | PIN_H_MODE_OD | PIN_L_MODE_PP;   //	     PWM2
	PINMOD54 = (PINMOD54 & 0x00) | PIN_H_MODE_PP | PIN_L_MODE_PP;   //N1	  N2
	PINMOD32 = (PINMOD32 & 0x00) | PIN_H_MODE_PP | PIN_L_MODE_PP;	//N3 	  CON1
	PINMOD10 = (PINMOD10 & 0x00) | PIN_H_MODE_OD | PIN_L_MODE_OD;   //CCL1  CCL2  (需加带电升级)  要不要加唤醒？？
	PINMOD |= (HSNK0EN | HSNK1EN);

	// P0 &= ~0x30;					 //谢工配置
	// P0 |= 0xc0;
	// PORTIDX = 0;		//PORT0                            
	// PINMOD54 = 0x66;	//P0.4,5 is P.P. output.
	// PINMOD76 = (PIN_H_MODE_OD | PIN_L_MODE_OD_WAKEUP);//P0.7,P0.6
	
	P1 = 0x00;
	PORTIDX = 1;		//PORT1
	PINMOD76 = (PINMOD76 & 0x00) |PIN_H_MODE_OD | PIN_L_MODE_OD;	//L7
	PINMOD54 = (PINMOD54 & 0x00) |PIN_H_MODE_OD | PIN_L_MODE_OD;
	PINMOD32 = (PINMOD32 & 0x00) |PIN_H_MODE_OD | PIN_L_MODE_OD;
	PINMOD10 = (PINMOD10 & 0x00) |PIN_H_MODE_OD | PIN_L_MODE_OD;    //		L6
	
	P2 = 0x0C;			//00001100
	PORTIDX = 2;		//PORT2
	PINMOD76 = (PINMOD76 & 0x00) |PIN_H_MODE_OD | PIN_L_MODE_OD;
	PINMOD54 = (PINMOD54 & 0x00) |PIN_H_MODE_ADC| PIN_L_MODE_ADC;   //ADC2   ADC1
	PINMOD32 = (PINMOD32 & 0x00) |PIN_H_MODE_PP | PIN_L_MODE_OD_WAKEUP;  //PWM PMOS	DC5VIN(要求高电平唤醒)   
	PINMOD10 = (PINMOD10 & 0x00) |PIN_H_MODE_OD | PIN_L_MODE_OD;    //L2	L1

	P3 = 0x03;             //00000011
	PORTIDX = 3;		//PORT3
	PINMOD76 = (PINMOD76 & 0x00) | PIN_H_MODE_OD | PIN_L_MODE_OD;   //L3		L4
	PINMOD54 = (PINMOD54 & 0x00) | PIN_H_MODE_OD | PIN_L_MODE_OD;   //L5
	PINMOD32 = (PINMOD32 & 0x00) | PIN_H_MODE_PP | PIN_L_MODE_OD;   //En_CHGR(充电使能)
	PINMOD10 = (PINMOD10 & 0x00) | (PIN_H_MODE_OD_IPD_WAKEUP | PIN_L_MODE_OD);    //MIC（要求高电平唤醒）参照规格书，必须拉高	KEY（要求低电平唤醒)
	
	VBGEN_ENABLE;
	CHRG_ENABLE;
	PDOWN_LVD_ENABLE;
	LVRPD = 1;
	
}
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*--------------------------------------------------------------*/
void Timer0_Init(void)
{
	TMOD = (TMOD &(~0x0F)) | 0x01;
	TH0 = TIME_RELOAD/256;
	TL0 = TIME_RELOAD%256;
	
//		TH0 =(65536 - 9216 )/256;   // 1000US
//		TL0 =(65536 - 9216 )%256;
	
	  TF0 = 0;
		TR0 = 1;                    // TIMER0 运行
		ET0 = 1;                    // Interrupt enable   //Timer0 中断使能
}
/*----------------------------------------------------------
  enState->Bit[7:6]:WDT_EN -> WDT Enable Control
           0xC0:11->WDT Always Enable
           0x80:10->WDT Enable in Fast/Slow, Disable in Idle/Stop mode
           0x00:0x->WDT Disable  
  ----------------------------------------------------------*/
void WDG_Init(void)
{
//	OPTION = (OPTION & ~OPTION_WDTPSC_MASK) | ClkPsc;	     //240MS
//	AUX2   = (AUX2   & ~AUX2_WDTE_MASK) | 0xc0;			  // 看门狗定时器复位于快钟/慢钟模式下使能,空闲/停止模式时禁止
	WDT_RUN_FAST_DIS_ILDE;//
	CLRWDT = 1;
}
/*--------------------------------------------------------------*/
void Lvd_Initialize(void)  
{
	INTFLG &= ~LVDIF;	//CLEAR LVDIF
	LVDS = 0x04;	//Enable LVD and lvd_voltage 2.61v
	INTE1 |= LVDIE; 
}
void Lvd_Interrupt(void) interrupt 9   //欠压中断
{
	INTFLG &= ~LVDIF;	//CLEAR LVDIF
	if(MainState==MainSmoke)    
	{
		StopOutput();
		SetLoadSC;
		SetLoad2SC;
//		if(bSmokeOut==1) { SetLoadSC;}
//		if(bSmokeOut2==1) { SetLoad2SC;}  //改为上面的
	}
}
/*--------------------------------------------------------------*/
void PortInt() interrupt 	8
{
	unsigned char PortBuffer=0;
	PortBuffer = PORTIDX;
	if((INTFLG&PCIF)==PCIF)               //PORT口变化中断
	{
	   if((INTPORT&P0IF)==P0IF)           //PORT0.X电平变化
	   {
			 PORTIDX = 0;
		     if((INTPIN&PIN6IF)==PIN6IF)  //P06,USB
			 {
				 INTPIN&=~PIN6IF;
			 }
			 INTPORT&=~P0IF;
	   }
	   if((INTPORT&P3IF)==P3IF)           //PORT3.X电平变化
	   {
			 PORTIDX = 3;
		     if((INTPIN&PIN0IF)==PIN0IF)  //P30,KEY
			 {
				 INTPIN&=~PIN0IF;
			 }
		     if((INTPIN&PIN1IF)==PIN1IF)  //P31,MIC
			 {
				 INTPIN&=~PIN1IF;
			 }
			 INTPORT&=~P3IF;
	   }
		 INTFLG&=~PCIF;
	}
  PORTIDX = PortBuffer;
}
/*----------------------------------------------------------*/
void PWM_Int() interrupt 14
{
	
}
/*------------------------------------------------------------*/
void Timer0_Int() interrupt 1
{
//	TH0 =(65536 - 9216 )/256;   // 100US
//	TL0 =(65536 - 9216 )%256;
	TH0 = TIME_RELOAD/256;
	TL0 = TIME_RELOAD%256;

	Time10mSCnt++;
	if(Time10mSCnt >= 100)//10ms
	{
//		P1_5 ^= 1;
//		P1_2 ^= 1;

		Time10mSCnt = 0;
		bTime10mS = 1;
		bTimeBat = 1;
		DelayState ++;
		TimeDelaymS ++;
		if(MainState==MainSmoke) SmokeTime++;
		Time100mSCnt++;
		if(Time100mSCnt >= 10)
		{
			Time100mSCnt = 0;
			bTime100mS = 1;
			
			if(MainState==MainSmoke)
			{
				PuffTime++;
				
				if(SmokeMode ==1)
				{
					SmokeTimeCnt1++;
					if(SmokeTimeCnt1 > OilTimeMax1) {SmokeTimeCnt1 = OilTimeMax1;}
				}
				else if(SmokeMode ==2)
				{
					SmokeTimeCnt2++;
					if(SmokeTimeCnt2 > OilTimeMax2) {SmokeTimeCnt2 = OilTimeMax2;}
				}
				else
				{
					SmokeTimeCnt++;
					if(SmokeTimeCnt > OilTimeMax) {SmokeTimeCnt = OilTimeMax;}
				}				
			}
		}
	}
//	/*
	if(MainState==MainSmoke)
	{
		if(bSmokeOut==1)
		{
			PwmPeriodCnt++;
			if(PwmPeriodCnt>=PwmDutyMax)	{PwmPeriodCnt=0;}
			if(PwmPeriodCnt == 15) {bOutCheck=1;}
			if(PwmPeriodCnt == 30) {bBatCheck=1;}
		}
		else {PwmHigh;}
	#if(TwoLoadForT == 1)
		if(bSmokeOut2==1)
		{
			Pwm2PeriodCnt++;
			if(Pwm2PeriodCnt>=PwmDutyMax)	{Pwm2PeriodCnt=0;}
			if(Pwm2PeriodCnt == 15) {bOut2Check=1;}
			if(Pwm2PeriodCnt == 30) {bBatCheck=1;}
		}
		else {Pwm2High;}
	#endif
	}
//	*/
	LedRenewDelay++;
	LedPRenewDelay++;
	
	#if(LedPForT == 1)
	LedPScan();
	#endif
	
	#if(LedBreatheForT == 1)
//	LedBreathe();
	#endif
	
}
/*--------------------------------------------------------------*/
void DelayNuS(unsigned int cnt)
{
	unsigned int i;
//	unsigned char delay_cnt;
	for(i = 0;i<cnt;i++)
	{
		_nop_();_nop_();_nop_();_nop_();_nop_();
	}
}
/*--------------------------------------------------------------*/
//
