/*--------------------------------------------------------------*/
#include "Global.h"
/*--------------------------------------------------------------*/

#if(LedForT==1)
uint8_t LedMode,LedModeBak,LedCounter;
uint8_t LedPeriod,LedDuty,LedDutyTime,LedScanT;
uint8_t LedPeriod1,LedDuty1;
uint8_t LedOffDelayCnt1;
uint8_t LedPeriod2,LedDuty2;
uint8_t LedOffDelayCnt2;
uint8_t LedRenewDelay,LedOffDelayCnt;
uint16_t LedDelayCnt;
ByteBit     LedFlag,LedFlag1;
uint8_t LedPStep1 = 0;
#endif

uint8_t	SBit,GBit;//QBit,BBit,
uint8_t LedPMode,LedPCounter,LedPStep,LedPRenewDelay;
uint8_t LedPScanT,LedPScanStep;
uint16_t LedPDelay;
ByteBit     LedPFlag;
#if(LedPComN<=8)
uint8_t LedPBufferData[LedPComN];
uint8_t LedPScanData[LedPComN];
#else
uint16_t LedPBufferData[LedPComN];
uint16_t LedPScanData[LedPComN];
#endif

/*--------------------------------------------------------------*/
const uint8_t LedDigTab[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00,0xff};  //0-9
//const uint8_t LedSBitTab[]={0x7e,0x48,0xba,0xda,0x5c,0xd6,0xf6,0x4a,0xfe,0xde,0x00,0xff};
//const uint8_t LedGBitTab[]={0x75,0x24,0x5c,0x6c,0x2d,0x69,0x79,0x24,0x7d,0x6d,0x00,0x7f};
//const uint16_t LedG1BitTab[]={0x100,0x000,0x100,0x100,0x000,0x100,0x100,0x100,0x100,0x100,0x00,0x100};

/*--------------------------------------------------------------*/
void IniLedPBreathe(uint8_t LedPF)
{
	if(LedPF==0)
	{
		bLedBreathe = 0;
		bLedBreathe2 = 0;
		bLedGrad =0;
		return;
	}
	if(bLedBreathe==0)
	{
		LedDuty=0;
		bDutyInc=1;
		LedPeriod=0;
		bLedBreathe =1;	
	}
	if(SmokeMode==0)
	{
		bLedBreathe2 =0;
		if(bLedGrad == 0)
		{
			bDuty1Inc =1;
			LedPeriod1=0;
			LedDuty1=0;
			bLedGrad =1;
		}
	}
	else
	{
		bLedGrad =0;
		if(bLedBreathe2 == 0)
		{
			LedDuty2=BLNDuty;
			bDuty2Inc=0;
			LedPeriod2=0;
			bLedBreathe2 =1;	
		}
	}	
}

#if(LedForT==1)
void IniLedMode(uchar LMode,uchar FTimes)
{
	if(LedMode==LMode) return;
	bLedBreathe =0;
	LedPeriod=0;
	LedPeriod1=0;
	LedPeriod2=0;
	LedDutyTime=0;
	if(LMode==LedGradOn || LMode==LedBreatheState
		|| LMode==LedSmoking || LMode==LedCharging
		|| LMode==LedScreenOn)
	{
		LedDuty=0;
		bDutyInc=1;
		LedDuty2=0;
		bDuty2Inc=1;
		bLedBreathe =1;
	}
	else if(LMode == LedGradOff)
	{
		LedDuty=BLNDuty;
		bDutyInc=0;
		bLedBreathe =1;
	}
	LedCounter=FTimes;
	LedDelayCnt = 0;

	LedMode=LMode; 
}
/*--------------------------------------------------------------*/
/*--------------------------------------------------------------*/
void LedBreathe(void)
{
	if(bLedBreathe == 0) return;//LedMode!=LedBreatheState && LedMode!=LedGradOff) return;
	LedPeriod++;	
	
	if(++LedDutyTime>=110)	//11mS
	{
		LedDutyTime=0;
		if(bDutyInc==1)
		{
			LedDuty++;
			if(LedDuty>=BLNDuty)
			{
				bDutyInc=0;
			}
		}
		else 
		{
			if(LedDuty>=1) {LedDuty--;LedOffDelayCnt=0;}
			else
			{
					if(++LedOffDelayCnt>=18)	//198mS Off
					{
						bDutyInc=1;
					}
			}
		}
		if(bLedGrad==1) { if(++LedDuty1>=140) {bLedGrad=0;}}
			
		if(bLedBreathe2)
		{
			if(bDuty2Inc==1)
			{
				LedDuty2++;
				if(LedDuty2>=BLNDuty)		{	bDuty2Inc=0; 	}
			}
			else 
			{
				if(LedDuty2>=1) {LedDuty2--;LedOffDelayCnt2=0;}
				else
				{
					if(++LedOffDelayCnt2>=10)	{	bDuty2Inc=1;	}
				}
			}
		}		
	}
	if(LedPeriod<LedDuty)	{	bLedOn = 1;Displayflower();Displayflower1();}
	else if(LedPeriod<=BLNPeriod)		{	bLedOn = 0;}
	else	{	LedPeriod=0;}
	if(bLedGrad==1)
	{
		LedPeriod1++;	
		if(LedPeriod1<LedDuty1)	{	bLed1On = 1;}
		else if(LedPeriod1<=140)		{	bLed1On = 0;}
		else	{	LedPeriod1=0;}
	}
	if(bLedBreathe2)
	{
		LedPeriod2++;	
		if(LedPeriod2<LedDuty2)	{bLed2On = 1;Displayflower();Displayflower1();}
		else if(LedPeriod2<=BLNPeriod)		{bLed2On = 0;}
		else	{LedPeriod2=0;}
	}
}
/*--------------------------------------------------------------*/

