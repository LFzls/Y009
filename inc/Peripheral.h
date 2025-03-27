
#ifndef _Peripheral_H
#define _Peripheral_H
/*----------------------------------------------------------------------------*/
#include "inc/Global.h"
/*-------------------------------------------------------------------------*
/**************************************************      功能脚位      *************************************************************/
//PIN7:VCC:VB+
//PIN14:P0.6/AD17:PWM2
#define	PIN_PWM2					P0_6  //PWM2
#define	PORT_PWM2					0
#define PWM2_HIGH				PIN_PWM2 = 1;bMos2On=0
#define PWM2_LOW				PIN_PWM2 = 0;bMos2On=1
#define Pwm2High				PWM2_HIGH
#define Pwm2Low					PWM2_LOW
#define Output2On				PWM2_LOW
#define Output2Off				PWM2_HIGH
//PIN9:P2.3/AD14:PWM1
#define	PIN_PWM 					P2_3	//PWM1
#define	PORT_PWM					2
#define PWM_HIGH				PIN_PWM = 1;bMosOn=0
#define PWM_LOW					PIN_PWM = 0;bMosOn=1
#define PwmHigh					PWM_HIGH
#define PwmLow					PWM_LOW
#define OutputOn				PWM_LOW
#define OutputOff				PWM_HIGH
//PIN10:P2.4/AD15:ADC_CHK2
#define PIN_LOAD2					P2_5	//ADC2
#define PORT_LOAD2					2
#define Load2IOInput			PIN_LOAD2=1;PORTIDX =PORT_LOAD2; PINMOD54 = (PINMOD54 & 0x0f) | PIN_L_MODE_OD_IPU	//GPIO PULL-UP
#define Load2ADInput			PORTIDX =PORT_LOAD2; PINMOD54 = (PINMOD54 & 0x0f) | PIN_L_MODE_ADC			//ADC
#define	Load2UPEn				PIN_LOAD2=1;PORTIDX =PORT_LOAD2; PINMOD54 = (PINMOD54 & 0x0f) | PIN_L_MODE_OD_IPU	//GPIO PULL-UP
#define	Load2UPDis				PIN_LOAD2=1;PORTIDX =PORT_LOAD2; PINMOD54 = (PINMOD54 & 0x0f) | PIN_L_MODE_OD	//GPIO PULL-UP
#define LOAD2_TRUE				PIN_LOAD2 == 0
#define LOAD2_FALSE				PIN_LOAD2 == 1
#define AD_Vol2Channel			ADCHS_AD16
//PIN11:P2.5/AD16:ADC_CHK
#define PIN_LOAD					P2_4	//ADC1
#define PORT_LOAD					2
#define LoadIOInput				PIN_LOAD=1;PORTIDX =PORT_LOAD; PINMOD54 = (PINMOD54 & 0xf0)| PIN_H_MODE_OD_IPU	//GPIO PULL-UP
#define LoadADInput				PORTIDX =PORT_LOAD; PINMOD54 = (PINMOD54 & 0xf0) | PIN_H_MODE_ADC			//ADC
#define	LoadUPEn				PIN_LOAD=1;PORTIDX =PORT_LOAD; PINMOD54 = (PINMOD54 & 0xf0) | PIN_H_MODE_OD_IPU	//GPIO PULL-UP
#define	LoadUPDis				PIN_LOAD=1;PORTIDX =PORT_LOAD; PINMOD54 = (PINMOD54 & 0xf0) | PIN_H_MODE_OD	//GPIO PULL-UP
#define LOAD_TRUE				PIN_LOAD == 0
#define LOAD_FALSE				PIN_LOAD == 1
#define AD_VolChannel			ADCHS_AD15

//PIN12:P3.0:KEY
// #define PIN_KEY						P3_0	//KEY
// #define PORT_KEY					3
// #define KEY_TRUE				PIN_KEY == 0
// #define KEY_FALSE				PIN_KEY == 1
// #define KEY_INPUT				PORTIDX =PORT_KEY; PINMOD10 = (PINMOD10 & 0xf0) | PIN_L_MODE_OD_IPU	//PULL-UP
	
//PIN13:P3.1:MIC	
#define PIN_MIC						P3_1	//MIC
#define PORT_MIC					3
#define MIC_TRUE				PIN_MIC == 1
#define MIC_FALSE				PIN_MIC == 0
#define MIC_INPUT				PIN_MIC =1;PORTIDX =PORT_MIC; PINMOD10 = (PINMOD10 & 0x0f) | PIN_H_MODE_OD_IPD	//PULL-DOWN
//PIN8:P22/AD13:USB_IN	
#define PIN_USB						P2_2  //DC5VIN   0:充满； 1/11Vcc:充电中； Vcc:未接入
#define PORT_USB					2
#define USB_TRUE				PIN_USB == 0
#define USB_FALSE				PIN_USB == 1
#define USB_INPUT				PIN_USB =1;PORTIDX =PORT_USB; PINMOD32 = (PINMOD32 & 0xF0) | PIN_L_MODE_OD
#define USBIOInput				PIN_USB =1;PORTIDX =PORT_USB; PINMOD32 = (PINMOD32 & 0xf0) | PIN_L_MODE_OD
#define USBADInput				PORTIDX =PORT_USB; PINMOD32 = (PINMOD32 & 0xf0) | PIN_L_MODE_ADC			//ADC
#define AD_UsbChannel			ADCHS_AD13

//PIN16:P32:CHRG_CTRL
#define	PIN_CHRG_CTRL				P3_2   //En_CHGR
#define	PORT_CHRG_CTRL		        3
#define CHRG_ENABLE				PIN_CHRG_CTRL = 0    //这里是不是要设置0？
#define CHRG_DISABLE			PIN_CHRG_CTRL = 1
#define CHRG_HR			 		PIN_CHRG_CTRL = 1;PORTIDX=PORT_CHRG_CTRL;PINMOD32 = (PINMOD32 & 0xF0) | PIN_L_MODE_OD

