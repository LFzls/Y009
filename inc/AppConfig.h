/*--------------------------------------------------------------*/
#ifndef _APPCONFIG_H
#define _APPCONFIG_H
/*--------------------------------------------------------------*/
#include "Global.h"
/*--------------------------------------------------------------*/
#define DebugForT						0	//0=false,1=truth  调试开关

#define TwoLoadForT					    1	//0=false,1=truth   双发输出开关
#define	WorkCwCv						0	//0=CW,1=CV         0：恒功率 1：恒压
#define UsbAdorIO							0	//0=IO,1=AD         USB检测
#define ChargeSAdorIO				    0	//0=IO,1=AD         充电信号
#define PreHeatForT					    0	//0=false,1=truth   预热0：带预热；1：不带预热

#define LoadNcOutputEn			        0	//0=dis,1=en        空载输出开关
#define OilPercentForT			        1	//0=false,1=truth   油量百分比
#define OilLevelForT				    0	//0=false,1=truth   油量格数

#define KeyTorF							0	//0=f.alse,1=truth   按键
#define TKeyForT						0	//0=false,1=truth   触摸按键
#define KeyOnOffForT				    0	//0=false,1=truth   按键开关机
#define KeyCountForT				    1	//0=false,1=truth   开关计数器

#define LedForT							1	//0=false,1=truth   单独led开关   N1 N2 N3 CON1做LED，不做扫描
#define LedBreatheForT			        1	//0=false,1=truth   呼吸灯

#define LedPForT						1	//0=false,1=truth   led屏
#define LedPBBitForT				    1	//0=false,1=truth   百位数字
#define LedPComN						7	//led panel com number  led扫描com数

#define FlashForT						0	//0=false,1=truth  flash
#define SwitchTorF					    1	//0=false,1=truth   拨动开关
#define SwitchIOorAD    			    1	//0=IO,1=AD
/*--------------------------------------------------------------*/
#define PwmDutyMin				51	//31
#define PwmDutyMax				99
	
#define ResistorMax				9000ul
#define ResistorMin				650//500ul
	
#define	SmokeTimeMax			10*100	//n * 0.01S   //超时10s
#define	PreheatTime 	  		6*100	//n * 0.01S     //预热6s
#define SmokeTimeTest			30*100	//30S

#define	OilTimeTotal			3050*10		//0.1S   
#define	OilTimeMax				3050*10		//0.1S,ECO
#define	OilTimeMax1				3050*10		//0.1S,NORM
#define	OilTimeMax2				3050*10		//0.1S,MAX
#define OilTimePer				OilTimeTotal/100
#define OilPercentMax			100
#define OilLevelMax				4
/*-------------------------------------------------*/
#define BatPerStep				1	//1=1%,5=5%
#define TimePerPuffMin			40		//3.0S
#define TimePerPuffMax			60		//5.0S
/*-------------------------------------------------*/
//Load resistor value
#define LoadRSCAdValue			3960   //0.5Ω   //0.3:3933,0.5:4022
#define LoadRLowAdValue			LoadRSCAdValue-100

/*-------------------------------------------------*/
//LoadState
#define LoadNC					0
#define LoadSC					1
#define LoadNORM				2

/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*--------------------------------------------------------------*/
#endif
