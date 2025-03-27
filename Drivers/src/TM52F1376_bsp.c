/**
******************************************************************************
* @file    HTX3736_bsp.c
* @brief   HTX3736_bsp Source File.
*
* @version V1.0.0
* @author  Hitenx Software Team
* @date    2021/04/13
*
* Copyright (C) Hitenx (Wuxi) Technology Co., Ltd
******************************************************************************
*/

#include "REGtenxTM52F1376.h"
#include "TM52F1376_bsp.h"
#include <intrins.h>

void Bsp_delay_100us(unsigned int cnt)
{
	unsigned int i;
	unsigned char delay_cnt;
	for(i = 0;i<cnt;i++)
	{
		delay_cnt = 200;
		while(delay_cnt--);
	}
}


void Bsp_delay_ms(unsigned int ms)
{
	unsigned int i;
	unsigned char delay_cnt;
	for(i = 0;i<ms;i++)
	{
		delay_cnt = 250;	 
		while(delay_cnt--);
	}
}

/*-----------------------------------------------------------------
   FRC=18.432Mhz, Div=4, sysClk=4.608Mhz
   FRC=18.432Mhz, Div=16,sysClk=1.152Mhz
  -----------------------------------------------------------------*/
void Bsp_FastClock_Init(SysClk_Prescaler_TypeDef div)
{
	  SELFCK = 0;	     //切换到慢时钟	   
	
	  CLKCON=(CLKCON&(~CLKCON_MASK))|div;
	
	  Delay_10nop();
		STPPCK = 0;			 //开启快时钟
		Delay_10nop();
		STPFCK = 0;			 //开启部分模块使用快时钟
		Delay_10nop();
		SELFCK = 1;			 //切换到快时钟
		Delay_10nop(); 
}
