#ifndef  _USER_DEFINE_H
#define  _USER_DEFINE_H
/*---------------------------------------------------------------*/
#include "Global.h"

#ifndef EXT_G_DEF
#define EXT_G extern
#else
#define EXT_G
#endif

#define uchar		uint8_t
#define u8			uint8_t
#define u16			uint16_t
#define uint16	uint16_t
#define u32			uint32_t
#define uint32	uint32_t

//typedef union
//{
//  uint8_t Byte;
//  struct
//  {
//    uint8_t Bit0 :1;  //
//    uint8_t Bit1 :1;
//    uint8_t Bit2 :1;
//    uint8_t Bit3 :1;
//    uint8_t Bit4 :1;
//    uint8_t Bit5 :1;
//    uint8_t Bit6 :1;
//    uint8_t Bit7 :1;
//  } Bits;
//} ByteBit;
#define WDTClean()		CLRWDT = 1;
#define CLRWDT()			CLRWDT = 1;
/*---------------------------------------------------------------*/
/*
														Modle.TM52F1376(QFN28)
								 _________________________  __________________________
				LED2 <-- 1|P1.7/AD12                     		       AD10/P1.6|28 --> LED1
				LED3 <-- 2|P0.5/AD1            	 	                  AD9/P1.5|27 <--> NC
				LED4 <-- 3|P0.4           				                  AD6/P1.2|26 <-- DONE
		LED_COM3 <-- 4|P0.3/AD22/LED3                	          AD5/P1.1|25 <-- FULL
				 GND <-- 5|VSS            			                   LED4/P3.5|24 --> LED_COM4
		LED_COM2 <-- 6|P0.2/AD21/LED2                          LED5/P3.6|23 --> LED_COM5
				 VB+ --> 7|VCC                                LED6/RSTn/P3.7|22 --> LED_COM6
		EN_CHARG <-- 8|P2.2/AD13                                AD3/P2.1|21 --> LED_COM7
				PWM2 <-- 9|P2.3/AD14                           LED8/AD2/P2.0|20 --> LED_COM8
			 PWM1 <-- 10|P2.4/AD15               	     PSDA/LED1/AD20/P0.1|19 --> PSDA/CC1A
				MIC --> 11|P2.5/AD16               	     PSCL/LED0/AD19/P0.0|18 --> PSCL/CC2A
		 DC5VIN --> 12|P3.0/SCL               	               INT1/P3.3|17 --> LED1
				KEY --> 13|P3.1/SDA               	               INT0/P3.2|16 <--> NC
	 ADC_CHK2 --> 14|P0.6/AD17               	               AD18/P0.7|15 <-- ADC_CHK1
								 _________________________  __________________________
*/ //  
/*---------------------------------------------------------------*/
union SysStatusFlag{
	struct {
		unsigned	bit0  	: 1;	
		unsigned	bit1	: 1;		
		unsigned	bit2    : 1;
		unsigned 	bit3	: 1;		
		unsigned	bit4	: 1;	
		unsigned	bit5	: 1;	
		unsigned	bit6	: 1;
		unsigned	bit7  	: 1;	 		
	}bits;
	unsigned char AllBits;
};
/*-----------------------------------------------------------*/
//-----------------------------------------------------
//typedef struct
//{
//    unsigned char dataTimeBase;     //Inc 100uS
//    unsigned char Time10mSCnt; //Inc 100uS
//    unsigned char Time100mSCnt; //Inc 10mS

//    unsigned char SmokeTime;     //Inc 100mS
//    unsigned char PuffTime;      //Inc 100mS
//    unsigned int TimeDelaymS;   //Inc 10mS
//} Time_TypeDef;

/*-----------------------------------------------------------*/
//连续4个bit配置一个IO口
#define		PIN_L_MODE_OD 	  	        0x01    //开漏
#define		PIN_L_MODE_OD_IPU	          0x00    //开漏带上拉
#define		PIN_L_MODE_OD_IPD	          0x04    //开漏带下拉

#define		PIN_L_MODE_PP		            0x06    //推挽输出
#define		PIN_L_MODE_ADC		          0x03    //ADC
#define		PIN_L_MODE_LED		          0x07    //LED
#define		PIN_L_MODE_AF 		          0x0B    //PWM TxO CKO
#define		PIN_L_MODE_COM		          0x0F    //LCD 1/2BIAS

#define		PIN_L_MODE_OD_WAKEUP 	  	  0x09    //开漏+唤醒
#define		PIN_L_MODE_OD_IPU_WAKEUP	  0x08    //开漏带上拉+唤醒
#define		PIN_L_MODE_OD_IPD_WAKEUP	  0x0C    //开漏带下拉+唤醒

#define		PIN_H_MODE_OD 		          0x10    //开漏
#define		PIN_H_MODE_OD_IPU	          0x00    //开漏带上拉
#define		PIN_H_MODE_OD_IPD	          0x40    //开漏带下拉

