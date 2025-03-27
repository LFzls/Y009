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
	if(bMicNew == bMicOld) {MicScnCnt = 0;}    // 如果当前麦克风状态 bMicNew 与上一个状态 bMicOld 相同，则将 MicScnCnt 置为 0
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
   if(SwAdValue < SwAdValue0) SwStateNew=0x01;	//左边		//
   else if(SwAdValue < SwAdValue1) SwStateNew=0x02; //右边  //应该是1/11Vcc，上面的是<150,应该是0    最左边关机，中间开机加单发，右边双发 
   else  SwStateNew=0x03;  //中间

//    if(SW_TRUE) {F_SwOld=1;F_SwNew=1;}
	SwStateOld = SwStateNew;
	// if(SwStateOld==1) FlavorMode=0;
	// else if(SwStateOld==2) FlavorMode=1;    //这边要换成三种状态，单发，双发，关机
	// else { FlavorMode=2;}
	if(SwStateOld==1) {ChanNum = 0;}   //这里要改成关机标志吗
	else if(SwStateOld==2) ChanNum = 1;        //这边要换成三种状态，单发，双发，关机
	else 	
	{
		MainState = MainTurnOn;
		IniMainTurnOn();   //不加这个，拨到左边睡眠的时候要先跳出睡眠，才能唤醒，就要先拨动一次开关，再重新拨动一次
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
