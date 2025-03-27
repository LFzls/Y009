#ifndef __HTX3736Z_SFR_CONFIG_H__
#define __HTX3736Z_SFR_CONFIG_H__

#define  __IO    volatile             /*!< defines 'read / write' permissions   */

#define P0_MASK					  (0xFF)      //Port 0 Data mask @ addr 0x80
#define P1_MASK					  (0xFF)      //Port 1 Data mask @ addr 0x90
#define P2_MASK					  (0xFF)      //Port 2 Data mask @ addr 0xA0
#define P3_MASK					  (0xFF)      //Port 3 Data mask @ addr 0xB0

/*-------INTPORT @ addr 0x85-------------------------------------------*/  
#define INTPORT_MASK      (0xFF) 		  //Port  Pin Change Interrupt Flag Mask

#define	INTPORT_P3IF_MASK	(0x08)		  //Port3 Pin Change Interrupt Flag Mask
#define	INTPORT_P3IF_POS	(3)

#define	INTPORT_P2IF_MASK	(0x04)		  //Port2 Pin Change Interrupt Flag Mask
#define	INTPORT_P2IF_POS	(2)

#define	INTPORT_P1IF_MASK	(0x02)			//Port1 Pin Change Interrupt Flag Mask
#define	INTPORT_P1IF_POS	(1)

#define	INTPORT_P0IF_MASK	(0x01)		  //Port0 Pin Change Interrupt Flag Mask
#define	INTPORT_P0IF_POS	(0)

/*-------PCOM  @ addr 0x87------------------------------------------*/
#define PCON_MASK         (0xFF)

#define PCON_SMOD_MASK    (0x80)      //1->波特率倍增
#define PCON_SMOD_POS		  (7)

#define PCON_GF1_MASK		  (0x08)      //general Bit for user
#define PCON_GF1_POS		  (3)

#define PCON_GF0_MASK		  (0x04)      //general Bit for user
#define PCON_GF0_POS		  (2)

#define PCON_PD_MASK      (0x02)      //1->MCU go to STOP mode
#define PCON_PD_POS       (1)

#define PCON_IDL_MASK     (0x01)      //1->MCU go to IDL mode
#define PCON_IDL_POS		  (0)

/*--------TCON  @ addr 0x88---------------------------*/
#define TCON_MASK				  (0xFF)

#define TCON_TF1_MASK     (0x80)    // 定时器T1溢出标志
#define TCON_TF1_POS      (7)

#define TCON_TR1_MASK     (0x40)    // T1充许计数控制位,为1时充许T1计数
#define TCON_TR1_POS      (6)

#define TCON_TF0_MASK     (0x20)    // 定时器T0溢出标志
#define TCON_TF0_POS      (5)

#define TCON_TR0_MASK     (0x10)    // T0充许计数控制位,为1时充许T0计数
#define TCON_TR0_POS      (4)

#define TCON_IE1_MASK     (0x08)    // INT1脚  边沿检测标志，不管 EX1=0 or EX1=1
#define TCON_IE1_POS      (3)

#define TCON_IT1_MASK     (0x04)    // INT1脚  0->低电平触发,1->下降沿触发
#define TCON_IT1_POS      (2)

#define TCON_IE0_MASK     (0x02)    // INT0脚  边沿检测标志，不管 EX0=0 or EX0=1
#define TCON_IE0_POS      (1)

#define TCON_IT0_MASK     (0x01)    // INT0脚  0->低电平触发,1->下降沿触发
#define TCON_IT0_POS      (0)

/*--------TMOD  @ addr 0x89----------------------------*/
#define TMOD_MASK				  (0xFF)

#define TMOD_T1GATE_MASK	(0x80)    // 1->INT1脚高电平且TCON中的TR1控制位为1时,计时/计数器1才开始工作
#define TMOD_T1GATE_POS		(7)       // 0->只要将TR1控制位设为1，计时/计数器1就开始工作

#define TMOD_CT1_MASK			(0x40)    // 1->计数器,通过外部引脚T1输入计数脉冲
#define TMOD_CT1_POS			(6)       // 0->定时器,由内部系统时钟提供计时工作脉冲

#define TMOD_T1MOD_MASK		(0x30)    // 00->T1为13位计时/计数器,         01->T1为16位计时/计数器
#define TMOD_T1MOD_POS		(4)       // 10->T1为8位自动加载计数/计时器 ,11->timer stop

#define TMOD_T0GATE_MASK	(0x08)    // 1->INT0脚为高电平且TCON中的TR0控制位为1时,计时/计数器0才开始工作
#define TMOD_T0GATE_POS		(3)       // 0->只要将TR0控制位设为1，计时/计数器0就开始工作

#define TMOD_CT0_MASK		  (0x04)    // 1->计数器,通过外部引脚T0输入计数脉冲
#define TMOD_CT0_POS			(2)       // 0->定时器,由内部系统时钟提供计时工作脉冲

#define TMOD_T0MOD_MASK		(0x03)    // 00->T0为13位计时/计数器,         01->T0为16位计时/计数器
#define TMOD_T0MOD_POS		(0)       // 10->T0为8位自动加载计数/计时器 ,11->仅适用于T0,T0分为两个独立的8位定时器/计数器TH0及TL0,在此模式下T1停止工作

/*----Timer0 Data high byte & low byte-----------------------------------*/
#define TL0_MASK				  (0xFF)    // Timer0 Data low  byte @ addr 0x8A
#define TH0_MASK				  (0xFF)    // Timer0 Data high byte @ addr 0x8C

/*----Timer1 Data high byte & low byte-----------------------------------*/
#define TL1_MASK				  (0xFF)    // Timer1 Data low  byte @ addr 0x8B
#define TH1_MASK				  (0xFF)    // Timer1 Data high byte @ addr 0x8D

/*----------------SCON2 @ addr 0x8E--------------------------------------*/
#define SCON2_MASK		  	(0xFF)

#define SCON2_SM_MASK     (0x80)   // 1->uart2 9bit 
#define SCON2_SM_pos      (7)      // 0->uart2 8bit 

#define SCON2_REN_MASK		(0x10)   // 1->uart2 receive enable
#define SCON2_REN_POS		  (4)      // 0->uart2 receive disable

#define SCON2_TB8_MASK		(0x08)   // uart2 send bit8
#define SCON2_TB8_POS		  (3)

#define SCON2_RB8_MASK		(0x04)   // uart2 receive bit8
#define SCON2_RB8_POS		  (2)

#define SCON2_TI_MASK			(0x02)   // Uart2 Transmit Interrupt flag
#define SCON2_TI_POS		  (1)

#define SCON2_RI_MASK			(0x01)   // Uart2  receive Interrupt flag
#define SCON2_RI_POS			(0)

/*----SCON @ addr 0x98--------------------------------------------*/
#define SCON_MASK			  	(0xFF)

#define SCON_SM01_MASK    (0xC0) //串口模式,SM0->Bit[0],SM1->Bit[1]
#define SCON_SM01_POS     (6)

#define SCON_SM2_MASK			(0x20) // 1->只有当接收到第9位数据(RB8)为1时,才把接收到的前8位数据送入SBUF,且置位RI发出中断申请,否则会将接收到的数据放弃
#define SCON_SM2_POS		  (5)    // 0->不管第9位数据是0还是1,都得将数据送入SBUF,并发出中断申请,工作于方式0时，SM2必须为0