#endif
/*---------------------------------------------------*/
void InitializeLedPMode(uchar LMode,uchar FTimes)     //设置LED显示模式    LMode:显示模式  FTimes:闪烁次数
{ 
	if(LedPMode==LMode) 
		return;   //如果是所需模式，直接返回

	LedPCounter=FTimes;    //设置LED闪烁次数
	LedPMode=LMode;        //更新 LED 显示模式
	LedPDelay = 0;		   //重置 LED 延迟计数器
	bLedPFlash = 1;        //设置 LED 闪烁标志为 1，表示启用闪烁
	if(LedPMode == LedPScreenOn)
	{
		LedPStep =1; 		// 如果模式是常亮模式，设置 LED 步骤为 1
	}
	else 
		LedPStep =0;		
}
/*--------------------------------------------------------------*/
/*--------------------------------------------------------------*/
/*--------------------------------------------------------------*/

void HexToDec(uint16_t DData)
{
  uint16_t n;
  n=DData;
  if(n>100) n = 99;//100;
//  QBit=(uint8_t)(n/1000);
//  n%=1000;
//  BBit=(uint8_t)(n/100);
//  n %= 100;
  SBit=(uint8_t)(n/10);
  GBit=(uint8_t)(n%10);
}

/*---------------------------------------------------------------*/
void DisplayNumber(void)     //显示数码管1数字（未加百位数字1）
{
	if(LedDigTab[SBit] & 0x01) {LedPBufferData[0] |= 0x02;}	//a   //COM1为低，00000001对应COM2为高，即L2为1，L1为0
	if(LedDigTab[SBit] & 0x02) {LedPBufferData[0] |= 0x04;}	//b	   //L1低L3高，类推
	if(LedDigTab[SBit] & 0x04) {LedPBufferData[0] |= 0x08;}	//c
	if(LedDigTab[SBit] & 0x08) {LedPBufferData[0] |= 0x10;}	//d
	if(LedDigTab[SBit] & 0x10) {LedPBufferData[0] |= 0x20;}	//e
	if(LedDigTab[SBit] & 0x20) {LedPBufferData[0] |= 0x40;}	//f
	if(LedDigTab[SBit] & 0x40) {LedPBufferData[1] |= 0x01;}	//g

	if(LedDigTab[GBit] & 0x01) {LedPBufferData[1] |= 0x04;}	//a
	if(LedDigTab[GBit] & 0x02) {LedPBufferData[1] |= 0x08;}	//b
	if(LedDigTab[GBit] & 0x04) {LedPBufferData[1] |= 0x10;}	//c
	if(LedDigTab[GBit] & 0x08) {LedPBufferData[1] |= 0x20;}	//d
	if(LedDigTab[GBit] & 0x10) {LedPBufferData[1] |= 0x40;}	//e
	if(LedDigTab[GBit] & 0x20) {LedPBufferData[2] |= 0x01;}	//f
	if(LedDigTab[GBit] & 0x40) {LedPBufferData[2] |= 0x02;}	//g

}

