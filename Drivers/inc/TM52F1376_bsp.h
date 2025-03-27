#ifndef __HTX3736Z_BSP_H__
#define __HTX3736Z_BSP_H__

#include "TM52F1376_sfr_config.h"

#define Delay_10nop() \
	do{												\
		_nop_();_nop_();_nop_();_nop_();_nop_();	 \
		_nop_();_nop_();_nop_();_nop_();_nop_();	\
	}while(0)

void Bsp_delay_ms(unsigned int ms);
void Bsp_delay_100us(unsigned int cnt); 
void Bsp_FastClock_Init(SysClk_Prescaler_TypeDef div);	
 
#endif