#define SCON_REN_MASK			(0x10) //REN用于控制数据接收的允许和禁止,REN=1时,允许接收,REN=0时,禁止接收 
#define SCON_REN_POS		  (4)

#define SCON_TB8_MASK			(0x08) //发送数据第8位
#define SCON_TB8_POS		  (3)

#define SCON_RB8_MASK			(0x04) //接收数据第8位
#define SCON_RB8_POS		  (2)

#define SCON_TI_MASK			(0x02) //发送中断标志位,方式0时,发送完第8位数据后,由硬件置位 
#define SCON_TI_POS			  (1)    //其它方式下,由硬件置位,TI=1表示帧发送结束,TI可由软件清零

#define SCON_RI_MASK			(0x01) //接收中断标志位,方式0时,接收完第8位数据后,由硬件置位,
#define SCON_RI_POS			  (0)    //其它方式下,由硬件置位,RI=1表示帧接收完成

/*-----------PORTIDX @ addr 0x91--------------------------------------------------------------*/
#define PORTIDX_MASK			(0x03) //Bit[1:0]->Pin Mode Index 
#define PORTIDX_POS			  (0)    //00~11->Port0~Port3 select,others->Reserved

/*-----------OPTION @ addr 0x94---------------------------------------------------------------*/
#define OPTION_MASK				  (0xFF)

#define OPTION_TM3CKS_MASK	(0x40)  //Timer3 Clock Source Select. 0: SLOW ( SXT(32.768KHz) / SRC(140KHz) ), 1: FRC/512 (36KHz)
#define OPTION_TM3CKS_POS		(6)

#define OPTION_WDTPSC_MASK	(0x30)  //WDT Prescale
#define OPTION_WDTPSC_POS		(4)

#define OPTION_ADCKS_MASK		(0x0C)  //ADC Clock Rate Mask
#define OPTION_ADCKS_POS		(2) 

/*-----------INTFLG @ addr 0x95------------------------------------------------------------------*/
#define INTFLG_MASK				  (0xFF)

#define INTFLG_LVDIF_MASK		(0x80)  //Low Voltage Detect Flag, write 0 to clear Interrupt flag 
#define INTFLG_LVDIF_POS		(7)

#define INTFLG_ADIF_MASK		(0x10)  //ADC Interrupt Flag，HW clear while ADSOC set 
#define INTFLG_ADIF_POS			(4)

#define INTFLG_PCIF_MASK		(0x02)  //Pin Change Interrupt Flag (INTVEC=43h) 
#define INTFLG_PXIF_POS			(1)

#define INTFLG_TF3_MASK			(0x01)  //TM3 Interrupt Flag,1=TM3 Interrupt
#define INTFLG_TF3_POS			(0)

/*-----------INTPIN @ addr 0x96--------------------------------------------------------------------*/
#define INTPIN_MASK				  (0xFF)

#define INTPIN_Px7IF_MASK		(0x80)  //Px.7 Change Interrupt Flag,x define by PINIDX,write 0 to clear INT flag
#define INTPIN_Px7IF_POS		(7)

#define INTPIN_Px6IF_MASK		(0x40)  //Px.6 Change Interrupt Flag,x define by PINIDX,write 0 to clear INT flag
#define INTPIN_Px6IF_POS		(6)

#define INTPIN_Px5IF_MASK		(0x20)  //Px.5 Change Interrupt Flag,x define by PINIDX,write 0 to clear INT flag
#define INTPIN_Px5IF_POS		(5)

#define INTPIN_Px4IF_MASK		(0x10)  //Px.4 Change Interrupt Flag,x define by PINIDX,write 0 to clear INT flag
#define INTPIN_Px4IF_POS		(4)

#define INTPIN_Px3IF_MASK		(0x08)  //Px.3 Change Interrupt Flag,x define by PINIDX,write 0 to clear INT flag
#define INTPIN_Px3IF_POS		(3)

#define INTPIN_Px2IF_MASK		(0x04)  //Px.2 Change Interrupt Flag,x define by PINIDX,write 0 to clear INT flag
#define INTPIN_Px2IF_POS		(2)

#define INTPIN_Px1IF_MASK		(0x02)  //Px.1 Change Interrupt Flag,x define by PINIDX,write 0 to clear INT flag
#define INTPIN_Px1IF_POS		(1)

#define INTPIN_Px0IF_MASK		(0x01)  //Px.0 Change Interrupt Flag,x define by PINIDX,write 0 to clear INT flag
#define INTPIN_Px0IF_POS		(0)

/*-----------SFR SWCMD  @addr 0x97--------------------------------------------------------*/
#define SWCMD_MASK			 	  (0xFF)    // Write 56H for generate SW Reset
                                      // Write 65H for enable IAP all area
																			// Write other value for disable IAP all
																			
#define SWCMD_WDTO_MASK		  (0x02)    // Only Read,watchdog time-out flag
#define SWCMD_WDTO_POS		  (1)

#define SWCMD_IAPALL_MASK		(0x01)    // Only Read,IAP enable control
#define SWCMD_IAPALL_POS		(0)

/*------------SFR IAPWE_SFR   @Addr 0xC9----------------------------------------------------------*/
#define IAPWE_SFR_MASK			(0xFF) 	  //Write 47H to this Register for enable main ROM IAP write
							                        //Write E2H to this Register for enable EEPROM       write
																		  //Write other value to this Register for disable IAP write
	
#define	IAPWE_MASK		  		(0x80)	   //Read,IAPWE Enable Flag															
#define	IAPWE_POS		    		(7)

#define	IAPTO_MASK		  		(0x40)	   //IAP Time-Out flag, H/W Auto clear when IAPWE =0
#define	IAPTO_POS		    		(6)

#define	EEPWE_MASK		  		(0x20)	   //EEPWE Enable Flag
#define	EEPWE_POS		    		(5)

/*-----------PINMOD10 @addr 0xA2----------------------------------------*/
#define PINMOD10_MASK				   (0xFF)

#define PINMOD10_PINMOD1_MASK	 (0xF0)  //Px.1 Pin Control, x define by PINIDX
#define PINMOD10_PINMOD1_POS	 (4)

#define PINMOD10_PINMOD0_MASK	 (0x0F)  //Px.0 Pin Control, x define by PINIDX
#define PINMOD10_PINMOD0_POS	 (0)

/*-----------PINMOD32 @addr 0xA3----------------------------------------*/
#define PINMOD32_MASK				   (0xFF)  

#define PINMOD32_PINMOD3_MASK	 (0xF0)  //Px.3 Pin Control, x define by PINIDX 
#define PINMOD32_PINMOD3_POS	 (4)

#define PINMOD32_PINMOD2_MASK	 (0x0F)  //Px.2 Pin Control, x define by PINIDX
#define PINMOD32_PINMOD2_POS	 (0)

/*-----------PINMOD54 @addr 0xA4----------------------------------------*/
#define PINMOD54_MASK				   (0xFF)

#define PINMOD54_PINMOD5_MASK	 (0xF0)  //Px.5 Pin Control, x define by PINIDX
#define PINMOD54_PINMOD5_POS	 (4)