void DisplayNumber1(void)     //显示数码管2数字（未加百位数字1）
{
	if(LedDigTab[SBit] & 0x01) {LedPBufferData[2] |= 0x10;}	//a   
	if(LedDigTab[SBit] & 0x02) {LedPBufferData[2] |= 0x20;}	//b	  
	if(LedDigTab[SBit] & 0x04) {LedPBufferData[2] |= 0x40;}	//c
	if(LedDigTab[SBit] & 0x08) {LedPBufferData[3] |= 0x01;}	//d
	if(LedDigTab[SBit] & 0x10) {LedPBufferData[3] |= 0x02;}	//e
	if(LedDigTab[SBit] & 0x20) {LedPBufferData[3] |= 0x04;}	//f
	if(LedDigTab[SBit] & 0x40) {LedPBufferData[3] |= 0x10;}	//g

	if(LedDigTab[GBit] & 0x01) {LedPBufferData[3] |= 0x20;}	//a
	if(LedDigTab[GBit] & 0x02) {LedPBufferData[3] |= 0x40;}	//b
	if(LedDigTab[GBit] & 0x04) {LedPBufferData[4] |= 0x01;}	//c
	if(LedDigTab[GBit] & 0x08) {LedPBufferData[4] |= 0x02;}	//d
	if(LedDigTab[GBit] & 0x10) {LedPBufferData[4] |= 0x04;}	//e
	if(LedDigTab[GBit] & 0x20) {LedPBufferData[4] |= 0x08;}	//f
	if(LedDigTab[GBit] & 0x40) {LedPBufferData[4] |= 0x20;}	//g

}
/*---------------------------------------------------------------*/
void DisplaySmokeTime(void)
{
	HexToDec(SmokeTime);///10);			
	DisplayNumber();
}
/*---------------------------------------------------------------*/
void DisplaySmokePower(uint8_t PData)   //显示数码管1数字（电量）
{
	uint8_t TempR8; 
	TempR8 = PData;//RefPowerTab[SmokeMode];
	if(TempR8>99) 
	{
		
		HexToDec(0);
		DisplayNumber();
		LedPBufferData[2] |= (0x08);   //数字百位1
	}
	else
	{	
		HexToDec(TempR8);
		DisplayNumber();
	}
}

void DisplayOilPower(uint8_t PData1)   //显示数码管2数字（油量）
{
	uint8_t Temp1R8;
	Temp1R8 = PData1;//RefPowerTab[SmokeMode];
	if(Temp1R8>99) 
	{
		
		HexToDec(0);
		DisplayNumber1();
		LedPBufferData[4] |= (0x40);   //数字百位1
	}
	else
	{	
		HexToDec(Temp1R8);
		DisplayNumber1();
	}
}

/*---------------------------------------------------------------*/
// void DisplaySmokeMode(void)
// {
// 	if(SmokeMode==0) 
// 	LedPBufferData[1]	|= 0x10;
// 	else if(SmokeMode==1) LedPBufferData[2]	|= 0x10;
// 	else LedPBufferData[3]	|= 0x10;
// }
/*---------------------------------------------------------------*/
void DisplayBatPercent(uint8_t BL1)
{
	LedPBufferData[6] |= (0x02);    //闪电图标
	DisplaySmokePower(BL1);   //电量值
}

void DisplayOilPercent(uint8_t OL1)
{
	LedPBufferData[6] |= (0x04);   //油标
	DisplayOilPower(OL1);	 //油量值
}

