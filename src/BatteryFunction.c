/*--------------------------------------------------------------*/
#include "Global.h"
/*--------------------------------------------------------------*/
uint8_t BatPowPercent,BatLevel;
uint8_t BatState,LowBatCounter,BatCounter,BatPowCnt;
uint8_t BatScanCnt,BatODCounter;
uint16_t	RefVddValue,BatVolValue,UsbVolValue;

/*--------------------------------------------------------------*/
uint8_t UsbState,UsbCounter,ChargeStep,ChargeDelayCnt;
uint8_t ChrgLevel;
uint16_t ChargeTime;
/*--------------------------------------------------------------*/
ByteBit      BatFlag,UsbFlag,OilFlag;
/*--------------------------------------------------------------*/
/*--------------------------------------------------------------*/
/*--------------------------------------------------------------*/
 /*--------------------------------------------------------------*/
void ReadBatteryVoltage(void)   //��ȡ��ص�ѹ
{	
	uint32_t m,n;
	m = (uint32_t)ADCModule(AD_1V2,10);//HAL_ADC_Sample(ADC_CH_IBAT, True); // AD_1V2��ADͨ��ֵ  ��V���������� 
	n = 4915200 /m; // 1.20*1000*4096/ADֵ
					//n = 4915200 / m; ������㹫ʽ���� ADC �Ĳ���ֵ m �������ѹֵ����ʽ�е� 4915200 ��ͨ�����¼���õ��ĳ�����1.20 * 1000 * 4096��
                    //1.20V �ǲο���ѹ��RefVdd����1000 ��Ϊ�˽���ѹת��Ϊ������4096 �� ADC �ķֱ��ʣ�12 λ ADC��

	RefVddValue = (uint16_t) n; //������õ��ĵ�ѹֵ n ת��Ϊ uint16_t ���ͣ���ֵ�� RefVddValue
	BatVolValue = RefVddValue + 30;  //�� RefVddValue ���е������õ����յĵ�ص�ѹֵ BatVolValue���˴�������һ������ 30��Ϊ��У׼�򲹳����
/*
	uint32_t m,n;
//	m = (uint32_t)ADC_mean(AD_1V2);   //��һ���㷨
	n = (uint32_t)Ref1V2;
	n = n*4096;
	n = n/m;
	RefVddValue=(uint16_t)n;
	BatVolValue=RefVddValue+110;//30;
	*/
}
/*----------------------------------------------------------------------------*/
void CheckBatteryState(void)    //�����״̬���ر����жϵ�ص�ѹ�Ƿ�����趨����ֵ�����ݴ˸��µ��״̬��Ϣ
{
	if(BatVolValue >= LowBatVoltage)    //�Ƚϵ�ǰ��ص�ѹֵ BatVolValue �Ƿ���ڻ���ڵ͵�ѹ��ֵ LowBatVoltage��
										//����ǣ��� bBatStateNew ����Ϊ 1����ʾ��ص�ѹ��������
										//���򣬽� bBatStateNew ����Ϊ 0����ʾ��ص�ѹ�ͣ���
		bBatStateNew =1;
	else 
		bBatStateNew =0; 

	if(bBatStateNew == bBatStateOld)   //����¾ɵ��״̬û�б仯���� bBatStateNew ���� bBatStateOld������ LowBatCounter ����������Ϊ 0
		 LowBatCounter=0;
		  
	if(++LowBatCounter >= 100)   // ���µ͵�ѹ����������鳬ʱ   ÿ�ε��� CheckBatteryState ����ʱ��LowBatCounter ���������� 1
	{
		LowBatCounter=0;
		bBatStateOld = bBatStateNew;
		if(bBatStateOld==0) { bBatLow = 1;BatPowPercent=0;}
	}
}
/*--------------------------------------------------------------*/
/*--------------------------------------------------------------*/
void CheckBatODState(void)  //����صĹ��ŵ�״̬�������ݵ�ص�ѹ״̬������Ӧ�ı�־λ
{
	uint16_t TempR16;
	if(bBatODOld == 1) TempR16 = ODBatVoltage +300; //ȷ����ѹ��ֵ     300:ƫ��
													//�����״̬ bBatODOld Ϊ 1����ʾ���ŵ�״̬�����򽫵�ѹ��ֵ TempR16 ����Ϊ ODBatVoltage + 300
	else TempR16 = ODBatVoltage;

	if(BatVolValue >= TempR16) bBatODNew =0;
	else bBatODNew =1;
	if(bBatODNew == bBatODOld) BatODCounter=0;
	if(++BatODCounter >= 100)   //���¹��ŵ�״̬����������鳬ʱ
	{
		BatODCounter=0;
		bBatODOld = bBatODNew;  //���¾ɵĹ��ŵ�״ֵ̬Ϊ��ǰ����״ֵ̬
		if(bBatODOld == 1) {bBatOD=1; bBatLow = 1;BatPowPercent=0;}
	}
}
/*--------------------------------------------------------------*/
/*--------------------------------------------------------------*/
/*--------------------------------------------------------------*/
/*--------------------------------------------------------------*/
void CheckChgBatPercent(void)
{
	uint8_t	  TempR8;
//	uint16_t TempR16;
	TempR8 = CalBatPercent(BatVolValue+BalVolChgOffset);//TempR16);
	if(TempR8 <= BatPowPercent)
	{
		if((BatPowPercent-TempR8) > 10)
		{
				if(++ChargeDelayCnt > 15)
				{ChargeDelayCnt=0;BatPowPercent=TempR8;} 
		}
		else {ChargeDelayCnt=0;}
		BatPowCnt=0;
	}
	else {ChargeDelayCnt=0;}
	if(BatPowPercent<75) TempR8=30;	//30S
	else if(BatPowPercent<95) TempR8=60;	//60S
	else TempR8=90;	//90S
	++BatPowCnt;	
	if(BatPowCnt>TempR8)
	{
		BatPowCnt=0;
		if(BatPowPercent<BatPercentMax){ BatPowPercent +=BatPerStep;PuffTime=0;}
		CalBatLevel();
	}
}
/*--------------------------------------------------------------*/
#if(ChargeSAdorIO == 1)
void CheckUsbState(void)
{
	uint16_t Temp16;
	Temp16 = ADC_mean(AD_UsbChannel);
	
	
}
#endif
/*--------------------------------------------------------------*/
#if(UsbAdorIO == 0)
void CheckUsbState(void)
{
	if(USB_TRUE) bUsbNew = 1;
	else bUsbNew = 0;
	if(bUsbOld == bUsbNew) UsbCounter = 0;
	if(++UsbCounter>=10)
	{
		UsbCounter = 0;
		bUsbOld = bUsbNew;
		if(bUsbOld == 1)	UsbState = 1;
		else UsbState = 0;
	}
}
#endif
/*--------------------------------------------------------------*/
#if(UsbAdorIO == 1)
void CheckUsbState(void)
{
	uint32_t m;
	uint16_t m0,m1,m2;
	m = (uint32_t)ADC_mean(AD_UsbChannel);
	m = m*RefVddValue;
	m = m * 11;
	m = m/4096;
	UsbVolValue=(uint16_t) m;	
	m0=UsbNcVol;m1=UsbOkVol;m2=UsbOvpVol;
	if(UsbVolValue<m0)
	{
		if(UsbState==UsbNc) {UsbCounter=0;return;}
		if(++UsbCounter >= 10)
		{
			UsbCounter=0;UsbState=UsbNc;
		}
	}
	else if(UsbVolValue<m2)
	{
		if(UsbState==UsbHigh) {UsbCounter=0;return;}
		if(++UsbCounter >= 10)
		{
			UsbCounter=0;UsbState=UsbOk;
		}
	}
	else
	{
		if(UsbState==UsbOvp) {UsbCounter=0;return;}
		if(++UsbCounter = 10)
		{
			UsbCounter=0;UsbState=UsbOvp;
		}
	}
//  UsbState=1;
}
#endif
/*--------------------------------------------------------------*/
void IniChargeMode(void)
{
	if(MainState==MainCharge) return;
	DelayState=0;	
	ChargeStep=0;
	ChargeTime=0;
	ChrgLevel = BatLevel;
	LEDP_CHARGE;
	MainState=MainCharge;			
}
/*--------------------------------------------------------------*/
void SetChargeFullState(void)
{
	ChargeStep = 2;
	PuffTime =0;
	ChargeTime = 0;
	BatPowPercent=BatPercentMax;
}
/*--------------------------------------------------------------*/
void CheckChargeState(void)  //��纯��
{
	uint16_t TempV;
	ChargeTime++;
	TempV = BatVolValue + BalVolOffset;
	switch(ChargeStep)
	{
		case 0:
		{
			if(ChargeTime > 5) ChargeStep=1;
			break;
		}
		case 1:
		{
			if(ChargeTime >= ChargeTimeMax)
			{
				SetChargeFullState();	
				break;
			 }
			if(TempV>=BatFullVol)  //4.15V
			{
				if((ChargeTime%15) == 0)	//15S
				{
					if(BatPowPercent<BatPercentMax)
					{
						++BatPowPercent;
						//CalBatLevel();  //
						PuffTime=0;
					}
					else {SetChargeFullState();	}
				}
			}
			else if(TempV>=BatFullVol1)  //4.0V
			{
				if((ChargeTime%60) == 0)	//60S
				{
					if(BatPowPercent<BatPercentMax)
					{
						++BatPowPercent;
						//CalBatLevel();  //
						PuffTime=0;
					}
					else {SetChargeFullState();	}
				}
			}
			break;
		}
		case 2:
		{
			 if(ChargeTime > 15) ChargeStep=3;
			break;
		}
		case 3:
		{
			
			break;
		}
		default:{break;}
	}	
}
/*--------------------------------------------------------------*/
void BatChargeFunction(void)   //��س�纯��
{
	if(bTimeBat == 0) return;   // ��� bTimeBat Ϊ 0�������������أ������κδ���						
	bTimeBat = 0;
	if(++BatScanCnt < 100) return;//���򣬽� bTimeBat ����Ϊ 0������ֻ�е� BatScanCnt �ﵽ 100 ʱ�Ż����ִ��
	BatScanCnt=0;
	CheckChgBatPercent();//����ص����ٷֱ�
	CheckChargeState();//������粽��
	if(bBatLow==1)
	{
		if(BatPowPercent > 0) bBatLow=0;   //��� bBatLow Ϊ 1���� BatPowPercent ���� 0���� bBatLow ����Ϊ 0
	}
}
/*--------------------------------------------------------------*/
const uint16_t code TabBatVol[]=
{
//	 <=0% <=5%<=15%<=20%<=25%<=30%<=35%<=40%<=45%<=50%  
	3500,3550,3600,3650,3675,3700,3725,3750,3775,3800,
//	<=55%<=60%<=65%<=70%<=75%<=80%<=85%<=90%<=95%<=100%
	3815,3830,3845,3860,3890,3905,3920,3950,4000,4050,4100,
////	 <=0% <=5%<=15%<=20%<=25%<=30%<=35%<=40%<=45%<=50%  
//	3200,3275,3350,3425,3500,3550,3600,3650,3700,3750,
////	<=55%<=60%<=65%<=70%<=75%<=80%<=85%<=90%<=95%<=100%
//	3800,3830,3860,3880,3910,3940,3970,4000,4030,4060,4100,
	
};
/*--------------------------------------------------------------*/
uint8_t CalBatPercent(uint16_t VData)   //��������ĵ�ѹֵ VData �����صĵ����ٷֱ�
{
	uint8_t i,j;
	uint16_t m,n;
	for(i=0;i<21;i++)
	{
		if(VData<=TabBatVol[i])     //������������������С��ѹֵ���˳�����
			break;
	}
	#if(BatPerStep==1)    //��һ
	if(i>=21) 
	{
		i=100;
	}
	else if(i>0)
	{
		m = (TabBatVol[i]-TabBatVol[i-1])/5;
		n = VData - TabBatVol[i-1];
		n = n/m;
		j = (uint8_t) n;
		if(j>5) j = 5;
		i -=1;
		i *=5;
		i +=j;
	}	
	#endif
	#if(BatPerStep==5)
	if(i>=21) {i=100;}
	else if(i>0)
	{
		i -=1;
		i *=BatPerStep;
	}	
	#endif
	if(i>100) i=100;
	return i;	
}
/*--------------------------------------------------------------*/
void CalBatLevel(void)
{
	if(BatPowPercent == 0) BatLevel=0;
	else if(BatPowPercent <= 10) BatLevel=1;
	else if(BatPowPercent <= 30) BatLevel=2;
	else if(BatPowPercent <= 60) BatLevel=3;
	else BatLevel = 4;
}
/*--------------------------------------------------------------*/
/*--------------------------------------------------------------*/