#define PINMOD54_PINMOD4_MASK	 (0x0F)  //Px.4 Pin Control, x define by PINIDX
#define PINMOD54_PINMOD4_POS	 (0)

/*-----------PINMOD76 @addr 0xA5----------------------------------------*/
#define PINMOD76_MASK				   (0xFF)

#define PINMOD76_PINMOD7_MASK	 (0xF0)  //Px.7 Pin Control, x define by PINIDX
#define PINMOD76_PINMOD7_POS	 (4)

#define PINMOD76_PINMOD6_MASK	 (0x0F)  //Px.6 Pin Control, x define by PINIDX
#define PINMOD76_PINMOD6_POS	 (0)

/*-----------PINMOD @addr 0xA6----------------------------------------*/
#define PINMOD_MASK        		 (0xFF)

#define PINMOD_HSNK2EN_MASK  	 (0x80) // Pin H-sink enable (Group 2 = P06, P07, P22~P25, P30~P33)
#define PINMOD_HSNK2EN_POS   	 (7)    // 0->Group 2 H-sink disable,1->Group 2 H-sink enable

#define PINMOD_HSNK1EN_MASK  	 (0x40) // Pin H-sink enable (Group 1 = P04, P05, P10~P17)
#define PINMOD_HSNK1EN_POS     (6)    // 0->Group 1 H-sink disable,1->Group 1 H-sink enable

#define PINMOD_HSNK0EN_MASK  	 (0x20) // Pin H-sink enable  (Group 0 = P00~P03, P20, P21, P34~P37)
#define PINMOD_HSNK0EN_POS     (5)    // 0->Group 0 H-sink disable,1->Group 0 H-sink enable

#define PINMOD_IICPS_MASK  		 (0x10) // IIC Pin Select,
#define PINMOD_IICPS_POS    	 (4)    // 0->SCL/SDA = P0.0/P0.1,1->SCL/SDA = P3.0/P3.1	

#define	PINMOD_UART2PS_MASK    (0x0C) // PINMOD Bit[3:2],UART2 Pin Select
#define PINMOD_UART2PS_POS     (2)	  // 00: RXD2/TXD2 = P0.0/P0.1,
																			// 01: RXD2/TXD2 = P3.5/P3.6
																			// 10: RXD2/TXD2 = P0.1/P0.0
																			// 11: RXD2/TXD2 = P3.6/P3.5							
	
#define	PINMOD_UART1PS_MASK    (0x03) // PINMOD Bit[1:0],UART1 Pin Select
#define	PINMOD_UART1PS_POS     (0)	  // 00: RXD/TXD = P3.0/P3.1
																			// 01: RXD/TXD = P3.2/P3.3
																			// 10: RXD/TXD = P3.1/P3.0
																			// 11: RXD/TXD = P3.3/P3.2
 
/*-----------IE @addr 0xA8----------------------------------------*/
#define IE_MASK					 (0xFF)

#define IE_EA_MASK			 (0x80)  //EA=0时,所有中断禁止;EA=1时,各中断的产生由个别的允许位决定
#define IE_EA_POS        (7)

#define IE_ET2_MASK		   (0x20)  //定时2中断允许
#define IE_ET2_POS       (5)

#define IE_ES_MASK		   (0x10)  //串行口中断充许(ES=1充许,ES=0禁止)
#define IE_ES_POS        (4)

#define IE_ET1_MASK			 (0x08)  //定时1中断充许
#define IE_ET1_POS       (3)

#define IE_EX1_MASK			 (0x04)  //外中断INT1中断充许
#define IE_EX1_POS       (2)

#define IE_ET0_MASK			 (0x02)  //定时器0中断充许
#define IE_ET0_POS       (1)

#define IE_EX0_MASK			 (0x01)  //外部中断INT0的中断允许
#define IE_EX0_POS       (0)

/*-----------INTE1 @addr 0xA9----------------------------------------*/
#define INTE1_MASK       (0xEF)
 
#define	INTE1_PWMIE_MASK (0x80)		//PWM Interrupt Enable 中断允许
#define	INTE1_PWMIE_POS  (7)

#define	INTE1_I2CE_MASK	 (0x40)		//I2C Interrupt Enable 中断允许
#define	INTE1_I2CE_POS   (6)

#define	INTE1_ES2_MASK	 (0x20)		//Uart2 Interrupt Enable 中断允许
#define	INTE1_ES2_POS    (5)

#define	INTE1_ADIE_MASK  (0x08)		//ADC/Touch Key  中断允许
#define	INTE1_ADIE_POS   (3)

#define	INTE1_LVDIE_MASK (0x04)		//LVD 中断允许
#define	INTE1_LVDIE_POS  (2)

#define	INTE1_PCIE_MASK	 (0x02)		//Pin端口中断允许
#define	INTE1_PCIE_POS   (1)

#define	INTE1_TM3IE_MASK (0x01)		//TM3中断允许	
#define	INTE1_TM3IE_POS  (0)

/*-----------IP @ addr 0xB8----------------------------------------*/
#define IP_MASK          (0x3F)

#define IP_PT2_MASK      (0x20)  //定时2中断优先级低位
#define IP_PT2_POS       (5)

#define IP_PS_MASK       (0x10)  //串行口中断优先级低位
#define IP_PS_POS        (4)

#define IP_PT1_MASK    	 (0x08)  //定时1中断优先级低位
#define IP_PT1_POS     	 (3)

#define IP_PX1_MASK    	 (0x04)  //外中断INT1中断优先级低位
#define IP_PX1_POS     	 (2)

#define IP_PT0_MASK    	 (0x02)  //定时0中断优先级低位
#define IP_PT0_POS     	 (1)

#define IP_PX0_MASK    	 (0x01)  //外中断INT0中断优先级低位
#define IP_PX0_POS       (0)

/*-----------IPH @ addr 0xB9----------------------------------------*/
#define IPH_MASK         (0x3F)

#define IPH_PT2H_MASK    (0x20)  //定时2中断优先级高位   
#define IPH_PT2H_POS     (5)

#define IPH_PSH_MASK     (0x10)  //串行口中断优先级高位    
#define IPH_PSH_POS      (4)

#define IPH_PT1H_MASK    (0x08)  //定时1中断优先级高位 
#define IPH_PT1H_POS     (3)

#define IPH_PX1H_MASK    (0x04)  //外中断INT1中断优先级高位 
#define IPH_PX1H_POS     (2)

#define IPH_PT0H_MASK    (0x02)  //定时0中断优先级高位    
#define IPH_PT0H_POS     (1)

#define IPH_PX0H_MASK    (0x01)  //外中断INT0中断优先级高位 
#define IPH_PX0H_POS     (0)

/*-----------IP1 @ addr 0xBA----------------------------------------*/
#define IP1_MASK         (0xFF)

#define IP1_PPWM_MASK    (0x80)  //PWM 中断优先级低位
#define IP1_PPWM_POS     (7)

#define IP1_PI2C_MASK    (0x40)  //I2C 中断优先级低位
#define IP1_PI2C_POS     (6)

#define IP1_PS2_MASK     (0x20)  //UART2中断优先级低位
#define IP1_PS2_POS      (5)