void DisplayBatLevel(uint8_t BL)
{
	if(BL==0)
	{
			if(LedPMode!=LedPCharging && LedPMode!=LedPScreenOn)
			{
				if(bLedPFlash == 1)		{		LedPBufferData[0]	|= 0x04;	}
			}
			else		{	LedPBufferData[0]	|= 0x04;	}
	}
	if(BL>=1)
	{
			LedPBufferData[0]	|= (0x04);
			LedPBufferData[1]	|= (0x04);
	}
	if(BL>=2)
	{
			LedPBufferData[3]	|= (0x04);
	}
	if(BL>=3)
	{
			LedPBufferData[4]	|= (0x04);
	}
	if(BL>=4)
	{
			LedPBufferData[5]	|= (0x04);
	}
}
/*---------------------------------------------------------------*/
void DisplayOilLevel(uint8_t OL)
{
	if(OL==0)
	{
			if(LedPMode!=LedPScreenOn)
			{
				if(bLedPFlash == 1)
				{
					LedPBufferData[0]	|= 0x08;
				}
			}
	}
	if(OL>=1)
	{
		LedPBufferData[0]	|= 0x08;
		LedPBufferData[1]	|= 0x08;
	}
	if(OL>=2)
	{
		LedPBufferData[6]	|= 0x04;
	}
	if(OL>=3)
	{
		LedPBufferData[7]	|= 0x04;
	}
	if(OL>=4)
	{
		LedPBufferData[8]	|= 0x04;
	}
}
/*---------------------------------------------------------------*/
void DisplayTurnOnOffUI(void)
{
	if((LedPDelay%200)==0)
	{
		if(bLedPStepID==1)
		{
			LedPStep++;
			if(LedPStep>10)
			{
				LEDP_STANDBY;
//				LedPStep=0;
			}
		}
		else
		{
			if(LedPStep == 0)
			{
				LEDP_ALLOFF;
			}
			else LedPStep--;				
		}
	}
	if(LedPStep<8) {}
	else if(LedPStep == 8){}
	else {}
	if(LedPStep>=0)	{}
	if(LedPStep>=1)	{}
	if(LedPStep>=2)	{}
	if(LedPStep>=3)	{}
	if(LedPStep>=4)	{}
	if(LedPStep>=5)	{}
	if(LedPStep>=6)	{}
	if(LedPStep>=7)	{}
	if(LedPStep>=10){}
	}

void DisplaySmokeBeidou(void)
{
	if((LedPDelay%250)==0)
	{
		LedPStep++;
		if(LedPStep>7) LedPStep=0;
	}
	if(LedPStep>=0)
	{
	}
	if(LedPStep>=1)
	{
		LedPBufferData[5] |= (0x01); 
	}
	if(LedPStep>=2)
	{
		LedPBufferData[5] |= (0x01);   
		LedPBufferData[5] |= (0x02);
	}
	if(LedPStep>=3)
	{
		LedPBufferData[5] |= (0x01);   
		LedPBufferData[5] |= (0x02);
		LedPBufferData[5] |= (0x04);
	}
	if(LedPStep>=4)
	{
		LedPBufferData[5] |= (0x01);   
		LedPBufferData[5] |= (0x02);
		LedPBufferData[5] |= (0x04);
		LedPBufferData[5] |= (0x08);
	}
	if(LedPStep>=5)	
	{
		LedPBufferData[5] |= (0x01);   
		LedPBufferData[5] |= (0x02);
		LedPBufferData[5] |= (0x04);
		LedPBufferData[5] |= (0x08);
		LedPBufferData[5] |= (0x10);
	}
	if(LedPStep>=6)
	{
		LedPBufferData[5] |= (0x01);   
		LedPBufferData[5] |= (0x02);
		LedPBufferData[5] |= (0x04);
		LedPBufferData[5] |= (0x08);
		LedPBufferData[5] |= (0x10);
		LedPBufferData[5] |= (0x40);
	}
	if(LedPStep>=7)	
	{	
		LedPBufferData[5] |= (0x01);   //第一格到第七格，要做走马
		LedPBufferData[5] |= (0x02);
		LedPBufferData[5] |= (0x04);
		LedPBufferData[5] |= (0x08);
		LedPBufferData[5] |= (0x10);
		LedPBufferData[5] |= (0x40);
		LedPBufferData[6] |= (0x01);
	}
}

void DisplaySmokestar(void)
{
	switch(LedPStep1)
	{
		case 0:
	{
		Displaystar1on();
		Displaystar2on();
		Displaystar3on();
		break;
	}
	case 1:
	{
		Displaystar1off();
		Displaystar2on();
		Displaystar3on();
		break;
	}	
	case 2:
	{
		Displaystar1on();
		Displaystar2off();
		Displaystar3on();
		break;
	}

	}
}

/**************************************************************************************************/
/*************************************     标志灯      ********************************************/
/**************************************************************************************************/
void Displayflower(void)   //花环
{
	LedPBufferData[6] |= (0x10);
	LedPBufferData[6] |= (0x20);
}

void Displayflower1(void)  //花朵
{
	LedPBufferData[6] |= (0x08);
}

void Displaystar1on(void)    //流星1
{
	Led1On;
}
void Displaystar1off(void)   
{
	Led1Off;
}


