/**
******************************************************************************
* @file    sleep.c
* @brief   sleep Source File.
*
* @version V1.0.0
* @author  lishuilan
* @date    2021/08/09
*
* Copyright (C) Hitenx (Wuxi) Technology Co., Ltd
******************************************************************************
*/
#include "REGtenxTM52F1376.h"
#include "TM52F1376_bsp.h"
#include <intrins.h>
#include "sleep.h"

/*-------------------------------------------------------------------------------------------------------
  val:
	   0x00->disable
		 0x01->IDLE
		 0x02->Stop)
 -------------------------------------------------------------------------------------------------------*/
void PowerDownMode_Enable(unsigned char val) 
{
	PCON=(PCON & ~0x03)|val;  
}

/*-------------------------------------------------------------------------------------------------------
  mode:
			PowerDown_None   0x00
			PowerDown_IDLE   0x01
			PowerDown_Stop   0x02
  -------------------------------------------------------------------------------------------------------*/
void PowerDown_Config(unsigned char mode)
{
	switch(mode)
	{
		case PowerDown_IDLE:
			                 PDOWN_LVD_DISABLE;	     // 0x00->enable,0x20->disable for reduce the chip¡¯s power consumption at Idle Mode.
											 STPPCK = 1;     				 // stop UART/Timer0/Timer1/Timer2/ADC clock in Idle mode for current reducing.
											 SELFCK = 0;     				 // select Slow clock
											 Bsp_delay_100us(2);
											 STPFCK = 1;     				 // stop Fast clock for power saving in Slow/Idle mode
											 break;
												 
		case PowerDown_Stop:
			                 PDOWN_LVD_DISABLE;	     // 0x00->enable,0x20->disable for reduce the chip¡¯s power consumption at Stop Mode.
		                   SELFCK = 0;
		                   break;
		case PowerDown_None:
		default            :
			                 STPFCK = 0;             // enable Fast clock for power saving in Slow/Idle mode
											 PDOWN_LVD_ENABLE;	     // 0x00->enable,0x20->disable for reduce the chip¡¯s power consumption at Idle and Stop Mode.
											 STPPCK = 0;					   // enable UART/Timer0/Timer1/Timer2/ADC clock 
											 SELFCK = 1;             // select Fast clock
											 Bsp_delay_100us(2);	 
			                 break;			           			
	}
}