#define IP1_PADI_MASK    (0x08)  //ADC 中断优先级低位
#define IP1_PADI_POS     (3)

#define IP1_PLVD_MASK    (0x04)  //LVD T2中断优先级低位
#define IP1_PLVD_POS     (2)

#define IP1_PPC_MASK     (0x02)  //Pin change中断优先级低位
#define IP1_PPC_POS      (1)

#define IP1_PT3_MASK     (0x01)  //定时3中断优先级低位
#define IP1_PT3_POS      (0)

/*-----------IP1H @ addr 0xBB----------------------------------------*/
#define IP1H_MASK        (0xFF)

#define IP1H_PPWMH_MASK  (0x80)  //PWM 中断优先级高位
#define IP1H_PPWMH_POS   (7)

#define IP1H_PI2CH_MASK  (0x40)  //I2C 中断优先级高位
#define IP1H_PI2CH_POS   (6)

#define IP1H_PS2H_MASK   (0x20)  //UART2中断优先级高位
#define IP1H_PS2H_POS    (5)

#define IP1H_PADIH_MASK  (0x08)  //ADC 中断优先级高位
#define IP1H_PADIH_POS   (3)

#define IP1H_PLVDH_MASK  (0x04)  //LVD T2中断优先级高位
#define IP1H_PLVDH_POS   (2)

#define IP1H_PPCH_MASK   (0x02)  //Pin change中断优先级高位
#define IP1H_PPCH_POS    (1)

#define IP1H_PT3H_MASK   (0x01)  //定时3中断优先级高位
#define IP1H_PT3H_POS    (0)     

/*-----------T2CON @ addr 0xC8-----------------------------------------------------------*/
#define T2CON_MASK       (0xFF)

#define T2CON_TF2_MASK   (0x80)  //timer2 overflow flag,set by H/W when overflows unless RCLK=1 or TCLK=1,must be cleared by S/W.
#define T2CON_TF2_POS    (7) 

#define T2CON_EXF2_MASK  (0x40)  //T2EX Interrupt pin falling edge flag,set when a capture or reload is caused by a negative transition on T2EX pin if EXEN2=1,must be cleared by S/W.
#define T2CON_EXF2_POS   (6) 

#define T2CON_RCLK_MASK  (0x20)  //UART receive clock control Bit, for serial port in mode 1 or 3, 0->timer1 overflow,1->timer2 overflow as receive clock.
#define T2CON_RCLK_POS   (5) 

#define T2CON_TCLK_MASK  (0x10)  //UART transmit clock control Bit for serial port in mode 1 or 3, 0->timer1 overflow,1->timer2 overflow as transmit clock.
#define T2CON_TCLK_POS   (4) 

#define T2CON_EXEN2_MASK (0x08)  //T2EX pin enable,0->T2EX pin disable,1->T2EX pin enable whitch cause a capture or reload when a negative transtion on T2EX pin is detected if RCLK=TCLK=0.
#define T2CON_EXEN2_POS  (3) 

#define T2CON_TR2_MASK   (0x04)  //timer2 run control,0->timer2 stops,1->timer2 runs.
#define T2CON_TR2_POS    (2) 

#define T2CON_CT2N_MASK  (0x02)  //timer2 counter/timer select Bit,0->timer mode that increases at 2 system clock cycle rate,1->counter mode that increases at T2 pin's negative edge.
#define T2CON_CT2N_POS   (1) 

#define T2CON_CPRL2N_MASK (0x01)  //timer2 capture/reload control Bit,0->reload mode that autoreload on timer2 overflow or negative transitions on T2EX pin if EXEN2=1.1->capture mode that capture on negative transition on T2EX pin if EXEN2=1.
#define T2CON_CPRL2N_POS  (0)     //if RCLK=1 or TCLK=1,CPRL2N is ignored and timer is forced to autoreload on timer2 overflow.

/*-----RCP2L @ addr 0xCA,RCP2H @ addr 0xCB--------------------------------------------------------*/
#define RCP2L_MASK				(0xFF)  //外部输入（P1.1）计数器/自动再装入模式时初值寄存器低八位
#define RCP2H_MASK				(0xFF)  //外部输入（P1.1）计数器/自动再装入模式时初值寄存器高八位

/*-----TL2 @ addr 0xCC,TH2 @ addr 0xCD---------------------------------------------------*/
#define TL2_MASK				  (0xFF)  //Timer2 Data low byte
#define TH2_MASK				  (0xFF)  //Timer2 Data high byte

/*-----------PSW @ addr 0xD0--------------------------------------------------------*/
#define PSW_MASK				  (0xFF)   

#define PSW_CY_MASK				(0x80)  //进位标志,有进或借位,CY＝1;无进或借位,CY＝0
#define PSW_CY_POS				(7) 

#define PSW_AC_MASK				(0x40)  //半进位标志
#define PSW_AC_POS				(6) 

#define PSW_F0_MASK				(0x20)  //用户可以随便使用
#define PSW_F0_POS				(5) 

#define PSW_RS1_MASK			(0x10)  //工作寄存器区选择[RS1:RS0]
#define PSW_RS1_POS				(4) 

#define PSW_RS0_MASK			(0x08)  //00--0区,01--1区,10--2区,11--3区
#define PSW_RS0_POS				(3) 

#define PSW_OV_MASK			  (0x04)  //运算结果按补码运算,有溢出,OV=1;无溢出,OV＝0
#define PSW_OV_POS				(2) 

#define PSW_F1_MASK			  (0x02)  //用户自定义标志
#define PSW_F1_POS				(1) 

#define PSW_P_MASK			  (0x01)  //用来表示ALU运算结果中二进制数位1的个数的奇偶性,若为奇数,则P=1,否则为0
#define PSW_P_POS				  (0) 

/*-----------CLKCON @ addr 0xD8----------------------------------------------------------*/
#define CLKCON_MASK				    (0xFF)

#define CLKCON_SCKTYPE_MASK		(0x80) //慢时钟类型选择，Slow Clock Type. 1=SXT, 0=SRC
#define CLKCON_SCKTYPE_POS		(7)

#define CLKCON_FCKTYPE_MASK		(0x40) //Fast clock Type. 0=FRC, 1=FXT.
#define CLKCON_FCKTYPE_POS		(6)

#define CLKCON_STPSCK_MASK		(0x20) //Stop Slow Clock in PDOWN
#define CLKCON_STPSCK_POS			(5)

#define CLKCON_STPPCK_MASK		(0x10) //1=进入IDL模式，Stop UART/Timer0/Timer1/Timer2 Clock in Idle mode
#define CLKCON_STPPCK_POS			(4)

#define CLKCON_STPFCK_MASK		(0x08) //1=停止快时钟，0=快时钟工作
#define CLKCON_STPFCK_POS			(3)

#define CLKCON_SELFCK_MASK		(0x04) //1=选择快时钟为系统时钟源，0=慢时钟为系统时钟源 
#define CLKCON_SELFCK_POS			(2)

#define CLKCON_CLKPSC_MASK		(0x03)  
#define CLKCON_CLKPSC_POS			(0)

/*-----------MICON @ addr 0xE1----------------------------------------*/
#define MICON_MASK          (0xFF)