void Displaystar2on(void)    //流星2
{
	Led2On;
}

void Displaystar2off(void)   
{
	Led2Off;
}


void Displaystar3on(void)    //流星3
{
	Led3On;
}

void Displaystar3off(void)    
{
	Led3Off;
}
void Displaycityon(void)    //城市加天空
{
	Led4On;
}

void Displaycityoff(void)    
{
	Led4Off;
}

void Display_BeidouStaron(void)
{
	LedPBufferData[5] |= (0x01);   //第一格到第七格，要做走马
	LedPBufferData[5] |= (0x02);
	LedPBufferData[5] |= (0x04);
	LedPBufferData[5] |= (0x08);
	LedPBufferData[5] |= (0x10);
	LedPBufferData[5] |= (0x40);
	LedPBufferData[6] |= (0x01);
}


/*---------------------------------------------------------------*/
void SetLedPBuffer(uint16_t DData)
{
	uint8_t i;
	for(i=0;i<LedPComN;i++)
	{
		LedPBufferData[i]=DData;
	}
}

void RenewLedPScanData(void)   //更新 LED 显示的数据，并检查缓冲区与扫描数据是否一致。
{
	uint8_t i;
	bLedPRenewD=0;
	for(i=0;i<LedPComN;i++)   //遍历 LedPComN 个数据项，比较 LedPScanData 和 LedPBufferData。
	{
		if(LedPScanData[i]!=LedPBufferData[i])
		{
			bLedPRenewD=1;   //如果数据不一致，设置 bLedPRenewD 为 1。
			break;
		}
	}	
	if(bLedPRenewD==0) return;
	bLedPRenewD=0;
	ET0 = 0;   //关闭Timer0 中断使能
	for(i=0;i<LedPComN;i++)
	{
		LedPScanData[i]=LedPBufferData[i];  //将 LedPBufferData 的数据拷贝到 LedPScanData 中
	}
	ET0 = 1;  //打开Timer0 中断使能
}
/*---------------------------------------------------------------*/
void LedPController(void)
{
//	uint8_t m;
	uint16_t m0;
	if(LedPRenewDelay<10) return;   //LedPRenewDelay:LED 刷新延迟计数器 
									//如果 LedPRenewDelay 小于 10，直接返回，意味着在此条件下不执行后续代码。这是为了确保在较短的时间间隔内不进行 LED 更新
	LedPRenewDelay=0;
	LedPDelay++;
	if(LedPDelay>60000) LedPDelay=0;	//增加 LedPDelay 计数器。如果它超过 60000，则重置为 0。这用于控制 LED 的更新频率
	SetLedPBuffer(0);   // 将所有LED关闭，准备进行新的状态更新
	m0 = 250;
	if(LedPMode == LedPCharging) {m0 = 500;}
	if((LedPDelay%m0)==0)		//如果 LedPDelay 对 m0 取模为 0，则说明到达了更新闪烁状态的时机
	{
		if(bLedPFlash==0) {bLedPFlash=1;}		//如果 bLedPFlash 为 0，切换为 1，表示当前 LED 处于闪烁状态
		else
		{
			bLedPFlash = 0;				//如果 bLedPFlash 为 1，切换为 0，表示当前 LED 处于关闭状态
			if(LedPCounter>0)	//如果 LedPCounter 大于 0，减少 LedPCounter 的值。如果计数器减至 0，则执行 LEDP_ALLOFF，关闭所有 LED，并将 bKeyEnable 设置为 0，禁用其他键的输入
			{
				if(--LedPCounter == 0)
				{
//					if(LedPMode==LedPBatLow) {LEDP_ALLOFF;bKeyEnable =0;}
//					else { LEDP_STANDBY;	}				
					LEDP_ALLOFF;
				//	bKeyEnable =0;  //禁止按键
				}
			}
		}
	}
	switch(LedPMode)
	{
		case LedPSolidOff:
		{
			Displaystar1off();  
			Displaystar2off();
			Displaystar3off();
			Displaycityoff();
			break;
		}
		/*-----------------------------------------------------------*/
		case LedPSolidOn:   
		{
			Displaycityon();
			Displaystar1on();
			Displaystar2on();
			Displaystar3on();
			SetLedPBuffer(0Xffff);			
			break;
		}
		/*-----------------------------------------------------------*/
		case LedPPowerOn:
		{		
			// Displaycityon();
			// Displaystar1on();
			// Displaystar2on();
			// Displaystar3on();
			// SetLedPBuffer(0Xffff);
			break;
		}
		/*-----------------------------------------------------------*/
		case LedPTurnOn:
		case LedPTurnOff:
		{
			Displaycityoff();
			Displaystar1off();
			Displaystar2off();
			Displaystar3off();
			break;
		}
		/*-------------------------------------------*/
		case LedPStandby:
		{
			if(ChanNum==0)
			{
				LedPMode = LedPSolidOff;
				break;
			}
			else
				{
				Displaycityon();
				Displaystar1on();
				Displaystar2on();
				Displaystar3on();
				DisplayBatPercent(BatPowPercent);
				DisplayOilPercent(OilPercent);
				 Display_BeidouStaron(); 	//北斗七星灯
			
			if(ChanNum==1)  //单发
			{
				Displayflower();	//花环
				
			}
			else if(ChanNum==2)  //双发
			{
				//bLedBreathe2=1;
					Displayflower();  //花环
					Displayflower1(); //花朵
			}		
		 }
			break;
		}
		/*-----------------------------------------------------------*/
		case LedPSmoking:
		{
			if(ChanNum==0)
			{
				LedPMode = LedPSolidOff;
				break;
			 }
			else
			{
		  if((LedPDelay%500)==0)
		  {
			 LedPStep1++;
			if(LedPStep1>2) LedPStep1=0;
		  }
			 DisplaySmokestar();

			DisplayBatPercent(BatPowPercent);
			DisplayOilPercent(OilPercent);
			DisplaySmokeBeidou();
			Displaycityon();   
			if(ChanNum==1)  //单发
			{
				Displayflower();	//花环
				
			}
			else if(ChanNum==2)  //双发
			{
				//bLedBreathe2=1;
					Displayflower();  //花环
					Displayflower1(); //花朵
			}			
			
			break;
		}
		case LedPSmokeOver:   //超时灯效，当前档位闪烁2次
		{

			Displaycityon();   //是闪烁当前电量还是188？
			Displaystar1on();
			Displaystar2on();
			Displaystar3on();
			DisplayBatPercent(BatPowPercent);
			DisplayOilPercent(OilPercent);
			if(ChanNum==1)  //单发
			{
				Displayflower();	//花环
				
			}
			else if(ChanNum==2)  //双发
			{
				//bLedBreathe2=1;
					Displayflower();  //花环
					Displayflower1(); //花朵
			}		
		}
			break;
		}
		/*-----------------------------------------------------------*/
		/*-----------------------------------------------------------*/
		case LedPScreenOn:
		{
			 

		}
		/*-----------------------------------------------------------*/
		case LedPBatLow:   //闪烁十次
		{
			if(bLedPFlash == 1)
			{
			Displaycityon();
			Displaystar1on();
			Displaystar2on();
			Displaystar3on();
			DisplayBatPercent(BatPowPercent);					
			Displayflower();  //花环
			Displayflower1(); //花朵
			Display_BeidouStaron();  //北斗七星灯
			// DisplayOilPercent(OilPercent);
			}	
			if(bLedPFlash == 0)	
			{
			Displaycityoff();
			Displaystar1off();
			Displaystar2off();
			Displaystar3off();
			}
			break;		
		}

		case LedPOilLow:   //闪烁十次
		{
			if(bLedPFlash == 1)
			{
			Displaycityon();
			Displaystar1on();
			Displaystar2on();
			Displaystar3on();
			// DisplayBatPercent(BatPowPercent);					
			Displayflower();  //花环
			Displayflower1(); //花朵
			Display_BeidouStaron();  //北斗七星灯
			DisplayOilPercent(OilPercent);
			}	
			if(bLedPFlash == 0)	
			{
			Displaycityoff();
			Displaystar1off();
			Displaystar2off();
			Displaystar3off();
			}
			break;		
		}
		/*-----------------------------------------------------------*/
		case LedPAllFlash:
		{
		
		}
		/*-------------------------------------------*/
		case LedPShortC:
		{
		
		 }
		/*-------------------------------------------*/
		case LedPTimeOver:
		{
			if(bLedPFlash==0)
			{
				Displaycityoff();
				Displaystar1off();
				Displaystar2off();
				Displaystar3off();
			}
			if(bLedPFlash==1)
			{				
				Displaycityon();
				Displaystar1on();
				Displaystar2on();
				Displaystar3on();
				DisplayBatPercent(88);
				DisplayOilPercent(88);
				LedPBufferData[4] |= (0x40);    //数字1
				LedPBufferData[2] |= (0x08);	//数字
				if(SmokeMode==0)  //单发
				{
					Displayflower();	//花环
					Display_BeidouStaron(); 
				}
				else if(SmokeMode==1)  //双发
				{
					Displayflower();  //花环
					Displayflower1(); //花朵
					Display_BeidouStaron();  //北斗七星灯
				}
			}				
			break;		 
		
		 }
		/*---------------------------------------*/
		case LedPWarning:
		{
			if(bLedPFlash==0)
			{
				Displaycityoff();
				Displaystar1off();
				Displaystar2off();
				Displaystar3off();
			}
			if(bLedPFlash==1)
			{				
				Displaycityon();
				Displaystar1on();
				Displaystar2on();
				Displaystar3on();
				DisplayBatPercent(88);
				DisplayOilPercent(88);
				LedPBufferData[4] |= (0x40);   
				LedPBufferData[2] |= (0x08);
				Displayflower();  //花环
			    Displayflower1(); //花朵  //先关掉，调试，后面记得打开
				Display_BeidouStaron();  //北斗七星灯				
			}				
			break;	
		}
		/*-----------------------------------------------------------*/
		case LedPCharging:
		{
			switch(ChargeStep)
			{
				case 0:
				{
					DisplaySmokePower(BatPowPercent);
					if(bLedPFlash == 0)
					{
						LedPBufferData[6] |= (0x02);   //闪电图标闪烁
					}
						Displaycityon();
						Displaystar1on();
						Displaystar2on();
						Displaystar3on();
						Display_BeidouStaron();
						Displayflower();
						Displayflower1();
						break;
				}
				case 1:	//Charging
				{				
					DisplaySmokePower(BatPowPercent);
					if(bLedPFlash == 0)
					{
						LedPBufferData[6] |= (0x02);   
					}
						Displaycityoff();
		   			Displaystar1off();
						Displaystar2off();
						Displaystar3off();
					break;
				}
				case 2:	//Charge full
				{
					DisplaySmokePower(BatPowPercent);
					LedPBufferData[6] |= (0x02);
					break;
				}
				case 3:	
				{
					Displaycityoff();
		   			Displaystar1off();
					Displaystar2off();
					Displaystar3off();
					break;
				}
				default:{break;}
			}
			break;
		}
		/*-----------------------------------------------------------*/
		case LedPDebug:
		{

		}
		/*-----------------------------------------------------------*/
		default:{break;}	
	}
	RenewLedPScanData();
}
/*--------------------------------------------------------------*/


