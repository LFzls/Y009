/**
******************************************************************************
* @file    sleep.h
* @brief   sleep Head File.
*
* @version V1.0.0
* @author  lishuilan
* @date    2021/09/02
*
* Copyright (C) Hitenx (Wuxi) Technology Co., Ltd
******************************************************************************
*/

#ifndef __SLEEP_H__
#define __SLEEP_H__

#define  PowerDown_None   0x00
#define  PowerDown_IDLE   0x01
#define  PowerDown_Stop   0x02

void PowerDownMode_Enable(unsigned char val); 
void PowerDown_Config(unsigned char mode);
 
#endif