#define MICON_MIEN_MASK     (0x80)  //Master IIC enable
#define MICON_MIEN_POS      (7)

#define MICON_MIACKO_MASK   (0x40)  //When Master IIC receive Data, send acknowledge to IIC Bus
#define MICON_MIACKO_POS    (6)     //0->ACK to slave device,1->NACK to slave device

#define MICON_MIIF_MASK     (0x20)  //Master IIC Interrupt flag
#define MICON_MIIF_POS      (5)     //1->Master IIC transmit or receive one byte complete,0->H/W write 0 to clear it

#define MICON_MIACKI_MASK   (0x10)  //"When Master IIC transmission, acknowledgement form IIC bus (read only)
#define MICON_MIACKI_POS    (4)     //0->ACK received,1->NACK received"

#define MICON_MISTART_MASK  (0x08)  //"Master IIC Start Bit 
#define MICON_MISTART_POS   (3)     //1->start IIC bus transmit period of MISTART=0 must longer than a IIC clock period"

#define MICON_MISTOP_MASK   (0x04)  //" Master IIC Stop Bit
#define MICON_MISTOP_POS    (2)     //1->send STOP signal to stop IIC bus"

#define MICON_MICR_MASK     (0x03)  // 00->Fsys/4  ,01->Fsys/16 
#define MICON_MICR_POS      (0)     // 10->Fsys/64 ,11->Fsys/256

/*-----------SIADR @ addr 0xE9----------------------------------------*/
#define SIADR_MASK		      (0xFF)

#define SIADR_SA_MASK		    (0xFE)  //Write->I2C Slave address assigned
#define SIADR_SA_POS        (1)     //Read ->address received at I2C Slave 

#define SIADR_SIEN_MASK		  (0x01)	// Slave IIC enable
#define SIADR_SIEN_POS      (0) 

/*-----------SICON @ addr 0xEA----------------------------------------*/
#define SICON_MASK		      (0xFF)

#define SICON_MIIE_MASK		  (0x80)	 //I2C Master INT enable
#define SICON_MIIE_POS      (7)

#define SICON_TXDIE_MASK		(0x40)	 //I2C Slave Data transmit INT enable
#define SICON_TXDIE_POS     (6)

#define SICON_RCD2IE_MASK		(0x20)	 //I2C Slave SIRCD2 receive INT enable
#define SICON_RCD2IE_POS    (5)

#define SICON_RCD1IE_MASK		(0x10)	 //I2C Slave SIRCD1 receive INT enable
#define SICON_RCD1IE_POS    (4)

#define SICON_TXDF_MASK		  (0x04)	 //I2C Slave Data transmit INT flag, it will not transmit SITXD Data and return NACK while 1
#define SICON_TXDF_POS      (2)

#define SICON_RCD2F_MASK		(0x02)	 //I2C Slave Data received INT flag, it will not receive SITXD Data and return NACK while 1
#define SICON_RCD2F_POS     (1)

#define SICON_RCD1F_MASK		(0x01)	 //I2C Slave data received INT flag, it will not receive SIRCD1 data and return NACK while 1
#define SICON_RCD1F_POS     (0)

/*-----------AUX3 @ addr 0xEF----------------------------------------*/
#define AUX3_MASK		        (0xFF)

#define AUX3_TM3PSC_MASK    (0x38)   //Timer3 Int Prescale. 
#define AUX3_TM3PSC_POS     (3)

#define AUX3_VBGEN_MASK		  (0x04)	 //1->VBGEN ENABLE,0->VBGEN DISABLE
#define AUX3_VBGEN_POS      (2)

#define AUX3_ADVREFS_MASK	  (0x03)	 // 00->VCC,01->2.5V
#define AUX3_ADVREFS_POS    (0)      // 10->3V ,11->4V 

/*-----------AUX2 @ addr 0xF7----------------------------------------*/
#define AUX2_MASK		        (0xFF)

#define AUX2_WDTE_MASK		  (0xC0)	 // WDTE:AUX2 Bit[7:6],WDT Control
#define AUX2_WDTE_POS       (6)      // 00->WDT Disable,10->Enable in Fast/Slow, Disable in Idle/Stop mode,11->WDT Always Enable

#define AUX2_PWRSAV_MASK		(0x20)	 //1: LVR disable at IDLE/PDOWN, 0: LVR enable at IDLE/PDOWN
#define AUX2_PWRSAV_POS     (5)

#define AUX2_VBGOUT_MASK		(0x10)	 //1: VBG output to P3.2, 0: P32 as normal IO (extra condition: VBGEN =1 or ADCHS=1011b or ADVREFS≠00b)"
#define AUX2_VBGOUT_POS     (4)

#define AUX2_DIV32_MASK		  (0x08)	 //only active when MULDVI16 =1
#define AUX2_DIV32_POS      (3)

#define AUX2_IAPTE_MASK		  (0x06)	 //IAPTE:AUX2 Bit[2:1],IAP TIMEOUT Enable  00:Disable  01: 2.8mS   10:  11mS  11:22mS
#define AUX2_IAPTE_POS      (1)

#define AUX2_MULDIV16_MASK	(0x01)	 //0->instruction mul/div as 8*8, 8/8 operation  
#define AUX2_MULDIV16_POS   (0)      //1->instruction mul/div as 16*16, 16/16 or 32/16 operation

/*-----------AUX1 @ addr 0xF8----------------------------------------*/
#define AUX1_MASK		        (0xFF)

#define AUX1_CLRWDT_MASK		(0x80)	 //Clear WatchDog, HW Auto clear
#define AUX1_CLRWDT_POS     (7) 

#define AUX1_CLRTM3_MASK	  (0x40)	 //清零TM3也是启动TM3
#define AUX1_CLRTM3_POS     (6) 

#define AUX1_ADSOC_MASK		  (0x10)	 //ADC开始，结束时硬件自动清零
#define AUX1_ADSOC_POS      (4)

#define AUX1_LVRPD_MASK		  (0x08)	 //1: LVR disable, 0: LVR enable
#define AUX1_LVRPD_POS      (3)

#define AUX1_T2SEL_MASK		  (0x04)	 //Timer2 counter mode input, 0=P1.0 pin, 1=SLOWCLK/16
#define AUX1_T2SEL_POS      (2)

#define AUX1_T1SEL_MASK		  (0x02)	 //Timer1 counter mode input, 0=P3.5 pin, 1=SLOWCLK/16
#define AUX1_T1SEL_POS      (1)

#define AUX1_DPSEL_MASK		 	(0x01)	 //0表选择DPTR;1表选择DPTR1
#define AUX1_DPSEL_POS      (0)

/*-----------ICECON @addr 0xF9----------------------------------------*/
#define ICECON_MASK		      (0xF9)

#define ICECON_HWBRK_MASK		(0x80)	 // H/W Break,only read
#define ICECON_HWBRK_POS    (7)

#define ICECON_ETROREQ_MASK	(0x40)	 // Retro-OPCode Request,R/W
#define ICECON_ETROREQ_POS  (6)      // HW set at SWBRK, clear at NMI return

#define ICECON_TXRDY_MASK		(0x20)	 // Transmitt ready,R/W
#define ICECON_TXRDY_POS    (5)