void LedPComHighR(void)
{
	LED_COM1 =1;
	LED_COM2 =1;
	LED_COM3 =1;
	LED_COM4 =1;
	LED_COM5 =1;
	LED_COM6 =1;
	LED_COM7 =1;

	PORTIDX = 1;
	PINMOD10 = (PINMOD10 & 0x0f) | (PIN_H_MODE_OD);		//L6
	PINMOD76 = (PINMOD76 & 0x0f) | (PIN_H_MODE_OD);		//L7
	PORTIDX = 2;
	PINMOD10 = (PIN_H_MODE_OD | PIN_L_MODE_OD);			//L1	L2
	PORTIDX =3;
	PINMOD54 = (PINMOD54 & 0x0f) | (PIN_H_MODE_OD); //L5
	PINMOD76 = (PIN_H_MODE_OD | PIN_L_MODE_OD);     //L3	L4
}
/*--------------------------------------------------------------*/
void LedPScan(void)
{
	if(++LedPScanT<3)    //调整扫描周期，扫描快慢
		return;			//300us扫描一次 
	LedPScanT=0;
	LedPComHighR();
	if(bBatOD || LedPMode==LedPSolidOff) return;
//	/*
//	LedPScanStep = 6;
	switch(LedPScanStep)
	{
		case 0:
		{
			LED_COM1_LOW;
//			if(LedPScanData[0]&0x01) {LED_COM1_HIGH;}
			if(LedPScanData[0]&0x02) {LED_COM2_HIGH;}
			if(LedPScanData[0]&0x04) {LED_COM3_HIGH;}
			if(LedPScanData[0]&0x08) {LED_COM4_HIGH;}
			if(LedPScanData[0]&0x10) {LED_COM5_HIGH;}
			if(LedPScanData[0]&0x20) {LED_COM6_HIGH;}
			if(LedPScanData[0]&0x40) {LED_COM7_HIGH;}
			break;
		}
		case 1:
		{
			LED_COM2_LOW;
			if(LedPScanData[1]&0x01) {LED_COM1_HIGH;}
//			if(LedPScanData[1]&0x02) {LED_COM2_HIGH;}
			if(LedPScanData[1]&0x04) {LED_COM3_HIGH;}
			if(LedPScanData[1]&0x08) {LED_COM4_HIGH;}
			if(LedPScanData[1]&0x10) {LED_COM5_HIGH;}
			if(LedPScanData[1]&0x20) {LED_COM6_HIGH;}
			if(LedPScanData[1]&0x40) {LED_COM7_HIGH;}
			break;                                  
		}                                               
		case 2:
		{
			LED_COM3_LOW;
			if(LedPScanData[2]&0x01) {LED_COM1_HIGH;}
			if(LedPScanData[2]&0x02) {LED_COM2_HIGH;}
//			if(LedPScanData[2]&0x04) {LED_COM3_HIGH;}
			if(LedPScanData[2]&0x08) {LED_COM4_HIGH;}
			if(LedPScanData[2]&0x10) {LED_COM5_HIGH;}
			if(LedPScanData[2]&0x20) {LED_COM6_HIGH;}
			if(LedPScanData[2]&0x40) {LED_COM7_HIGH;}
			break;                                  
		}
		case 3:
		{
			LED_COM4_LOW;
			if(LedPScanData[3]&0x01) {LED_COM1_HIGH;}
			if(LedPScanData[3]&0x02) {LED_COM2_HIGH;}
			if(LedPScanData[3]&0x04) {LED_COM3_HIGH;}
//			if(LedPScanData[3]&0x08) {LED_COM4_HIGH;}
			if(LedPScanData[3]&0x10) {LED_COM5_HIGH;}
			if(LedPScanData[3]&0x20) {LED_COM6_HIGH;}
			if(LedPScanData[3]&0x40) {LED_COM7_HIGH;}
			break;                                  
		}                                               
		case 4:
		{
			LED_COM5_LOW;
			if(LedPScanData[4]&0x01) {LED_COM1_HIGH;}
			if(LedPScanData[4]&0x02) {LED_COM2_HIGH;}
			if(LedPScanData[4]&0x04) {LED_COM3_HIGH;}
			if(LedPScanData[4]&0x08) {LED_COM4_HIGH;}
			//if(LedPScanData[4]&0x10) {LED_COM5_HIGH;}
			if(LedPScanData[4]&0x20) {LED_COM6_HIGH;}
			if(LedPScanData[4]&0x40) {LED_COM7_HIGH;}
			break;
		}
	
		case 5:
		{
			LED_COM6_LOW;
			if(LedPScanData[5]&0x01) {LED_COM1_HIGH;}
			if(LedPScanData[5]&0x02) {LED_COM2_HIGH;}
			if(LedPScanData[5]&0x04) {LED_COM3_HIGH;}
			if(LedPScanData[5]&0x08) {LED_COM4_HIGH;}
			if(LedPScanData[5]&0x10) {LED_COM5_HIGH;}
//			if(LedPScanData[5]&0x20) {LED_COM6_HIGH;}
			if(LedPScanData[5]&0x40) {LED_COM7_HIGH;}
			break;
		}
		case 6:
		{   											//花环
			LED_COM7_LOW;
			if(LedPScanData[6]&0x01) {LED_COM1_HIGH;}
			if(LedPScanData[6]&0x02) {LED_COM2_HIGH;}
			if(LedPScanData[6]&0x04) {LED_COM3_HIGH;}
			if(LedPScanData[6]&0x08) {LED_COM4_HIGH;}    //叶子，这里要做呼吸
			if(LedPScanData[6]&0x10) {LED_COM5_HIGH;}
			if(LedPScanData[6]&0x20) {LED_COM6_HIGH;}
//			if(LedPScanData[6]&0x40) {LED_COM7_HIGH;}
			break;
		}
		
		default:{break;}
	}
//	*/
	LedPScanStep++;
	if(LedPScanStep > 7) LedPScanStep=0;
}
/*--------------------------------------------------------------*/


/*--------------------------------------------------------------*/






