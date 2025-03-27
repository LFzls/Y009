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
void InitializeLedPMode(uchar LMode,uchar FTimes)     //����LED��ʾģʽ    LMode:��ʾģʽ  FTimes:��˸����
{ 
	if(LedPMode==LMode) 
		return;   //���������ģʽ��ֱ�ӷ���

	LedPCounter=FTimes;    //����LED��˸����
	LedPMode=LMode;        //���� LED ��ʾģʽ
	LedPDelay = 0;		   //���� LED �ӳټ�����
	bLedPFlash = 1;        //���� LED ��˸��־Ϊ 1����ʾ������˸
	if(LedPMode == LedPScreenOn)
	{
		LedPStep =1; 		// ���ģʽ�ǳ���ģʽ������ LED ����Ϊ 1
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
void DisplayNumber(void)     //��ʾ�����1���֣�δ�Ӱ�λ����1��
{
	if(LedDigTab[SBit] & 0x01) {LedPBufferData[0] |= 0x02;}	//a   //COM1Ϊ�ͣ�00000001��ӦCOM2Ϊ�ߣ���L2Ϊ1��L1Ϊ0
	if(LedDigTab[SBit] & 0x02) {LedPBufferData[0] |= 0x04;}	//b	   //L1��L3�ߣ�����
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

void DisplayNumber1(void)     //��ʾ�����2���֣�δ�Ӱ�λ����1��
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
void DisplaySmokePower(uint8_t PData)   //��ʾ�����1���֣�������
{
	uint8_t TempR8; 
	TempR8 = PData;//RefPowerTab[SmokeMode];
	if(TempR8>99) 
	{
		
		HexToDec(0);
		DisplayNumber();
		LedPBufferData[2] |= (0x08);   //���ְ�λ1
	}
	else
	{	
		HexToDec(TempR8);
		DisplayNumber();
	}
}

void DisplayOilPower(uint8_t PData1)   //��ʾ�����2���֣�������
{
	uint8_t Temp1R8;
	Temp1R8 = PData1;//RefPowerTab[SmokeMode];
	if(Temp1R8>99) 
	{
		
		HexToDec(0);
		DisplayNumber1();
		LedPBufferData[4] |= (0x40);   //���ְ�λ1
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
	LedPBufferData[6] |= (0x02);    //����ͼ��
	DisplaySmokePower(BL1);   //����ֵ
}

void DisplayOilPercent(uint8_t OL1)
{
	LedPBufferData[6] |= (0x04);   //�ͱ�
	DisplayOilPower(OL1);	 //����ֵ
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
		LedPBufferData[5] |= (0x01);   //��һ�񵽵��߸�Ҫ������
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
/*************************************     ��־��      ********************************************/
/**************************************************************************************************/
void Displayflower(void)   //����
{
	LedPBufferData[6] |= (0x10);
	LedPBufferData[6] |= (0x20);
}

void Displayflower1(void)  //����
{
	LedPBufferData[6] |= (0x08);
}

void Displaystar1on(void)    //����1
{
	Led1On;
}
void Displaystar1off(void)   
{
	Led1Off;
}


void Displaystar2on(void)    //����2
{
	Led2On;
}

void Displaystar2off(void)   
{
	Led2Off;
}


void Displaystar3on(void)    //����3
{
	Led3On;
}

void Displaystar3off(void)    
{
	Led3Off;
}
void Displaycityon(void)    //���м����
{
	Led4On;
}

void Displaycityoff(void)    
{
	Led4Off;
}

void Display_BeidouStaron(void)
{
	LedPBufferData[5] |= (0x01);   //��һ�񵽵��߸�Ҫ������
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

void RenewLedPScanData(void)   //���� LED ��ʾ�����ݣ�����黺������ɨ�������Ƿ�һ�¡�
{
	uint8_t i;
	bLedPRenewD=0;
	for(i=0;i<LedPComN;i++)   //���� LedPComN ��������Ƚ� LedPScanData �� LedPBufferData��
	{
		if(LedPScanData[i]!=LedPBufferData[i])
		{
			bLedPRenewD=1;   //������ݲ�һ�£����� bLedPRenewD Ϊ 1��
			break;
		}
	}	
	if(bLedPRenewD==0) return;
	bLedPRenewD=0;
	ET0 = 0;   //�ر�Timer0 �ж�ʹ��
	for(i=0;i<LedPComN;i++)
	{
		LedPScanData[i]=LedPBufferData[i];  //�� LedPBufferData �����ݿ����� LedPScanData ��
	}
	ET0 = 1;  //��Timer0 �ж�ʹ��
}
/*---------------------------------------------------------------*/
void LedPController(void)
{
//	uint8_t m;
	uint16_t m0;
	if(LedPRenewDelay<10) return;   //LedPRenewDelay:LED ˢ���ӳټ����� 
									//��� LedPRenewDelay С�� 10��ֱ�ӷ��أ���ζ���ڴ������²�ִ�к������롣����Ϊ��ȷ���ڽ϶̵�ʱ�����ڲ����� LED ����
	LedPRenewDelay=0;
	LedPDelay++;
	if(LedPDelay>60000) LedPDelay=0;	//���� LedPDelay ����������������� 60000��������Ϊ 0�������ڿ��� LED �ĸ���Ƶ��
	SetLedPBuffer(0);   // ������LED�رգ�׼�������µ�״̬����
	m0 = 250;
	if(LedPMode == LedPCharging) {m0 = 500;}
	if((LedPDelay%m0)==0)		//��� LedPDelay �� m0 ȡģΪ 0����˵�������˸�����˸״̬��ʱ��
	{
		if(bLedPFlash==0) {bLedPFlash=1;}		//��� bLedPFlash Ϊ 0���л�Ϊ 1����ʾ��ǰ LED ������˸״̬
		else
		{
			bLedPFlash = 0;				//��� bLedPFlash Ϊ 1���л�Ϊ 0����ʾ��ǰ LED ���ڹر�״̬
			if(LedPCounter>0)	//��� LedPCounter ���� 0������ LedPCounter ��ֵ��������������� 0����ִ�� LEDP_ALLOFF���ر����� LED������ bKeyEnable ����Ϊ 0������������������
			{
				if(--LedPCounter == 0)
				{
//					if(LedPMode==LedPBatLow) {LEDP_ALLOFF;bKeyEnable =0;}
//					else { LEDP_STANDBY;	}				
					LEDP_ALLOFF;
				//	bKeyEnable =0;  //��ֹ����
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
				 Display_BeidouStaron(); 	//�������ǵ�
			
			if(ChanNum==1)  //����
			{
				Displayflower();	//����
				
			}
			else if(ChanNum==2)  //˫��
			{
				//bLedBreathe2=1;
					Displayflower();  //����
					Displayflower1(); //����
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
			if(ChanNum==1)  //����
			{
				Displayflower();	//����
				
			}
			else if(ChanNum==2)  //˫��
			{
				//bLedBreathe2=1;
					Displayflower();  //����
					Displayflower1(); //����
			}			
			
			break;
		}
		case LedPSmokeOver:   //��ʱ��Ч����ǰ��λ��˸2��
		{

			Displaycityon();   //����˸��ǰ��������188��
			Displaystar1on();
			Displaystar2on();
			Displaystar3on();
			DisplayBatPercent(BatPowPercent);
			DisplayOilPercent(OilPercent);
			if(ChanNum==1)  //����
			{
				Displayflower();	//����
				
			}
			else if(ChanNum==2)  //˫��
			{
				//bLedBreathe2=1;
					Displayflower();  //����
					Displayflower1(); //����
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
		case LedPBatLow:   //��˸ʮ��
		{
			if(bLedPFlash == 1)
			{
			Displaycityon();
			Displaystar1on();
			Displaystar2on();
			Displaystar3on();
			DisplayBatPercent(BatPowPercent);					
			Displayflower();  //����
			Displayflower1(); //����
			Display_BeidouStaron();  //�������ǵ�
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

		case LedPOilLow:   //��˸ʮ��
		{
			if(bLedPFlash == 1)
			{
			Displaycityon();
			Displaystar1on();
			Displaystar2on();
			Displaystar3on();
			// DisplayBatPercent(BatPowPercent);					
			Displayflower();  //����
			Displayflower1(); //����
			Display_BeidouStaron();  //�������ǵ�
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
				LedPBufferData[4] |= (0x40);    //����1
				LedPBufferData[2] |= (0x08);	//����
				if(SmokeMode==0)  //����
				{
					Displayflower();	//����
					Display_BeidouStaron(); 
				}
				else if(SmokeMode==1)  //˫��
				{
					Displayflower();  //����
					Displayflower1(); //����
					Display_BeidouStaron();  //�������ǵ�
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
				Displayflower();  //����
			    Displayflower1(); //����  //�ȹص������ԣ�����ǵô�
				Display_BeidouStaron();  //�������ǵ�				
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
						LedPBufferData[6] |= (0x02);   //����ͼ����˸
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
	if(++LedPScanT<3)    //����ɨ�����ڣ�ɨ�����
		return;			//300usɨ��һ�� 
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
		{   											//����
			LED_COM7_LOW;
			if(LedPScanData[6]&0x01) {LED_COM1_HIGH;}
			if(LedPScanData[6]&0x02) {LED_COM2_HIGH;}
			if(LedPScanData[6]&0x04) {LED_COM3_HIGH;}
			if(LedPScanData[6]&0x08) {LED_COM4_HIGH;}    //Ҷ�ӣ�����Ҫ������
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