#define ICECON_CMDRDY_MASK	(0x10)	 // Ready for command,R/W
#define ICECON_CMDRDY_POS   (4)

#define ICECON_XFIRCK_MASK	(0x08)	 // Swich to FIRC 4MHz,R/W
#define ICECON_XFIRCK_POS   (3)

#define ICECON_WRFAIL_MASK	(0x01)	 // EEPROM write fail,only read
#define ICECON_WRFAIL_POS   (0)

/*-----------LVDS @addr 0xBF----------------------------------------*/
#define LVDS_MASK        (0xCF)

#define	LVDS_LVDPD_MASK	 (0x80)	// LVD enable control
#define	LVDS_LVDPD_POS   (7)

#define	LVDS_LVDO_MASK	 (0x40) // LVDO control
#define	LVDS_LVDO_POS    (6)

#define	LVDS_LVDSEL_MASK (0x0F) // LVD Select
#define LVDS_LVDSEL_POS  (0)

/*-----------ADCHS @addr 0xB6----------------------------------------*/
#define ADCHS_MASK		     	  (0x1F)	 //ADC Channel Select

/*-----------ADCDL @addr 0xAA----------------------------------------*/
#define ADCDL_MASK            (0xF0)

/*-----------ADCDH @addr 0xAB----------------------------------------*/
#define ADCDH_MASK            (0xFF)

/*-----------LEDCON @addr 0xB1----------------------------------------*/
#define LEDCON_MASK            (0xFF)
 
#define LEDCON_LEDPNEN_MASK    (0xC0)
#define LEDCON_LEDPNEN_POS     (6)

#define LEDCON_LEDPSC_MASK		 (0x30)
#define LEDCON_LEDPSC_POS    	 (4)
 
#define LEDCON_LEDHOLD_MASK		 (0x08)
#define LEDCON_LEDHOLD_POS     (3)

#define LEDCON_LEDBRIT_MASK		 (0x07)
#define LEDCON_LEDBRIT_POS     (0)

/*-----------LEDCON2 @addr 0xB2----------------------------------------*/
#define LEDCON2_MASK          (0xFF)		

#define	LEDCON2_LEDBRTM_MASK  (0x80) // brightness mode control 
#define LEDCON2_LEDBRTM_POS   (7)

#define	LEDCON2_LEDBRIT2_MASK (0x70) // LED PN/BD Mode Brightness control  
#define LEDCON2_LEDBRIT2_POS  (4)

#define	LEDCON2_LEDMTEN_MASK  (0x08) // LED BD-Mode enable control
#define LEDCON2_LEDMTEN_POS   (3)	

#define	LEDCON2_LEDBRIT1_MASK (0x07) // LED SEG4- Brightness control 
#define LEDCON2_LEDBRIT1_POS  (0)

/*-------INTPWM @ addr 0x86-------------------------------------------*/ 
#define	INTPWM_MASK         (0xFF)    //PWM  Interrupt Mask 

#define	INTPWM_PWM2IF_MASK	(0x04)	  //PWM2 Interrupt Flag Mask
#define	INTPWM_PWM2IF_POS	  (2)

#define	INTPWM_PWM1IF_MASK	(0x02)	  //PWM1 Interrupt Flag Mask
#define	INTPWM_PWM1IF_POS	  (1)

#define	INTPWM_PWM0IF_MASK	(0x01)	  //PWM0 Interrupt Flag Mask
#define	INTPWM_PWM0IF_POS	  (0)

/*-----------PWMCON @addr 0xA1-------------------------------------------------------------*/	
#define	PWMCON_MASK         (0x3F)

#define	PWMCON_PWM2CKS_MASK	 (0x30)	//PWM2 Clock source. 11=FIRC*2, 10=FIRC, 01=Cpuclk
#define	PWMCON_PWM2CKS_POS   (4)

#define	PWMCON_PWM1CKS_MASK	 (0x0C)	//PWM1 Clock source. 11=FIRC*2, 10=FIRC, 01=Cpuclk
#define	PWMCON_PWM1CKS_POS   (2)

#define	PWMCON_PWM0CKS_MASK	 (0x03)	//PWM0 Clock source. 11=FIRC*2, 10=FIRC, 01=Cpuclk
#define	PWMCON_PWM0CKS_POS   (0)

/*-----------PWMCON2 @addr 0xA7------------------------------------------------------------*/
#define	PWMCON2_MASK         (0x77)

#define	PWMCON2_PWM2IE_MASK	 (0x40)	//PWM2 Interrupt Enable. 1: enable, 0: disable
#define	PWMCON2_PWM2IE_POS   (6)

#define	PWMCON2_PWM1IE_MASK	 (0x20)	//PWM1 Interrupt Enable. 1: enable, 0: disable
#define	PWMCON2_PWM1IE_POS   (5)

#define	PWMCON2_PWM0IE_MASK	 (0x10)	//PWM0 Interrupt Enable. 1: enable, 0: disable
#define	PWMCON2_PWM0IE_POS   (4)

#define	PWMCON2_PWM2CLR_MASK (0x04)	//Clear PWM2,1:clear and hold,0->runing
#define	PWMCON2_PWM2CLR_POS  (2)

#define	PWMCON2_PWM1CLR_MASK (0x02)	//Clear PWM1,1:clear and hold,0->runing
#define	PWMCON2_PWM1CLR_POS  (1)

#define	PWMCON2_PWM0CLR_MASK (0x01)	//Clear PWM0,1:clear and hold,0->runing	
#define	PWMCON2_PWM0CLR_POS  (0)

/*----------------------------------------------------------------
  定义GPIO 模式	
  ---------------------------------------------------------------*/
#define GPIO_CmosOutput            (0x06)
//#define GPIO_CmosOutput          (0x0A)
//#define GPIO_CmosOutput          (0x0E)

#define GPIO_LED                   (0x07)
#define GPIO_PWMO_TxO_CKO          (0x0B)
#define GPIO_LCD1_2_BIAS           (0x0F)

#define GPIO_OD_PU                 (0x00)  //开漏带上拉
#define GPIO_OD                    (0x05)
#define GPIO_OD_PD                 (0x04)  //open-drain pull-down   
#define GPIO_OD_PD_PinChgWKUP_INT  (0x0C)
#define GPIO_OD_PU_PinChgWKUP_INT  (0x08)  //open-drain pull-up 
#define GPIO_OD_PinChgWKUP_INT     (0x09)
//#define GPIO_OD_PinChgWKUP_INT   (0x0D)
  
/*-------------------------------------------------------------------------------------- 
  FIRC:18.432MHz
	Bit[5:4]:PWM2CKS->PWM2 Clock source. 11=FIRC*2, 10=FIRC, 01=Cpuclk, 
	Bit[3:2]:PWM1CKS->PWM1 Clock source. 11=FIRC*2, 10=FIRC, 01=Cpuclk, 
	Bit[1:0]:PWM0CKS->PWM0 Clock source. 11=FIRC*2, 10=FIRC, 01=Cpuclk, 
  -------------------------------------------------------------------------------------*/
typedef enum
{
  PWMxSrc_Cpuclk = 0x01,
  PWMxSrc_FIRC   = 0x02,
  PWMxSrc_2FIRC  = 0x03
}PWMx_ClkSrc_TypeDef;

