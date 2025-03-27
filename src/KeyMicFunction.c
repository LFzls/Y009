/******************************************************************************
 ** Function :	KeyMicFunction.c
 ******************************************************************************/

/******************************************************************************
 ** Include files
 ******************************************************************************/
#include "Global.h"
/*----------------------------------------------*/
#define SwitchTorF 1
uint8_t MicScnCnt;
ByteBit MicInfoFlag;
void MicIni(void)
{
	MicScnCnt = 0;
	bMicNew = 0;
	bMicOld = 0;
}
void MicScan(void)
{
	if(MIC_TRUE) bMicNew =1;
	else bMicNew = 0;
	if(bMicNew == bMicOld) {MicScnCnt = 0;}    // �����ǰ��˷�״̬ bMicNew ����һ��״̬ bMicOld ��ͬ���� MicScnCnt ��Ϊ 0
	if(++MicScnCnt >= 3)
	{
		MicScnCnt = 0;
		bMicOld = bMicNew;		
	}
}    
/*----------------------------------------------*/
uint8_t KeyScanCnt,KeyCounter;
uint16_t KeyDelayCnt,KeyCntDelay;
ByteBit KeyInfoFlag;
/*----------------------------------------------*/
/*------------------------------------------*/
#if(SwitchTorF==1)
uint8_t SwScanCnt;
uint8_t SwStateNew,SwStateOld;
uint16_t SwAdValue;
//bit F_SwNew;
//bit F_SwOld;
void SwitchIni(void)
{
   SwInAD;
	SwScanCnt=0;
//	F_SwNew = 0;
//	F_SwOld = 0;

   SwStateNew = 0;
	SwAdValue=ReadAdResult(ADC_CH_SW);
   if(SwAdValue < SwAdValue0) SwStateNew=0x01;	//���		//
   else if(SwAdValue < SwAdValue1) SwStateNew=0x02; //�ұ�  //Ӧ����1/11Vcc���������<150,Ӧ����0    ����߹ػ����м俪���ӵ������ұ�˫�� 
   else  SwStateNew=0x03;  //�м�

//    if(SW_TRUE) {F_SwOld=1;F_SwNew=1;}
	SwStateOld = SwStateNew;
	// if(SwStateOld==1) FlavorMode=0;
	// else if(SwStateOld==2) FlavorMode=1;    //���Ҫ��������״̬��������˫�����ػ�
	// else { FlavorMode=2;}
	if(SwStateOld==1) {ChanNum = 0;}   //����Ҫ�ĳɹػ���־��
	else if(SwStateOld==2) ChanNum = 1;        //���Ҫ��������״̬��������˫�����ػ�
	else 	
	{
		MainState = MainTurnOn;
		IniMainTurnOn();   //����������������˯�ߵ�ʱ��Ҫ������˯�ߣ����ܻ��ѣ���Ҫ�Ȳ���һ�ο��أ������²���һ��
		ChanNum = 2;   
	}
	
}
void SwitchScan(void)
{
   SwInAD;
   SwStateNew = 0;
   SwAdValue=ReadAdResult(ADC_CH_SW);
   if(SwAdValue < SwAdValue0) {SwStateNew=0x01;ChanNum = 0;}
   else if(SwAdValue < SwAdValue1) SwStateNew=0x02;
   else  SwStateNew=0x03;

	if(SwStateNew == SwStateOld)
	{
		SwScanCnt=0;
	}
	if(++SwScanCnt >=15)
	{
		SwScanCnt=0;
		SwStateOld = SwStateNew;
  	 if(SwStateOld == 1) 
		{
			ChanNum = 0;
			MainState = MainTurnOff;
			IniMainTurnOff();
		 }
	  	else if(SwStateOld == 2) 	ChanNum = 1;		
		  else
		  {
			MainState = MainTurnOn;
		  IniMainTurnOn();
			ChanNum =2;		
		  }
	 }
}
#endif
/*------------------------------------------*/