#define		PIN_H_MODE_PP		  	      0x60    //推挽输出
#define		PIN_H_MODE_ADC		          0x30    //ADC
#define		PIN_H_MODE_LED		          0x70    //LED
#define		PIN_H_MODE_AF 		          0xB0    //PWM TxO CKO
#define		PIN_H_MODE_COM		          0xF0    //LCD 1/2BIAS

#define		PIN_H_MODE_OD_WAKEUP 		    0x90    //开漏+唤醒
#define		PIN_H_MODE_OD_IPU_WAKEUP	  0x80    //开漏带上拉+唤醒
#define		PIN_H_MODE_OD_IPD_WAKEUP	  0xC0    //开漏带下拉+唤醒




#define SET_REG_BITS(reg,regbit,value) ((reg) = (reg)&~(reg##_##regbit##_##MASK) | ((value) << (reg##_##regbit##_##POS)))               //设置多位寄存器


#define	CLEAR_REG_BITS(reg,regbit) ((reg) = (reg)&~(reg##_##regbit##_##MASK))                                                           //清除寄存器当前状态

#define SET_REG(reg,value)	((reg) = (value))                                                                                           //设置一位寄存器
#define GET_REG(reg)		(reg)

///***********************************************************************************************************************
EXT_G void Udelay_10us(void);
EXT_G void Delay_Nx10us(unsigned int j);

EXT_G void PortInit(void);
///***********************************************************************************************************************

//* Description  : User_SysStatus_Define

//***********************************************************************************************************************/
///***********************************************************************************************************************
//* Description  : User_SysLowPower_Define
//***********************************************************************************************************************/
/*-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*/
#define FRC_HZ				18432000
#define FRC_DIV				2
#define CLK_US              200                     //100us
#define TIME_RELOAD        (unsigned int)(65536-(((FRC_HZ/FRC_DIV)/2/1000)*CLK_US/1000))   //精度更高
/*---------------------------------------------------------------*/
/*--------------------------------------------------------------*/
#define MainStandby					0
#define MainPowerOn					1
#define MainSmoke						2
#define MainWarning					3
#define MainCharge					4
#define MainOffCharge				5
#define MainSleep						6
#define MainTurnOff					7
#define MainPreHeat        	8 
#define MainScreenOn     		9
#define MainTurnOn					10
#define MainDebug		     		0xFF
/*----------------------------------------------*/
/*--------------------------------------------------------------*/

extern	uint16_t data  Ref1V2;

/*--------------------------------------------------------------*/
extern	ByteBit data	  		SysInfoFlag;
#define bSysOn					SysInfoFlag.Bits.Bit0
#define bHeat					SysInfoFlag.Bits.Bit1
#define ClrHeat				bHeat = 0
#define SetHeat				bHeat = 1

/*--------------------------------------------------------------*/
extern	ByteBit data    	TimeFlag;
#define bTime10mS				TimeFlag.Bits.Bit0

#define bTime100mS			TimeFlag.Bits.Bit1
#define SetTime100mS		bTime100mS = 1
#define ClrTime100mS		bTime100mS = 0
#define bTimeBat				TimeFlag.Bits.Bit2

/*--------------------------------------------------------------*/
extern	ByteBit 	data  	LoadInfoFlag;
#define bLoadNC			LoadInfoFlag.Bits.Bit0
#define SetLoadNC		bLoadNC = 1
#define ClrLoadNC		bLoadNC = 0
#define bLoadSC			LoadInfoFlag.Bits.Bit1
#define SetLoadSC		bLoadSC = 1
#define ClrLoadSC		bLoadSC = 0

#define bLoad2NC			LoadInfoFlag.Bits.Bit2
#define SetLoad2NC		bLoad2NC = 1
#define ClrLoad2NC		bLoad2NC = 0
#define bLoad2SC			LoadInfoFlag.Bits.Bit3
#define SetLoad2SC		bLoad2SC = 1
#define ClrLoad2SC		bLoad2SC = 0

/*--------------------------------------------------------------*/
extern	uint8_t data  MainState,StateStep;
extern	uint8_t data  OilPercent,OilLevel;
extern	uint8_t data  FlagSmoke0,FlagSmoke1;
extern	uint16_t data SmokeTimeCnt;
extern	uint16_t data SmokeTimeCnt1;
extern	uint16_t data SmokeTimeCnt2;
extern	uint32_t data StoreFlag;

//extern	Time_TypeDef  data 	TimeCnt;
extern	uint8_t  data  dataTimeBase;     //Inc 100uS
extern	uint8_t  data  Time10mSCnt; //Inc 100uS
extern	uint8_t  data  Time100mSCnt; //Inc 10mS

extern	uint8_t  data  PuffTime;      //Inc 100mS
extern	uint16_t data  TimeDelaymS;   //Inc 10mS
extern	uint16_t data  SmokeTime;     //Inc 100mS
extern	uint16_t data  DelayState;

/*--------------------------------------------------------------*/
extern	void UserAppInitialize(void);
/*--------------------------------------------------------------*/

#endif