/*------------------------------------------------
  Timer0 工作模式类型定义
	00     13位计时/计数器
	01     16位计时/计数器 
	10     8位自动加载计数/计时器
	11     仅适用于T0,T0分为两个独立的8位定时器/计数器TH0及TL0,在此模式下T1停止工作
  -------------------------------------------------*/
typedef enum
{
  T0_Mode0_13 = 0x00,
  T0_Mode1_16 = 0x01,
  T0_Mode2_8  = 0x02,
  T0_Mode3_88 = 0x03
}Timer0_Mode_TypeDef;

/*------------------------------------------------
  Timer1 工作模式类型定义
	00     13位计时/计数器
	01     16位计时/计数器 
	10     8位自动加载计数/计时器
	11     timer stop
  -------------------------------------------------*/
typedef enum
{
  T1_Mode0_13 = 0x00,
  T1_Mode1_16 = 0x10,
  T1_Mode2_8  = 0x20,
  T1_Mode3_88 = 0x30
}Timer1_Mode_TypeDef;

/*----------------------------------------------------------------------------
	Bit[5:3] ,Timer3 Int Prescale. 	
						000->32768*Clk, 
						001->16384*Clk, 
						010->8192*Clk, 
						011->4096*Clk
						100->2048*Clk, 
						101->1024*Clk, 
						110->512*Clk, 
						111->256*Clk
	--------------------------------------------------------------------------*/
typedef enum
{
	T3_Psc_32768  =0x00,
	T3_Psc_16384  =0x08,
	T3_Psc_8192   =0x10,
	T3_Psc_4096   =0x18,
	T3_Psc_2048   =0x20,
	T3_Psc_1024   =0x28,
	T3_Psc_512    =0x30,
	T3_Psc_256    =0x38
}Timer3_Prescale_TypeDef;

/*------------------------------------------------------------------------------------
  CLKPSC:CLKCON Bit[1:0]
  系统时钟预分频:
                  0:div16, 
									1:div4, 
								  2:div2, 
									3:div1
	------------------------------------------------------------------------------------*/
typedef enum
{
	SYSCLKPSC_Div16	=0x00,
	SYSCLKPSC_Div4	=0x01,
	SYSCLKPSC_Div2	=0x02,
	SYSCLKPSC_Div1	=0x03
}SysClk_Prescaler_TypeDef;

/*-----------------------------------------------------------------------------------
  uart 工作模式类型定义
	00     模式0->波特率由振荡器频率所定:振荡器频率/12
	01     模式1->波特率由定时器T1或T2的溢出率和SMOD所定:2SMOD*(T1溢出率)/32 
	10     模式2->波特率由振荡器频率和SMOD所定:2SMOD*振荡器频率/64
	11     模式3->波特率由定时器T1或T2的溢出率和SMOD所定:2SMOD*(T1溢出率)/32
  -----------------------------------------------------------------------------------*/
typedef enum
{
  Uart1_Mode0 = 0x00,
  Uart1_Mode1 = 0x40,
  Uart1_Mode2 = 0x80,
  Uart1_Mode3 = 0xC0
}Uart1_Mode_TypeDef;

typedef enum
{
  Uart2_8Bit = 0x00,
  Uart2_9Bit = 0x80
}Uart2_Mode_TypeDef;

/*------------------------------------------------
  PINMOD Bit[3:2],UART2 Pin Select
	00: RXD2/TXD2 = P0.0/P0.1,
	01: RXD2/TXD2 = P3.5/P3.6
	10: RXD2/TXD2 = P0.1/P0.0
	11: RXD2/TXD2 = P3.6/P3.5
  -------------------------------------------------*/
typedef enum
{
  Uart2_RxTxP00P01 = 0x00,
  Uart2_RxTxP35P36 = 0x04,
  Uart2_RxTxP01P00 = 0x08,
  Uart2_RxTxP36P35 = 0x0C
}Uart2_PinSel_TypeDef;

/*------------------------------------------------
  PINMOD Bit[1:0],UART1 Pin Select
	00: RXD1/TXD1 = PP3.0/P3.1,
	01: RXD1/TXD1 = P3.2/P3.3
	10: RXD1/TXD1 = P3.1/P3.0
	11: RXD1/TXD1 = P3.3/P3.2	
  -------------------------------------------------*/
typedef enum
{
  Uart1_RxTxP30P31 = 0x00,
  Uart1_RxTxP32P33 = 0x01,
  Uart1_RxTxP31P30 = 0x02,
  Uart1_RxTxP33P32 = 0x03
}Uart1_PinSel_TypeDef;

#define 	UART2_RX_ENABLE		   SCON2=(SCON2&0xEF)|REN2
#define 	UART2_RX_DISABLE		 SCON2=(SCON2&0xEF)

/*================================================*/
/*------------------------------------------------
  IIC clock Select
	00->Fsys/4  
  01->Fsys/16 
	10->Fsys/64 
  11->Fsys/256
  -------------------------------------------------*/
typedef enum
{
  IIC_SysClk_Div4   = 0x00,
  IIC_SysClk_Div16  = 0x01,
  IIC_SysClk_Div64  = 0x02,
  IIC_SysClk_Div256 = 0x03
}IIC_Clock_TypeDef;



#define   IIC_Master_Enable    MICON |= MICON_MIEN_MASK; 
#define   IIC_Master_Disable   MICON &=~MICON_MIEN_MASK; 

#define   IIC_Send_Start	     MICON &= ~MICON_MISTOP_MASK;  \ 
	                             MICON |=  MICON_MISTART_MASK; 	

#define   IIC_Send_Stop        MICON &= ~MICON_MISTART_MASK; \ 
                               MICON |=  MICON_MISTOP_MASK;  \
                               Bsp_delay_ms(5); 

#define   IIC_Send_NACK        MICON |= MICON_MIACKO_MASK; 
#define   IIC_Send_ACK         MICON &=~MICON_MIACKO_MASK; 

#define   IIC_MasterINT_Enable    SICON |= SICON_MIIE_MASK; 
#define   IIC_MasterINT_Disable   SICON &=~SICON_MIIE_MASK; 

#define   IIC_INT_Enable 	        INTE1 |=  INTE1_I2CE_MASK;    //I2CE interrupt enable	
#define   IIC_INT_Disable         INTE1 &= ~INTE1_I2CE_MASK;    //I2CE interrupt disable	

#define   IIC_MasterINT_clrFlg    MICON &= ~MICON_MIIF_MASK;   //clear IIC interrupt flag
//----------------------------------------------------------------------
#define   IIC_Slave_Enable     					 SIADR |= SIADR_SIEN_MASK; 
#define   IIC_Slave_Disable    					 SIADR &=~SIADR_SIEN_MASK;

#define   IIC_SlaveDataTxINT_Enable      SICON |= SICON_TXDIE_MASK; 
#define   IIC_SlaveDataTxINT_Disable     SICON &=~SICON_TXDIE_MASK; 

#define   IIC_SlaveSIRCD2RxINT_Enable    SICON |= SICON_RCD2IE_MASK; 
#define   IIC_SlaveSIRCD2RxINT_Disable   SICON &=~SICON_RCD2IE_MASK;