//PIN28:P16/AD10:SWITCH
#define  SW_IN_PIN              P1_6
#define  PORT_SW								1
#define  SwInIO                 SW_IN_PIN = 1;PORTIDX =PORT_SW;PINMOD76 = (PINMOD76 & 0xF0) | PIN_L_MODE_OD_WAKEUP
#define  SW_TRUE                SW_IN_PIN == 0
#define  SW_FALSE               SW_IN_PIN == 1
#define  SwInAD                 PORTIDX =PORT_SW;PINMOD76	= (PINMOD76 & 0xF0) | PIN_L_MODE_ADC   
#define	 ADC_CH_SW   	          ADCHS_AD10   //通道10



//PIN18:P00/AD19:PSCL/CC2A
//PIN19:P01/AD20:PSDA/CC2A

/********************************************           LED            ***********************************************************/

//PIN20:P20/AD2:LED_COM1
#define LED_COM1					P2_0    //L1
#define MOD_LED_COM1			PINMOD10
#define PORT_LED_COM1			2		
#define LED_COM1_HIGH			PORTIDX=PORT_LED_COM1;MOD_LED_COM1 = (MOD_LED_COM1 & 0xf0) | PIN_L_MODE_PP  //高位P21不变，改P20的值
#define LED_COM1_LOW			LED_COM1 = 0
//PIN21:P21/AD3:LED_COM2
#define LED_COM2					P2_1	//L2
#define MOD_LED_COM2			PINMOD10
#define PORT_LED_COM2			2	
#define LED_COM2_HIGH			PORTIDX=PORT_LED_COM2;MOD_LED_COM2 = (MOD_LED_COM2 & 0x0f) | PIN_H_MODE_PP
#define LED_COM2_LOW			LED_COM2 = 0
//PIN22:P37/RST:LED_COM3
#define LED_COM3					P3_7	//L3
#define MOD_LED_COM3			PINMOD76
#define PORT_LED_COM3			3	
#define LED_COM3_HIGH			PORTIDX=PORT_LED_COM3;MOD_LED_COM3 = (MOD_LED_COM3 & 0x0f) | PIN_H_MODE_PP
#define LED_COM3_LOW			LED_COM3 = 0
//PIN23:P36:LED_COM4	
#define LED_COM4					P3_6	//L4
#define MOD_LED_COM4			PINMOD76
#define PORT_LED_COM4			3	
#define LED_COM4_HIGH			PORTIDX=PORT_LED_COM4;MOD_LED_COM4 = (MOD_LED_COM4 & 0xf0) | PIN_L_MODE_PP
#define LED_COM4_LOW			LED_COM4 = 0
//PIN24:P35:LED_COM5	
#define LED_COM5					P3_5	//L5
#define MOD_LED_COM5			PINMOD54
#define PORT_LED_COM5			3	  
#define LED_COM5_HIGH			PORTIDX=PORT_LED_COM5;MOD_LED_COM5 = (MOD_LED_COM5 & 0x0f) | PIN_H_MODE_PP
#define LED_COM5_LOW			LED_COM5 = 0
//PIN6:P0.2/AD21/LED2:LED_COM6
#define LED_COM6					P1_1	//L6
#define MOD_LED_COM6			PINMOD10
#define PORT_LED_COM6			1	
#define LED_COM6_HIGH			PORTIDX=PORT_LED_COM6;MOD_LED_COM6 = (MOD_LED_COM6 & 0x0f) | PIN_H_MODE_PP
#define LED_COM6_LOW			LED_COM6 = 0

#define LED_COM7					P1_7   //L7
#define MOD_LED_COM7			PINMOD76
#define PORT_LED_COM7			1
#define LED_COM7_HIGH			PORTIDX=PORT_LED_COM7;MOD_LED_COM7 = (MOD_LED_COM7 & 0x0f) | PIN_H_MODE_PP
#define LED_COM7_LOW			LED_COM7 = 0
//PIN5:VSS:GND

#define	Led1Pin						P0_3    //N1
#define Led1On						Led1Pin = 0
#define Led1Off						Led1Pin = 1
#define LED_GP1_ON				Led1On
#define LED_GP1_OFF				Led1Off
 
#define	Led2Pin						P0_4     //N2
#define Led2On						Led2Pin = 0
#define Led2Off						Led2Pin = 1
#define LED_GP2_ON				Led2On
#define LED_GP2_OFF				Led2Off

#define	Led3Pin						P0_5    //N3
#define Led3On						Led3Pin = 0
#define Led3Off						Led3Pin = 1
#define LED_GP3_ON				Led3On
#define LED_GP3_OFF				Led3Off

#define	Led4Pin						P0_2    //CON1   连接MOS，高电平点亮
#define Led4On						Led4Pin = 1
#define Led4Off						Led4Pin = 0
#define LED_GP4_ON				Led4On
#define LED_GP4_OFF				Led4Off

//#define AD_UsbChannel			AIN1_Channel
#define AD_1V2					0x0B//ADCHS_VBG	//ADC_CHANNEL_VREFINT
/*-----------------------------------------------------------*/

/*--------------------------------------------------------------*/
extern	void Lvd_Initialize(void);
extern	void PwmInitialize(void);
extern	void PortInitialize(void);
extern	void Timer0_Init(void);
extern	void WDG_Init(void);
extern	void DelayNuS(unsigned int cnt);
/*--------------------------------------------------------------*/
#define SwAdValue0          150
#define SwAdValue1          500
#define SwAdValue2          3800
#endif

