/*--------------------------------------------------------------*/
#ifndef _APPCONFIG_H
#define _APPCONFIG_H
/*--------------------------------------------------------------*/
#include "Global.h"
/*--------------------------------------------------------------*/
#define DebugForT						0	//0=false,1=truth  ���Կ���

#define TwoLoadForT					    1	//0=false,1=truth   ˫���������
#define	WorkCwCv						0	//0=CW,1=CV         0���㹦�� 1����ѹ
#define UsbAdorIO							0	//0=IO,1=AD         USB���
#define ChargeSAdorIO				    0	//0=IO,1=AD         ����ź�
#define PreHeatForT					    0	//0=false,1=truth   Ԥ��0����Ԥ�ȣ�1������Ԥ��

#define LoadNcOutputEn			        0	//0=dis,1=en        �����������
#define OilPercentForT			        1	//0=false,1=truth   �����ٷֱ�
#define OilLevelForT				    0	//0=false,1=truth   ��������

#define KeyTorF							0	//0=f.alse,1=truth   ����
#define TKeyForT						0	//0=false,1=truth   ��������
#define KeyOnOffForT				    0	//0=false,1=truth   �������ػ�
#define KeyCountForT				    1	//0=false,1=truth   ���ؼ�����

#define LedForT							1	//0=false,1=truth   ����led����   N1 N2 N3 CON1��LED������ɨ��
#define LedBreatheForT			        1	//0=false,1=truth   ������

#define LedPForT						1	//0=false,1=truth   led��
#define LedPBBitForT				    1	//0=false,1=truth   ��λ����
#define LedPComN						7	//led panel com number  ledɨ��com��

#define FlashForT						0	//0=false,1=truth  flash
#define SwitchTorF					    1	//0=false,1=truth   ��������
#define SwitchIOorAD    			    1	//0=IO,1=AD
/*--------------------------------------------------------------*/
#define PwmDutyMin				51	//31
#define PwmDutyMax				99
	
#define ResistorMax				9000ul
#define ResistorMin				650//500ul
	
#define	SmokeTimeMax			10*100	//n * 0.01S   //��ʱ10s
#define	PreheatTime 	  		6*100	//n * 0.01S     //Ԥ��6s
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
#define LoadRSCAdValue			3960   //0.5��   //0.3:3933,0.5:4022
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