#define   IIC_SlaveSIRCD1RxINT_Enable    SICON |= SICON_RCD1IE_MASK; 
#define   IIC_SlaveSIRCD1RxINT_Disable   SICON &=~SICON_RCD1IE_MASK;

#define   IIC_SlaveDataTxINT_clrFlg      SICON &=~SICON_TXDF_MASK; 
#define   IIC_SlaveSIRCD2RxINT_clrFlg    SICON &=~SICON_RCD2F_MASK;
#define   IIC_SlaveSIRCD1RxINT_clrFlg    SICON &=~SICON_RCD1F_MASK;

//typedef enum
//{
//  GPIO_PuPd_NOPULL = 0x00,
//  GPIO_PuPd_UP     = 0x01,
//  GPIO_PuPd_DOWN   = 0x02,
//  GPIO_PuPd_UPDOWN = 0x03
//}GPIOPuPd_TypeDef;

///**
//  * @brief  GPIO Init structure definition  
//  */
//typedef struct
//{
//  uint32_t          GPIO_Pin;    /*!< Specifies the GPIO pins to be configured.This parameter can be any value of @ref GPIO_pins_define */                                     
//  GPIOMode_TypeDef  GPIO_Mode;   /*!< Specifies the operating mode for the selected pins.This parameter can be a value of @ref GPIOMode_TypeDef   */
//  GPIOSpeed_TypeDef GPIO_Speed;  /*!< Specifies the speed for the selected pins.This parameter can be a value of @ref GPIOSpeed_TypeDef  */
//  GPIOOType_TypeDef GPIO_OType;  /*!< Specifies the operating output type for the selected pins. This parameter can be a value of @ref GPIOOType_TypeDef  */
//  GPIOPuPd_TypeDef  GPIO_PuPd;   /*!< Specifies the operating Pull-up/Pull down for the selected pins.                                      This parameter can be a value of @ref GPIOPuPd_TypeDef   */
//  GPIODR_TypeDef    GPIO_DR;     /*  GPIO output driver strength*/
//}GPIO_InitTypeDef;


typedef struct
{
	unsigned char year;
	unsigned char month;
	unsigned char day;
	unsigned char hour;
	unsigned char min;	
}TIME_InitTypeDef;

#define  SW_Reset  					0x56  //Write 56h to SWCMD Register will generate SW Reset
#define  IAP_En    					0x65  //Write 65h to SWCMD Register to enable IAP all area
#define  IAP_Dis   					0x00  //Write other value to SWCMD Register to disable IAP all

#define MainRomIAP_WriteEn  0x47  //Write 47H to IAPWE Register for enable main ROM IAP write
#define EEPROM_WriteEn      0xE2  //Write E2H to IAPWE Register for enable EEPROM       write
#define IAP_WriteDis        0x00  //Write other value to this Register for disable IAP write
							
typedef enum
{
	 LVD_4p35V =0x0F,  // LVD 4.35V
	 LVD_4p20V =0x0E,  // LVD 4.20V
	 LVD_4p05V =0x0D,  // LVD 4.05V
	 LVD_3p90V =0x0C,  // LVD 3.90V
	 LVD_3p75V =0x0B,  // LVD 3.75V
	 LVD_3p60V =0x0A,  // LVD 3.60V
	 LVD_3p45V =0x09,  // LVD 3.45V
	 LVD_3p30V =0x08,  // LVD 3.30V
	 LVD_3p15V =0x07,  // LVD 3.15V
	 LVD_3p00V =0x06,  // LVD 3.00V
	 LVD_2p85V =0x05,  // LVD 2.85V
	 LVD_2p70V =0x04,  // LVD 2.70V
	 LVD_2p55V =0x03,  // LVD 2.55V
	 LVD_2p40V =0x02,  // LVD 2.40V
	 LVD_2p25V =0x01,  // LVD 2.25V
	 LVD_2p10V =0x00   // LVD 2.1V
}LVDSEL_TypeDef;

typedef enum
{
	ADCHS_AD0    =0x00,  // AD0->(P0.4)
	ADCHS_AD1    =0x01,  // AD1->(P0.5)
	ADCHS_AD2    =0x02,  // AD2->(P2.0)
	ADCHS_AD3    =0x03,  // AD3->(P2.1)
	ADCHS_AD4    =0x04,  // AD4->(P1.0)
	ADCHS_AD5    =0x05,  // AD5->(P1.1)
	ADCHS_AD6    =0x06,  // AD6->(P1.2)
	ADCHS_AD7    =0x07,  // AD7->(P1.3)
	ADCHS_AD8    =0x08,  // AD8->(P1.4)
	ADCHS_AD9    =0x09,  // AD9->(P1.5)
	ADCHS_AD10   =0x0A,  // AD10->(P1.6)
	ADCHS_VBG    =0x0B,  // AD11->(Internal Bandgap Reference Voltage)
	ADCHS_AD12   =0x0C,  // AD12->(P1.7)
	ADCHS_AD13   =0x0D,  // AD13->(P2.2)
	ADCHS_AD14   =0x0E,  // AD14->(P2.3)
	ADCHS_AD15   =0x0F,  // AD15->(P2.4)
	ADCHS_AD16   =0x10,  // AD16->(P2.5)
	ADCHS_AD17   =0x11,  // AD17->(P0.6)
	ADCHS_AD18   =0x12,  // AD18->(P0.7)
	ADCHS_AD19   =0x13,  // AD19->(P0.0)
	ADCHS_AD20   =0x14,  // AD20->(P0.1)
	ADCHS_AD21   =0x15,  // AD21->(P0.2)
	ADCHS_AD22   =0x16,  // AD22->(P0.3)
	ADCHS_1_4VCC =0x17   // AD23->(1/4VCC)
}ADCHS_TypeDef; 

typedef enum
{
	ADC_Vref_VCC  =0x00,  //ADC Vref select VCC
	ADC_Vref_2V5  =0x01,  //ADC Vref select 2.5V
  ADC_Vref_3V   =0x20,  //ADC Vref select 3V
	ADC_Vref_4V   =0x03   //ADC Vref select 4V
}ADC_Vref_TypeDef; 

typedef enum
{
	AdcClkPsc_32  =0x00,  //Interrupt rate is 32768 system clock cycle
	AdcClkPsc_16  =0x04,  //Interrupt rate is 16384 system clock cycle
  AdcClkPsc_8   =0x08,  //Interrupt rate is 8192 system clock cycle
	AdcClkPsc_4   =0x0C   //Interrupt rate is 128 system clock cycle
}AdcClkPsc_TypeDef; 

/*-------------------------------------------------------------------
	Bit[5:4]:WDTPSC ->Watch Dog Timer Prescale
										00->div 0
										01->div 1
										10->div 2
										11->div 3  Fastest
 --------------------------------------------------------------------*/
typedef enum
{
	WdtClkPsc_0  =0x00,   
	WdtClkPsc_1  =0x10,   
  WdtClkPsc_2  =0x20,   
	WdtClkPsc_3  =0x30    
}WdtClkPsc_TypeDef; 

typedef enum
{
	PerPWM0 =0,
	PerPWM1 =1,
	PerPWM2 =2
}Peripheral_TypeDef; 

#endif
