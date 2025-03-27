/*
******************************************************************************************************
Name		:REGtenxTM52F1376.h
Version		:V1.0
Author		:MFTu
Date		:2020.09.11
******************************************************************************************************
*/
#ifndef __HTX3736Z_H__
#define __HTX3736Z_H__


/*--------------------------------------------------------------------------------------*/
sfr 	P0    		  = 0x80;		 //Port 0 Data
	sbit 		P0_7		= P0^7;
	sbit 		P0_6		= P0^6;
	sbit 		P0_5		= P0^5;
	sbit 		P0_4		= P0^4;
	sbit 		P0_3		= P0^3;
	sbit 		P0_2		= P0^2;
	sbit 		P0_1		= P0^1;
	sbit 		P0_0		= P0^0;
	
/*-------------------------------------------------------------------------------------- */
sfr 	SP   				= 0x81;		 //Stack Point
sfr 	DPL   			= 0x82;		 //Data Point Low byte
sfr 	DPH   			= 0x83;    //Data Point High byte

/*-------------------------------------------------------------------------------------- */
sfr 	INTPORT		  = 0x85;   //Port  Pin Change Interrupt Flag.
	#define		P3IF		0x08	  //Port3 Pin Change Interrupt Flag.
	#define		P2IF		0x04	  //Port2 Pin Change Interrupt Flag.
	#define		P1IF		0x02	  //Port1 Pin Change Interrupt Flag.
	#define		P0IF		0x01	  //Port0 Pin Change Interrupt Flag.

/*-------------------------------------------------------------------------------------- 
  Bit[2]:PWM2IF->PWM2 Interrupt Flag
	Bit[1]:PWM1IF->PWM1 Interrupt Flag
	Bit[0]:PWM0IF->PWM0 Interrupt Flag
	       1->Interrupt asserted, write 0 to clear Int flag     
  -------------------------------------------------------------------------------------- */
sfr 	INTPWM		    = 0x86; //PWM  Interrupt Flag. 1: Interrupt asserted, write 0 to clear Int flag
	#define		PWM2IF		0x04	//PWM2 Interrupt Flag. 1: Interrupt asserted, write 0 to clear Int flag
	#define		PWM1IF		0x02	//PWM1 Interrupt Flag. 1: Interrupt asserted, write 0 to clear Int flag
	#define		PWM0IF		0x01	//PWM0 Interrupt Flag. 1: Interrupt asserted, write 0 to clear Int flag

/*-------------------------------------------------------------------------------------- */
sfr 	PCON  		= 0x87;			//��֧��λ����,�ö���д��ʽ
	#define 	SMOD	0x80		  //PCON Bit[7],1=�����ʱ���	 
	#define 	GF1		0x08		  //PCON Bit[3],�û��������ʹ��
	#define 	GF0		0x04			//PCON Bit[2],�û��������ʹ��	 
	#define 	PD		0x02			//PCON Bit[1],��λ��1,оƬ����stopģʽ	 
	#define 	IDL		0x01			//PCON Bit[0],��λ��1,оƬ����IDLģʽ
	 
	#define		ENTER_IDLE_MODE		PCON=(PCON&0xfe)|IDL
	#define		LEAVE_IDLE_MODE		PCON=(PCON&0xfe)
	#define		ENTER_STOP_MODE		PCON=(PCON&0xfd)|PD
	#define		LEAVE_STOP_MODE		PCON=(PCON&0xfd)
	
/*-------------------------------------------------------------------------------------- */
sfr 	TCON  		  = 0x88;
	sbit 		TF1 		= TCON^7;	//��ʱ��T1�����־,���ɳ����ѯ������,TF1Ҳ���ж�����Դ,��CPU��ӦT1�ж�ʱ��Ӳ������
	sbit 		TR1 		= TCON^6;	//T1�����������λ,Ϊ1ʱ����T1����

	sbit 		TF0 		= TCON^5;	//��ʱ��T0�����־,���ɳ����ѯ������,TF0Ҳ���ж�����Դ,��CPU��ӦT0�ж�ʱ��Ӳ������
	sbit 		TR0			= TCON^4;	//T0�����������λ,Ϊ1ʱ����T0����

	sbit 		IE1 		= TCON^3;	//�ⲿ�ж�1��ʾԴ(INT1,P3.3)��־;IE1Ҳ���ж�����Դ,��CPU��Ӧ���ж�ʱ��Ӳ����IE1(���ش�����ʽ)
	sbit 		IT1 		= TCON^2;	//�ⲿ�ж�Դ1������ʽ����λ,IT1��0,�ⲿ�ж�1�̿�Ϊ��ƽ������ʽ;��INT1��P3.3������͵�ƽʱ,��λIE1

	sbit 		IE0 		= TCON^1;	//�ⲿ�ж�0��ʾԴ(INT1,P3.2)��־;IE0Ҳ���ж�����Դ,��CPU��Ӧ���ж�ʱ��Ӳ����IE0(���ش�����ʽ)
	sbit 		IT0 		= TCON^0;	//�ⲿ�ж�Դ0������ʽ����λ,IT0��0,�ⲿ�ж�0�̿�Ϊ��ƽ������ʽ;��INT0��P3.2������͵�ƽʱ,��λIE0

/*--------------------------------------------------------------------------------------------------------- 
  Bit[7]  :T1GATE->��ʱ��1�������ؿ���λ
	                 1->INT1����Ϊ�ߵ�ƽ,ͬʱTCON�е�TR1����λΪ1ʱ,��ʱ/������1�ſ�ʼ����
					 	 			 0->ֻҪ��TR1����λ��Ϊ1����ʱ/������1�Ϳ�ʼ����
  Bit[6]  :CT1   ->��ʱ��1��ʱ/�������ܵ�ѡ��λ
	                 1->������,ͨ���ⲿ����T1�����������
					 	 			 0->��ʱ��,���ڲ�ϵͳʱ���ṩ��ʱ��������
  Bit[5:4]:T1MOD ->��ʱ��1ģʽѡ��λ
	                 00->T1Ϊ13λ��ʱ/������
									 01->T1Ϊ16λ��ʱ/������
									 10->T1Ϊ8λ�Զ����ؼ���/��ʱ�� 
									 11->timer stop	
	Bit[3]  :T0GATE->��ʱ��0�������ؿ���λ
									 1->INT0����Ϊ�ߵ�ƽ,ͬʱTCON�е�TR0����λΪ1ʱ,��ʱ/������0�ſ�ʼ����
									 0->ֻҪ��TR0����λ��Ϊ1����ʱ/������0�Ϳ�ʼ����
  Bit[2]  :CT0   ->��ʱ��0��ʱ/�������ܵ�ѡ��λ
	                 1->������,ͨ���ⲿ����T0�����������
					 	 			 0->��ʱ��,���ڲ�ϵͳʱ���ṩ��ʱ��������
  Bit[1:0]:T0MOD ->��ʱ��0ģʽѡ��λ
									 00->T0Ϊ13λ��ʱ/������ 
									 01->T0Ϊ16λ��ʱ/������ 
									 10->T0Ϊ8λ�Զ����ؼ���/��ʱ��
									 11->��������T0,T0��Ϊ����������8λ��ʱ��/������TH0��TL0,�ڴ�ģʽ��T1ֹͣ����
  ----------------------------------------------------------------------------------------------------------*/
sfr 	TMOD  		     = 0x89;	 // ��֧��λ����,�ö���д��ʽ 
  #define 	T1_Mask		~0xF0		 // Bit[7:4]->T1����ģʽѡ��Mask 
	#define 	T0_Mask		~0x0F		 // Bit[3:0]->T0����ģʽѡ��Mask
	
	#define 	GATE1		   0x80		 // Bit[7]->��ʱ��1�������ؿ���λ 	 				          															 
	#define 	CT1			   0x40		 // Bit[6]->��ʱ/������1���ܵ�ѡ��λ			 	 				           
  #define 	GATE0			 0x08		 // Bit[3]->��ʱ��0�������ؿ���λ
  #define 	CT0				 0x04		 // Bit[2]->��ʱ/������0���ܵ�ѡ��λ
 
  #define 	T1_Mode0	 0x00	   // Bit[5:4]->T1Ϊ13λ��ʱ/������
	#define 	T1_Mode1	 0x10	   // Bit[5:4]->T1Ϊ16λ��ʱ/������
	#define 	T1_Mode2	 0x20	   // Bit[5:4]->T1Ϊ8λ�Զ����ؼ���/��ʱ�� 
	#define 	T1_Mode3	 0x30	   // Bit[5:4]->timer stop
	
	#define 	T0_Mode0	 0x00		 // Bit[1:0]->T0Ϊ13λ��ʱ/������ 
	#define 	T0_Mode1	 0x01		 // Bit[1:0]->T0Ϊ16λ��ʱ/������ 
	#define 	T0_Mode2	 0x02		 // Bit[1:0]->T0Ϊ8λ�Զ����ؼ���/��ʱ��
	#define 	T0_Mode3	 0x03		 // Bit[1:0]->��������T0,T0��Ϊ����������8λ��ʱ��/������TH0��TL0,�ڴ�ģʽ��T1ֹͣ����

/*--------------------------------------------------------------------------------------*/	
sfr 	TL0   		= 0x8A;				//Timer 0 Data low byte
sfr 	TH0   		= 0x8C;				//Timer 0 Data high byte

sfr 	TL1   		= 0x8B;				//Timer 1 Data low byte
sfr 	TH1   		= 0x8D;			  //Timer 1 Data high byte

/*--------------------------------------------------------------------------------------*/
sfr 	SCON2  		  = 0x8E;		  
	#define		SM		  0x80      // Uart2 mode select,1->9bit,0->8bit ,baud rate variable
	#define		REN2	  0x10	    // Uart2 reception enable
	#define		TB82		0x08	    // Uart2 transmit Bit8 
	#define		RB82		0x04		  // Uart2 Receive  Bit8
	#define		TI2			0x02		  // Uart2 Transmit Interrupt flag
	#define		RI2			0x01		  // Uart2 Receive  Interrupt flag
	
	#define 	UART2_9Bits		SCON2=(SCON2&0x7F)|SM   // 1->9bit,baud rate variable
	#define 	UART2_8Bits		SCON2=(SCON2&0x7F)      // 0->8bit,baud rate variable
	
	#define 	UART2_RECEPTION_ENABLE		SCON2=(SCON2&0xEF)|REN2
	#define 	UART2_RECEPTION_DISABLE		SCON2=(SCON2&0xEF)

/*-------------------------------------------------------------------------------------- 
  Bit[7:6]:[SM0][SM1] ->���пڹ�����ʽ����λ Bit[0][1]
	           0    0   ->��ʽ0,������������Ƶ������:����Ƶ��/12
					   0    1   ->��ʽ1,�������ɶ�ʱ��T1��T2������ʺ�SMOD����:2SMOD*(T1�����)/32
					   1    0   ->��ʽ2,������������Ƶ�ʺ�SMOD����:2SMOD*����Ƶ��/64
					   1    1   ->��ʽ3,�������ɶ�ʱ��T1��T2������ʺ�SMOD����:2SMOD*(T1�����)/32 
	Bit[5]  :SM2 ->���ͨ�ſ���λ,��Ҫ���ڹ�����ʽ2�ͷ�ʽ3����״̬
					 	 		 1->ֻ�е����յ���9λ����(RB8)Ϊ1ʱ,�Űѽ��յ���ǰ8λ��������SBUF,
								    ����λRI�����ж�����,����Ὣ���յ������ݷ���
					 	 		 0->���ܵ�9λ������0����1,������������SBUF,
								    �������ж�����,�����ڷ�ʽ0ʱ��SM2����Ϊ0
	Bit[4]  :REN ->����ʹ��λ
                 1->�������
								 0->��ֹ���� 	
	Bit[3]  :TB8 ->�������ݵ�8λ	
  Bit[2]  :RB8 ->�������ݵ�8λ 	
	Bit[1]  :TI  ->�����жϱ�־λ,1->��ʾ֡���ͽ���,�����������
	               ��ʽ0ʱ,�������8λ���ݺ�,��Ӳ����λ
	               ������ʽ��,��Ӳ����λ					 	    
	Bit[0]  :RI  ->�����жϱ�־λ,1->��ʾ֡�������
                 ��ʽ0ʱ,�������8λ���ݺ�,��Ӳ����λ
					 	 		 ������ʽ��,��Ӳ����λ	
  -------------------------------------------------------------------------------------- */
sfr 	SCON    = 0x98;
	sbit 		SM0 = SCON^7;	//���пڹ�����ʽ����λ Bit[0]
	sbit 		SM1 = SCON^6;	//���пڹ�����ʽ����λ Bit[1]		
	sbit 		SM2 = SCON^5;	//���ͨ�ſ���λ 	    
  sbit 		REN = SCON^4;	//����ʹ��λ	
	sbit 		TB8 = SCON^3;	//�������ݵ�8λ
	sbit 		RB8 = SCON^2;	//�������ݵ�8λ 
	sbit 		TI 	= SCON^1;	//�����жϱ�־λ 	 			 
  sbit 		RI 	= SCON^0;	//�����жϱ�־λ
																					
/*--------------------------------------------------------------------------------------*/
sfr 	SBUF2  	  = 0x8F;			//Uart2 transmit and receive Data
sfr 	SBUF  		= 0x99;		  //���ڻ���Ĵ���,UART transmit and receive Data

/*--------------------------------------------------------------------------------------*/
sfr 	P1    		  = 0x90;				//Port 1 Data
	sbit 		P1_7		= P1^7;
	sbit 		P1_6		= P1^6;	
	sbit 		P1_5		= P1^5;	
	sbit 		P1_4		= P1^4;	
	sbit 		P1_3		= P1^3;	
	sbit 		P1_2		= P1^2;	
	sbit 		P1_1		= P1^1;	
	sbit 		P1_0		= P1^0;	
	
/*-------------------------------------------------------------------------------------- 
  Bit[1:0]->Pin Mode Index
	          00->Port0
						01->Port1
						10->Port2
						11->Port3
  --------------------------------------------------------------------------------------*/
sfr		PORTIDX		  = 0x91;  

/*-------------------------------------------------------------------------------------- 
  Bit[6]  :TM3CKS ->Timer3 Clock Source Select. 
	                  0->SLOW (SXT/SRC), 
										1->FRC/512 (36KHz)  
	Bit[5:4]:WDTPSC ->Watch Dog Timer Prescale
										00->div 0
										01->div 1
										10->div 2
										11->div 3  Fastest
	Bit[3:2]:ADCKS  ->ADC Clock Rate 
	    						  00->div 32     Interrupt rate is 32768 system clock cycle
										01->div 16     Interrupt rate is 16384 system clock cycle
										10->div 8      Interrupt rate is 8192 system clock cycle
										11->div 4      Interrupt rate is 128 system clock cycle
  --------------------------------------------------------------------------------------*/
sfr 	OPTION    	  = 0x94;
	#define		TM3CKS		0x40		// Bit[6]->Timer3 Clock Source Select. 
		
	#define  	WDTPSC0     OPTION= OPTION&0xCF			     
	#define  	WDTPSC1     OPTION=(OPTION&0xCF)|0x10	   
	#define  	WDTPSC2     OPTION=(OPTION&0xCF)|0x20	   
	#define  	WDTPSC3     OPTION=(OPTION&0xCF)|0x30	  
  
	#define		ADCKS_DIV32	OPTION= OPTION&0xF3	 
	#define		ADCKS_DIV16	OPTION=(OPTION&0xF3)|0x04	 
	#define		ADCKS_DIV8 	OPTION=(OPTION&0xF3)|0x08
	#define		ADCKS_DIV4 	OPTION=(OPTION&0xF3)|0x0C

/*-------------------------------------------------------------------------------------- */
sfr 	INTFLG    	= 0x95; 
	#define		LVDIF 	0x80		//Low Voltage Detect Flag, write 0 to clear Interrupt flag 
	#define		ADIF  	0x10		//ADC Interrupt Flag��HW clear while ADSOC set 
	#define 	PCIF	  0x02		//Pin Change Interrupt Flag (INTVEC=43h) 
	#define 	TF3		  0x01		//TM3 Interrupt Flag,1=TM3 Interrupt
	
/*-------------------------------------------------------------------------------------- */
sfr		INTPIN		  = 0x96;						
	#define		PIN7IF	0x80		//Px.7 Change Interrupt Flag., x define by PINIDX, write 0 to clear INT flag
	#define		PIN6IF	0x40		//Px.6 Change Interrupt Flag., x define by PINIDX, write 0 to clear INT flag
	#define		PIN5IF	0x20		//Px.5 Change Interrupt Flag., x define by PINIDX, write 0 to clear INT flag
	#define		PIN4IF	0x10		//Px.4 Change Interrupt Flag., x define by PINIDX, write 0 to clear INT flag
	#define		PIN3IF	0x08		//Px.3 Change Interrupt Flag., x define by PINIDX, write 0 to clear INT flag
	#define		PIN2IF	0x04		//Px.2 Change Interrupt Flag., x define by PINIDX, write 0 to clear INT flag
	#define		PIN1IF	0x02		//Px.1 Change Interrupt Flag., x define by PINIDX, write 0 to clear INT flag
	#define		PIN0IF	0x01		//Px.0 Change Interrupt Flag., x define by PINIDX, write 0 to clear INT flag

/*-------------------------------------------------------------------------------------- 
  Write Register:
        Write 56h   	-> generate SW Reset
        Write 65h   	-> enable IAP all area	
        Write other 	-> disable IAP all	
	Read  Register:
	      Bit[1]:WDTO	  -> WatchDog Time-Out flag 
	      Bit[0]:IAPALL	-> IAP Enable Control 				
  -------------------------------------------------------------------------------------- */
sfr		SWCMD		    = 0x97;	 
	#define		WDTO	  0x02		//WatchDog Time-Out flag
	#define		IAPALL	0x01		//IAP Enable Control

/*-------------------------------------------------------------------------------------- */
sfr 	P2    		  = 0xA0;	  //Port 2 Data
	sbit 		P2_5		= P2^5;	
	sbit 		P2_4		= P2^4;	
	sbit 		P2_3		= P2^3;	
	sbit 		P2_2		= P2^2;	
	sbit 		P2_1		= P2^1;	
	sbit 		P2_0		= P2^0;							

/*------------------------------------------------------------------------------------------ 	 
	 pinMode:
	  GPIO_OD_PU                 (0x00)
    GPIO_OD                    (0x05)
    GPIO_OD_PD                 (0x04)     open-drain pull-down
    GPIO_OD_PD_PinChgWKUP_INT  (0x0C)
    GPIO_OD_PU_PinChgWKUP_INT  (0x08)     open-drain pull-up 

    GPIO_LED                   (0x07)
    GPIO_PWMO_TxO_CKO          (0x0B)
    GPIO_LCD1_2_BIAS           (0x0F)

    GPIO_OD_PinChgWKUP_INT     (0x09)
    GPIO_OD_PinChgWKUP_INT     (0x0D)

    GPIO_CmosOutput            (0x06)
    GPIO_CmosOutput            (0x0A)
    GPIO_CmosOutput            (0x0E)
		
		note: x defined by PINIDX
  -----------------------------------------------------------------------------------------*/
sfr	PINMOD10 = 0xA2; //Bit[7:4]:PINMOD1->Px.1 Pin Control,Bit[3:0]:PINMOD0->Px.0 Pin Control
sfr	PINMOD32 = 0xA3; //Bit[7:4]:PINMOD3->Px.3 Pin Control,Bit[3:0]:PINMOD2->Px.2 Pin Control
sfr	PINMOD54 = 0xA4; //Bit[7:4]:PINMOD5->Px.5 Pin Control,Bit[3:0]:PINMOD4->Px.4 Pin Control
sfr	PINMOD76 = 0xA5; //Bit[7:4]:PINMOD7->Px.7 Pin Control,Bit[3:0]:PINMOD6->Px.6 Pin Control

/*-------------------------------------------------------------------------------------- 
	Bit[7]:HSNK2EN  ->Pin H-sink enable (Group 2 = P06, P07, P22~P25, P30~P33)
										0: Group 2 H-sink disable
										1: Group 2 H-sink enable	
	Bit[6]:HSNK1EN  ->Pin H-sink enable (Group 1 = P04, P05, P10~P17)
										0: Group 1 H-sink disable
										1: Group 1 H-sink enable
	Bit[5]:HSNK0EN	->Pin H-sink enable  (Group 0 = P00~P03, P20, P21, P34~P37)
										0: Group 0 H-sink disable
										1: Group 0 H-sink enable
	Bit[4]:IICPS	  ->IIC Pin Select
	                  0: SCL/SDA = P0.0/P0.1
										1: SCL/SDA = P3.0/P3.1
	Bit[3:2]:UART2PS->UART2 Pin Select	
	                  00: RXD2/TXD2 = P0.0/P0.1
									  01: RXD2/TXD2 = P3.5/P3.6
									  10: RXD2/TXD2 = P0.1/P0.0
									  11: RXD2/TXD2 = P3.6/P3.5
	Bit[1:0]:UARTPS	->UART Pin Select
	                  00: RXD/TXD = P3.0/P3.1
										01: RXD/TXD = P3.2/P3.3
										10: RXD/TXD = P3.1/P3.0
										11: RXD/TXD = P3.3/P3.2
 ---------------------------------------------------------------------------------------*/ 
sfr 	PINMOD  		  = 0xA6;
	#define		HSNK2EN		0x80  //Pin H-sink enable (Group 2 = P06, P07, P22~P25, P30~P33)
	#define		HSNK1EN		0x40  //Pin H-sink enable (Group 1 = P04, P05, P10~P17)
	#define		HSNK0EN		0x20  //Pin H-sink enable  (Group 0 = P00~P03, P20, P21, P34~P37)
	#define		IICPS		  0x10  //IIC Pin Select
	#define		UART2PS		0x0C  //UART2 Pin Select	
	#define		UARTPS		0x03  //UART Pin Select
	
/*----------------------------------------------------------------*/
sfr 	IE    	  	= 0xA8;
 	sbit 		EA 			= IE^7;		//EA=0ʱ,�����жϽ�ֹ;EA=1ʱ,���жϵĲ����ɸ��������λ����
	sbit		ET2			= IE^5;		//��ʱ2�ж�����
	sbit 		ES 			= IE^4;		//���п��жϳ���(ES=1����,ES=0��ֹ)
	sbit 		ET1 		= IE^3;		//��ʱ1�жϳ���
	sbit 		EX1 		= IE^2;		//���ж�INT1�жϳ���
	sbit 		ET0 		= IE^1;		//��ʱ��0�жϳ���
	sbit 		EX0 		= IE^0;		//�ⲿ�ж�INT0���ж�����
 
/*----------------------------------------------------------------*/
sfr		INTE1		    = 0xA9;
	#define		PWMIE		0x80		//PWM Interrupt Enable �ж�����
	#define		I2CE		0x40		//I2C Interrupt Enable �ж�����
	#define		ES2			0x20		//Uart2 Interrupt Enable �ж�����
	#define		ADIE 		0x08		//ADC/Touch Key  �ж�����
  #define		LVDIE		0x04		//LVD �ж�����
	#define	 	PCIE		0x02		//Pin�˿��ж�����
	#define		TM3IE		0x01		//TM3�ж�����	
	
/*-------------------------------------------------------------------------------------- 
	Bit[5:4]:PWM2CKS->PWM2 Clock source. 11=IRC18M*2, 10=IRC18M, 01=Cpuclk, 
	Bit[3:2]:PWM1CKS->PWM1 Clock source. 11=IRC18M*2, 10=IRC18M, 01=Cpuclk, 
	Bit[1:0]:PWM0CKS->PWM0 Clock source. 11=IRC18M*2, 10=IRC18M, 01=Cpuclk, 
  -------------------------------------------------------------------------------------*/
sfr		PWMCON		= 0xA1;

/*----------------------------------------------------------------*/
sfr		PWMCON2			    = 0xA7;
	#define		PWM2IE			0x40	//PWM2 Interrupt Enable. 1: enable, 0: disable
	#define		PWM1IE			0x20	//PWM1 Interrupt Enable. 1: enable, 0: disable
	#define		PWM0IE			0x10	//PWM0 Interrupt Enable. 1: enable, 0: disable

  #define		PWM2CLR			0x04	//Clear PWM2,1:clear and hold,0->runing
	#define		PWM1CLR			0x02	//Clear PWM1,1:clear and hold,0->runing
	#define		PWM0CLR			0x01	//Clear PWM0,1:clear and hold,0->runing	
	
/*----------------------------------------------------------------*/
sfr		ADCDL		= 0xAA; // Bit[7:4]->ADC Data Bit  3~0
sfr		ADCDH		= 0xAB; // Bit[7:0]->ADC Data Bit 11~4 
	
/*----------------------------------------------------------------*/
sfr 	P3    		  = 0xB0;				//Port 3 Data
	sbit 		P3_7		= P3^7;
	sbit 		P3_6		= P3^6;
	sbit 		P3_5		= P3^5;
	sbit 		P3_4		= P3^4;
	sbit 		P3_3		= P3^3;
	sbit 		P3_2		= P3^2;
	sbit 		P3_1		= P3^1;
	sbit 		P3_0		= P3^0;
	
/*-----------------------------------------------------------------------------
  Bit[7:6]:LEDEN ->LED PN-Mode Enable and duty control
	               LEDEN  ռ�ձ�     ����ѡ��      ����������ص�
									 00 : disable, 
									 01 : 1/8 duty  ->4COM x 4SEG    32(4x4x2)
									 10 : 1/9 duty  ->4COM x 5SEG    40(4x5x2)
									 11 : 1/10 duty ->4COM x 6SEG    48(4x6x2)
	Bit[5:4]:LEDPSC->LED Clock divided control ( LEDCLK  > 100K )
									 00: LED Clock divided by 0:64     
									 01: LED Clock divided by 1:32
									 10: LED Clock divided by 2:16   
									 11: LED Clock divided by 3:8 
	Bit[3]  :LEDHOLD->LED hold control
	                 1: hold LED scan, all LED pin state are Hi-Z  
									 0: release to run LED scan	
	Bit[2:0]:LEDBRIT->LED SEG0-~3- & COM0-~3- Brightness ��LED���ص�0~31��40~47 ����
                   000: Most darkness 
									 111: Most brightness 
  -----------------------------------------------------------------------------*/
sfr		LEDCON		  = 0xB1;
  #define LEDHOLD		0x08
							
	//Bit[7:6]:LEDPNEN->LED PN-Mode Enable and duty control
	#define LEDPNEN_DIS      0x00
	#define LEDPNEN_DIV8		 0x40
	#define LEDPNEN_DIV9		 0x80
	#define LEDPNEN_DIV10	   0xC0
		
  #define LEDEN_DUTY_DIV8		LEDCON=(LEDCON&0x3F)|0x40
	#define LEDEN_DUTY_DIV9		LEDCON=(LEDCON&0x3F)|0x80
	#define LEDEN_DUTY_DIV10	LEDCON=(LEDCON&0x3F)|0xC0
	#define LEDEN_DISABLE		  LEDCON=(LEDCON&0x3F)
	
	//Bit[5:4]:LEDPSC->LED Clock divided control ( LEDCLK  > 100K )
	#define	LEDPSC_64	0x00
	#define	LEDPSC_32	0x10
	#define	LEDPSC_16	0x20
	#define	LEDPSC_8	0x30

  //Bit[3]  :LEDHOLD->LED hold control		
	#define	LEDHOLD_HOLD	  LEDCON=(LEDCON&0xF7)|LEDHOLD
	#define	LEDHOLD_RELEASE	LEDCON=(LEDCON&0xF7)

	//Bit[2:0]:LEDBRIT->LED SEG0-~3- & COM0-~3- Brightness control
	#define	LEDBRIT_0	0x00	// most darkness
	#define	LEDBRIT_1	0x01	// 
	#define	LEDBRIT_2	0x02	// 
	#define	LEDBRIT_3	0x03	// 
	#define	LEDBRIT_4	0x04	// 
	#define	LEDBRIT_5	0x05	// 
	#define	LEDBRIT_6	0x06	// 
	#define	LEDBRIT_7	0x07	// Most brightness
	
/*-----------------------------------------------------------------------------
  Bit[7]  :LEDBRTM->brightness mode control
									 0: Uniform brightness mode     (���Ⱦ���ģʽ)
									 1: Brightness enhancement mode (��������ģʽ)
	Bit[6:4]:LEDBRIT2->LED PN/BD Mode Brightness control
	                 LED���ص�33��35��37��39����
	                 LED PN Mode:LED SEG5- Brightness. 000: Most darkness, 111: Most brightness
	                 LED BD Mode:Brightness.           000: Most darkness, 111: Most brightness 
	Bit[3]  :LEDMTEN->LED BD-Mode enable control
	                 0: LED BD-Mode disable
								   1: LED BD-Mode enable	
	Bit[2:0]:LEDBRIT1->LED SEG4- Brightness control    000: Most darkness, 111: Most brightness 
	                 LED ���ص�32��34��36��38����
  -----------------------------------------------------------------------------*/
sfr		LEDCON2		= 0xB2;

  //����ģʽ
	#define LEDBRTM_Uniform 0x00	  //����ģʽ
	#define LEDBRTM_Enhance 0x80    //��ǿģʽ 
 
  //LED PN/BD Mode Brightness control
	#define	LEDBRIT2_0	0x00	// most darkness
	#define	LEDBRIT2_1	0x10	// 
	#define	LEDBRIT2_2	0x20	// 
	#define	LEDBRIT2_3	0x30	// 
	#define	LEDBRIT2_4	0x40	// 
	#define	LEDBRIT2_5	0x50	// 
	#define	LEDBRIT2_6	0x60	// 
	#define	LEDBRIT2_7	0x70	// Most brightness	
	
	//LED BD-Mode enable control
	#define LEDBD_En    0x08		
	#define LEDBD_Dis   0x00
	
	//LEDBRIT1:Bit[2:0],LED SEG4- Brightness. 
	#define	LEDBRIT1_0	0x00	// most darkness
	#define	LEDBRIT1_1	0x01	// 
	#define	LEDBRIT1_2	0x02	// 
	#define	LEDBRIT1_3	0x03	// 
	#define	LEDBRIT1_4	0x04	// 
	#define	LEDBRIT1_5	0x05	// 
	#define	LEDBRIT1_6	0x06	// 
	#define	LEDBRIT1_7	0x07	// Most brightness	

/*-----------------------------------------------------------------------------
  Bit[4:0]:ADCHS->ADC Channel Select
					 00000: AD0 (P0.4)
					 00001: AD1 (P0.5)
					 00010: AD2 (P2.0)
					 00011: AD3 (P2.1)
					 00100: AD4 (P1.0)
					 00101: AD5 (P1.1)
					 00110: AD6 (P1.2)
					 00111: AD7 (P1.3)
					 01000: AD8 (P1.4)
					 01001: AD9 (P1.5)
					 01010: AD10 (P1.6)
					 01011: VBG (Internal Bandgap Reference Voltage)
					 01100: AD12 (P1.7)
					 01101: AD13 (P2.2)
					 01110: AD14 (P2.3)
					 01111: AD15 (P2.4)
					 10000: AD16 (P2.5)
					 10001: AD17 (P0.6)
					 10010: AD18 (P0.7)
					 10011: AD19 (P0.0)
					 10100: AD20 (P0.1)
					 10101: AD21 (P0.2)
					 10110: AD22 (P0.3)
					 10111: 1/4VCC
  -----------------------------------------------------------------------------*/
sfr		ADCHS		= 0xB6;
	
/*--------------------------------------------------------------------------------------*/
sfr 	IP    		    = 0xB8;
	sbit		PT2			  = IP^5;		//��ʱ2�ж����ȼ���λ
	sbit 		PS			  = IP^4;		//���п��ж����ȼ���λ
	sbit 		PT1	    	= IP^3;		//��ʱ1�ж����ȼ���λ
	sbit 		PX1	    	= IP^2;		//���ж�INT1�ж����ȼ���λ
	sbit 		PT0	    	= IP^1;		//��ʱ0�ж����ȼ���λ
	sbit 		PX0	    	= IP^0;		//���ж�INT0�ж����ȼ���λ
	
/*--------------------------------------------------------------------------------------*/
sfr 	IPH    		      = 0xB9;
	#define		IPH_PT2H    0x20		//��ʱ2�ж����ȼ���λ       
	#define		IPH_PSH     0x10 	  //���п��ж����ȼ���λ      
	#define		IPH_PT1H    0x08	  //��ʱ1�ж����ȼ���λ       
	#define		IPH_PX1H    0x04		//���ж�INT1�ж����ȼ���λ  
	#define		IPH_PT0H    0x02		//��ʱ0�ж����ȼ���λ       
	#define		IPH_PX0H    0x01 	  //���ж�INT0�ж����ȼ���λ/*
	
/*--------------------------------------------------------------------------------------*/	
sfr 	IP1  		    = 0xBA; 
	#define		PPWM		0x80		//PWM �ж����ȼ���λ
	#define		PI2C		0x40		//I2C �ж����ȼ���λ
	#define		PS2			0x20		//UART2�ж����ȼ���λ 
	#define 	PADI		0x08		//ADC �ж����ȼ���λ
	#define		PLVD		0x04		//LVD T2�ж����ȼ���λ
	#define 	PPC			0x02		//Pin change�ж����ȼ���λ
	#define		PT3			0x01		//��ʱ3�ж����ȼ���λ
	
/*--------------------------------------------------------------------------------------*/
sfr 	IP1H   		  = 0xBB;
	#define		PPWMH		0x80		//PWM �ж����ȼ���λ
	#define		PI2CH		0x40		//I2C �ж����ȼ���λ
	#define		PS2H 		0x20		//UART2�ж����ȼ���λ
	#define 	PADIH		0x08		//ADC �ж����ȼ���λ
	#define		PLVDH		0x04		//LVD T2�ж����ȼ���λ
	#define 	PPCH		0x02		//Pin change�ж����ȼ���λ
	#define 	PT3H    0x01		//��ʱ3�ж����ȼ���λ

/*-----------------------------------------------------------------------------
  Bit[7]  :LVDPD ->LVD enable control
	                 1->LVD disable
									 0->LVD enable
	Bit[6]  :LVDO  ->LVDO control 
	                  
	Bit[3:0]:LVDSEL->LVD Select
	         1111: LVD 4.35V
					 1110: LVD 4.2V
					 1101: LVD 4.05V
					 1100: LVD 3.9V
					 1011: LVD 3.75V
					 1010: LVD 3.6V
					 1001: LVD 3.45V
					 1000: LVD 3.3V
					 0111: LVD 3.15V
					 0110: LVD 3V
					 0101: LVD 2.85V
					 0100: LVD 2.7V
					 0011: LVD 2.55V
					 0010: LVD 2.4V
					 0001: LVD 2.25V
					 0000: LVD 2.1V	
  -----------------------------------------------------------------------------*/
sfr 	LVDS   		= 0xBF;
	#define	 LVDPD	0x80	
	#define	 LVDO		0x40	

/*--------------------------------------------------------------------------------------*/
sfr 	T2CON  		= 0xC8; 
	sbit 	TF2  		= T2CON^7;		//��ʱ��T2����жϱ�־��TF2�������û������塰0������T2��Ϊ���ڲ����ʷ�����ʱ��TF2���ᱻ�á�1����
	sbit 	EXF2   	= T2CON^6;		//�ⲿ�ж�2��־��EXEN2Ϊ1ʱ����T2EX��P1.1������������ʱ��1�жϱ�־DXF2��EXF2�������û������塰0����
	sbit 	RCLK   	= T2CON^5;		//���нӿڵĽ���ʱ��ѡ���־��TCLK=1ʱ��T2������mode 1 or 3��
	sbit 	TCLK 	  = T2CON^4;		//���нӿڵķ���ʱ��ѡ���־λ��RCLK��1ʱ��T2������mode 1 or 3��
	sbit 	EXEN2  	= T2CON^3;		//�ⲿ�ж�2�����־��
	sbit 	TR2    	= T2CON^2;		//Timer2���п��ơ�0��Timer2ֹͣ��1��Timer2����
	sbit 	CT2    	= T2CON^1;		//Timer2������/��ʱ��ѡ��λ��C/T2=0ʱ��Ϊ��ʱ��ģʽ��C/T2=1ʱ��Ϊ������ģʽ��
	sbit 	CPRL2  	= T2CON^0;		//��׽�ͳ����Զ���װ�뷽ʽѡ��λ��Ϊ1ʱ�����ڲ�׽��ʽ��Ϊ0ʱT2�����ڳ����Զ���װ�뷽ʽ����TCLK��RCLKΪ1ʱ��CP/RL2�����ԣ�T2���ǹ����ڳ����Զ���װ�뷽ʽ��

/*--------------------------------------------------------------------------------------*/
sfr 	RCP2L   = 0xCA;	 //�ⲿ���루P1.1��������/�Զ���װ��ģʽʱ��ֵ�Ĵ����Ͱ�λ
sfr 	RCP2H   = 0xCB;	 //�ⲿ���루P1.1��������/�Զ���װ��ģʽʱ��ֵ�Ĵ����߰�λ
 
sfr 	TL2   	= 0xCC;	 //Timer2 Data low byte
sfr 	TH2   	= 0xCD;	 //Timer2 Data high byte

/*-----------------------------------------------------------------------------
  Write Register:
		Write 47h to enable main ROM IAP write
		Write E2h to enable EEPROM  write
		Write other value to disable IAP write
	Read Register:	
	  Bit[7]:IAPWE->IAPWE Enable Flag(only read) 	
		Bit[6]:IAPTO->IAP Time-Out flag,? H/W Auto clear when IAPWE =0
		Bit[5]:EEPWE->EEPWE Enable Flag
 -----------------------------------------------------------------------------*/
sfr	IAPWE_SFR	= 0xC9;								
	#define	IAPWE	0x80  // IAPWE Enable Flag(only read) 					
	#define	IAPTO	0x40	// IAP Time-Out flag,? H/W Auto clear when IAPWE =0
	#define	EEPWE	0x20	// EEPWE Enable Flag
 
/*--------------------------------------------------------------------------------------*/
sfr 	PSW   		= 0xD0; 
	sbit 		CY 		= PSW^7;		//��λ��־,�н����λ,CY��1;�޽����λ,CY��0
	sbit 		AC 		= PSW^6;		//���λ��־
	sbit 		F0 		= PSW^5;		//�û��������ʹ��
	sbit 		RS1 	= PSW^4;		//�����Ĵ�����ѡ��[RS1:RS0]
	sbit 		RS0 	= PSW^3;		//00--0��,01--1��,10--2��,11--3��
	sbit 		OV 		= PSW^2;		//����������������,�����,OV=1;�����,OV��0
	sbit 		F1 		= PSW^1;		//�û��Զ����־
	sbit 		P 		= PSW^0;		//������ʾALU�������ж�������λ1�ĸ�������ż��,��Ϊ����,��P=1,����Ϊ0

/*--------------------------------------------------------------------------------------*/
sfr		CLKCON		  = 0xD8;
	sbit 	SCKTYPE   = CLKCON^7;		//��ʱ������ѡ��Slow Clock Type. 1=SXT, 0=SRC
	sbit 	FCKTYPE   = CLKCON^6;		//Fast clock Type. 0=FRC, 1=FXT.
	sbit 	STPSCK 	  = CLKCON^5;		//Stop Slow Clock in PDOWN
	sbit 	STPPCK 	  = CLKCON^4;		//1=����IDLģʽ��Stop UART/Timer0/Timer1/Timer2 Clock in Idle mode
	sbit 	STPFCK 	  = CLKCON^3;		//1=ֹͣ��ʱ�ӣ�0=��ʱ�ӹ���
	sbit 	SELFCK 	  = CLKCON^2;		//1=ѡ���ʱ��Ϊϵͳʱ��Դ��0=��ʱ��Ϊϵͳʱ��Դ
	sbit 	CLKPSC_H 	= CLKCON^1;	  //Bit[1:0]->CPUCLK Prescaler
	sbit 	CLKPSC_L	= CLKCON^0;	  //0->divide 16,1->divide 4,2->divide 2,3->divide 1
	 
	#define  	SCKTYPE_SRC  	CLKCON=(CLKCON&0x7F)       // Slow Clock Type SIRC 
	#define  	SCKTYPE_SXT   CLKCON=(CLKCON&0x7F)|0x80  // Slow Clock Type SXT
	
	#define		FCKTYPE_FRC		CLKCON=(CLKCON&0x9F)       // Fast Clock Type FIRC 
	#define		FCKTYPE_FXT		CLKCON=(CLKCON&0x9F)|0x40  // Fast Clock Type FXT
	
	#define		STPSCK_OFF		CLKCON=(CLKCON&0xDF)       // Run  Slow Clock in PDOWN 
	#define		STPSCK_OPEN		CLKCON=(CLKCON&0xDF)|0x20  // Stop Slow Clock in PDOWN
	
	#define		STPPCK_OFF		CLKCON=(CLKCON&0xEF)       // Run  UART/Timer0/Timer1/Timer2/ADC Clock in Idle mode
	#define		STPPCK_OPEN		CLKCON=(CLKCON&0xEF)|0x10  // Stop UART/Timer0/Timer1/Timer2/ADC Clock in Idle mode
	
	#define		STPFCK_OFF		CLKCON=(CLKCON&0xF7)       // Run  Fast Clock
	#define		STPFCK_OPEN		CLKCON=(CLKCON&0xF7)|0x08  // Stop Fast Clock
	
	#define		SELFCK_SLOW		CLKCON=(CLKCON&0xFB)       // Select Slow Clock
	#define		SELFCK_FAST		CLKCON=(CLKCON&0xFB)|0x04  // Select Fast Clock
 
	//CLKPSC:CLKCON Bit[1:0],ϵͳʱ��Ԥ��Ƶ��SYSCLK Prescaler, 0:div16, 1:div4, 2:div2, 3:div1
	#define		CLKPSC_Mask		 ~0x03
	#define		CLKPSC_Div16		0x00
	#define		CLKPSC_Div4			0x01
	#define		CLKPSC_Div2			0x02
	#define		CLKPSC_Div1			0x03	
	
	#define		SYSCLOCK_DIV_16	CLKCON=(CLKCON&0xFC)
	#define		SYSCLOCK_DIV_4	CLKCON=(CLKCON&0xFC)|CLKPSC_Div4
	#define		SYSCLOCK_DIV_2	CLKCON=(CLKCON&0xFC)|CLKPSC_Div2
	#define		SYSCLOCK_DIV_1	CLKCON=(CLKCON&0xFC)|CLKPSC_Div1	

/*-----------------------------------------------------------------------------
 extra condition: 
 write sequence:  PWMxDL then PWMxDH
 read  sequence:  PWMxDH then PWMxDL 
  -----------------------------------------------------------------------------*/
sfr		PWM0DH		= 0xD1; // PWM0 duty high byte				
sfr		PWM0DL		= 0xD2; // PWM0 duty low byte		
sfr		PWM1DH		= 0xD3;	// PWM1 duty high byte			
sfr		PWM1DL		= 0xD4; // PWM1 duty low byte		
sfr		PWM2DH		= 0xD5; // PWM1 duty high byte				
sfr		PWM2DL		= 0xD6; // PWM1 duty low byte	

/*-----------------------------------------------------------------------------
  extra condition: 
	write sequence:  PWMxPRDL then PWMxPRDH
  read  sequence:  PWMxPRDH then PWMxPRDL 
 -----------------------------------------------------------------------------*/
sfr		PWM0PRDH	= 0xD9;	// PWM0 Period high byte			 			
sfr		PWM0PRDL	= 0xDA; // PWM0 Period low byte
sfr		PWM1PRDH	= 0xDB;	// PWM1 Period high byte								
sfr		PWM1PRDL	= 0xDC; // PWM1 Period low byte 
sfr		PWM2PRDH	= 0xDD;	// PWM2 Period high byte			
sfr		PWM2PRDL	= 0xDE; // PWM2 Period low byte	 
 
/*-----------------------------------------------------------------------------
  Bit[7]:MIEN   ->Master IIC enable
                 0->Disable
								 1->Enable	
	Bit[6]:MIACKO ->send acknowledge to IIC Bus when Master IIC receive Data  
								 0-> ACK to slave device
								 1->NACK to slave device	
	Bit[5]:MIIF   ->Master IIC Interrupt flag
	               0->H/W write 0 to clear it
								 1->Master IIC transmit or receive one byte complete
	Bit[4]:MIACKI ->acknowledgement form IIC bus (read only) When Master IIC transmission 
	               0-> ACK received
								 1->NACK received
	Bit[3]:MISTART->Master IIC Start Bit,1->start IIC bus transmit
	                period of MISTART=0 must longer than a IIC clock period					 
	Bit[2]:MISTOP -> Master IIC Stop Bit,1->send STOP signal to stop IIC bus					 
	Bit[1:0]:MICR ->Frequency select
               00: Fsys/4    (ex. If Fsys=16MHz, IIC clock is    4M Hz)
							 01: Fsys/16   (ex. If Fsys=16MHz, IIC clock is    1M Hz)
							 10: Fsys/64   (ex. If Fsys=16MHz, IIC clock is  250K Hz)
							 11: Fsys/256  (ex. If Fsys=16MHz, IIC clock is 62.5K Hz)"	
  -----------------------------------------------------------------------------*/
sfr 	MICON     = 0xE1;		 
	#define	MIEN	  0x80 // Master IIC enable,0->disable,1->enable
	#define	MIACKO  0x40 // send acknowledge to IIC Bus when Master IIC receive Data 		 
	#define	MIIF	  0x20 // Master IIC Interrupt flag 
	#define	MIACKI  0x10 // acknowledgement form IIC bus (read only) 
  #define	MISTART 0x08 // Master IIC Start Bit,1->start IIC bus transmit
	#define	MISTOP  0x04 // Master IIC Stop Bit, 1->send STOP signal to stop IIC bus"
	
/*-----------------------------------------------------------------------------
  Master IIC Data shift Register:
  (W): resume trasmission to IIC bus after Start and before Stop condition 	     
	(R): resume receiving from IIC bus after Start and before Stop condition 
  -----------------------------------------------------------------------------*/
sfr 	MIDAT   		= 0xE2;	  
 	
/*-----------------------------------------------------------------------------
  Bit[7:8]:SA ->Write I2C Slave address assigned
                 Read  address received at I2C Slave
	Bit[0]:SIEN ->Slave IIC enable,0->Disable,1->Enable
  -----------------------------------------------------------------------------*/
sfr 	SIADR   		= 0xE9;	
	#define		SIEN		0x01	// Slave IIC enable,0->Disable,1->Enable

/*-----------------------------------------------------------------------------
  Bit[7]:MIIE  ->I2C Master INT enable 
                 0->Disable
								 1->Enable	
	Bit[6]:TXDIE ->I2C Slave Data transmit INT enable
								 0->Disable
								 1->Enable	
	Bit[5]:RCD2IE->I2C Slave SIRCD2 receive INT enable
	               0->Disable
								 1->Enable 
	Bit[4]:RCD1IE->I2C Slave SIRCD1 receive INT enable
	               0->Disable
								 1->Enable	
	Bit[2]:TXDF  ->I2C Slave Data transmit INT flag
	               it will not transmit SITXD Data and return NACK while 1
								 Set by H/W when Slave IIC SITXD transmit one byte complete,S/W write 0 to clear it
	Bit[1]:RCD2F ->I2C Slave Data received INT flag
	               it will not receive SITXD Data and return NACK while 1
								 Set by H/W when Slave IIC SITXD receive one byte complete,S/W write 0 to clear it
	Bit[0]:RCD1F ->I2C Slave Data received INT flag
	               it will not receive SIRCD1 Data and return NACK while 1
	               Set by H/W when Slave IIC RCVD1 receive one byte complete,S/W write 0 to clear it
  -----------------------------------------------------------------------------*/
sfr 	SICON    = 0xEA;	
	#define	MIIE	 0x80 // I2C Master INT enable Bit
	#define	TXDIE	 0x40 // I2C Slave Data transmit INT enable
	#define	RCD2IE 0x20 // I2C Slave SIRCD2 receive INT enable
	#define	RCD1IE 0x10 // I2C Slave SIRCD1 receive INT enable
	#define	TXDF	 0x04 // I2C Slave Data transmit INT flag              
	#define	RCD2F	 0x02 // I2C Slave Data received INT flag 
	#define	RCD1F	 0x01 // I2C Slave Data received INT flag, 

/*--------------------------------------------------------------------------------------*/
sfr 	SIRCD1   = 0xEB; // Slave IIC Data receive register1,only read
sfr 	SITXRCD2 = 0xEC; // Slave IIC Data transmit and receive Register (Data-out/in),R/W
		              
/*--------------------------------------------------------------------------------------
  Bit[5:3]:TM3PSC->Timer3 Int Prescale
	         000->32768*Clk  
					 001->16384*Clk  
					 010-> 8192*Clk  
					 011-> 4096*Clk
	         100-> 2048*Clk
					 101-> 1024*Clk  
					 110->  512*Clk  
					 111->  256*Clk 
  Bit[2]  :VBG/VBGO enable control Bit
	         1->Force VBG/VBGO to be enabled, included in IDLE mode, but disabled in stop mode
					 0->VBG/VBGO disable at IDLE and STOP mode
	Bit[1:0]:ADC Vref select Bit
	         00->ADC Vref is VCC
					 01->ADC Vref is 2.5V
					 10->ADC Vref is 3V
					 11->ADC Vref is 4V
  --------------------------------------------------------------------------------------*/
sfr 	AUX3   		= 0xEF;		

	#define	TM3PSC  0x38 // Bit[5:3],Timer3 Int Prescale. 
	#define	VBGEN	  0x04 // Bit[2]  ,VBG/VBGO enable control Bit
	#define	ADVREFS 0x03 // Bit[1:0],ADC Vref select Bit
	
	#define VBGEN_ENABLE	AUX3=(AUX3&0xFB)|VBGEN  // 1->Force VBG/VBGO to be enabled, included in IDLE mode, but disabled in stop mode
	#define VBGEN_DISABLE	AUX3=(AUX3&0xFB)        // 0->VBG/VBGO disable at IDLE and STOP mode
	
	#define	SET_ADVREFS_00	AUX3=(AUX3&0xFC)      // 00->ADC Vref is VCC
	#define	SET_ADVREFS_01	AUX3=(AUX3&0xFC)|0x01	// 01->ADC Vref is 2.5V
	#define	SET_ADVREFS_02	AUX3=(AUX3&0xFC)|0x02	// 10->ADC Vref is 3V
	#define	SET_ADVREFS_03	AUX3=(AUX3&0xFC)|0x03	// 11->ADC Vref is 4V
 
/*--------------------------------------------------------------------------------------*/
sfr 	TESTMODE    = 0xF4;// Will not display on datasheet, TEST ONLY
	#define	TSTREG_5	0x20 // 0->High Sink setting by HSNKxEN,1->All pin force enable  High Sink
	#define	TSTREG_4	0x10 // 0->LEDDRV is controled by LEDEN,1->force LEDDRV=1,
	#define	TSTREG_3	0x08 // 0->EEPROM Read and wait 5 clock;1->disable EEPROM read delay (for test EEPROM access time)"
	#define	TSTREG_2	0x04 // 0->POR always enable,1->disable POR and force PORPD=1
	
/*--------------------------------------------------------------------------------------
	Bit[7:6]:WDT_EN -> WDT Enable Control
					 11->WDT Always Enable
					 10->WDT Enable in Fast/Slow, Disable in Idle/Stop mode
					 0x->WDT Disable
	Bit[5]  :PWRSAV -> LVR Enable Control	
           1->LVR disable at IDLE/PDOWN, 
					 0->LVR enable at IDLE/PDOWN	
	Bit[4]  :VBGOUT -> VBGOUT output Control
	         1->VBG output to P3.2,   
					 0->P32 as normal IO
	Bit[3]  :DIV32    -> insturction div division operation,only active when MULDVI16 =1 
           1->as 32/16 Bit 
					 0->as 16/16 Bit  	
	Bit[2:1]:IAPTE    -> IAP TIMEOUT Enable Control 
					 00->IAP TIMEOUT Disable
					 01->IAP TIMEOUT 2.8mS 
					 10->IAP TIMEOUT  11mS
					 11->IAP TIMEOUT  22mS	
	Bit[0]  :MULDIV16 -> instruction mul/div operation  
	         1->as 16*16 or 16/16 or 32/16, 
					 0->as 8*8 or 8/8  											
  --------------------------------------------------------------------------------------*/
sfr 	AUX2		   = 0xF7;
 
	#define WDT_EN	 0xC0	// Bit[7:6],WDT Control	
	#define	PWRSAV	 0x20 // 1->LVR disable,0->LVR enable,at IDLE/PDOWN
	#define	VBGOUT	 0x10	// 1->VBG output to P3.2, 0->P32 as normal IO,(extra condition: VBGEN =1 or ADCHS=1011b or ADVREFS��00b)
	#define	DIV32		 0x08	// 1->as 32/16 Bit,0->as 16/16 Bit,insturction div division operation only active when MULDVI16 =1
	#define IAPTE    0x06	// Bit[2:1],IAP TIMEOUT Enable											
	#define	MULDIV16 0x01	// 1->as 16*16 or 16/16 or 32/16, 0->as 8*8 or 8/8, instruction mul/div operation 											
	
	#define WDT_IS_OPEN           AUX2=(AUX2&0x3F)|0xC0	// 11��WDT Always Enable
	#define WDT_RUN_FAST_DIS_ILDE AUX2=(AUX2&0x3F)|0x80	// 10: WDT Enable in Fast/Slow, Disable in Idle/Stop mode
	#define WDT_IS_STOP           AUX2=AUX2&0x3F  	  	// 0x: WDT Disable
	
	#define	PDOWN_LVD_ENABLE	    AUX2=(AUX2&0xDF)         // 0->LVR  enable at IDLE/PDOWN
	#define	PDOWN_LVD_DISABLE   	AUX2=(AUX2&0xDF)|PWRSAV  // 1->LVR disable at IDLE/PDOWN
 	
	#define	VBG_OUTPUT	  AUX2=(AUX2&0xEF)|VBGOUT      // 1->VBG output to P3.2
	#define	VBG_NORMAL	  AUX2=(AUX2&0xEF)             // 0->P32 as normal IO

	#define	IAPTE_DISABLE	AUX2=(AUX2&0xF9)             // 00->IAP TIMEOUT Disable
	#define	IAPTE_2P8_MS	AUX2=(AUX2&0xF9)|0x02        // 01->IAP TIMEOUT 2.8mS
	#define	IAPTE_11_MS		AUX2=(AUX2&0xF9)|0x04        // 10->IAP TIMEOUT  11mS
	#define	IAPTE_22_MS		AUX2=(AUX2&0xF9)|0x06        // 11->IAP TIMEOUT  22mS			

/*--------------------------------------------------------------------------------------*/
sfr 	AUX1   		= 0xF8; 
  sbit 	CLRWDT	= AUX1^7;	 //Clear WatchDog, HW Auto clear    
	sbit 	CLRTM3	= AUX1^6;  //����TM3Ҳ������TM3
  sbit 	ADSOC		= AUX1^4;  //ADC��ʼ������ʱӲ���Զ�����
  sbit 	LVRPD		= AUX1^3;  //1: LVR disable, 0: LVR enable
  sbit 	T2SEL		= AUX1^2;  //Timer2 counter mode input, 0=P1.0 pin, 1=SLOWCLK/16
  sbit 	T1SEL		= AUX1^1;  //Timer1 counter mode input, 0=P3.5 pin, 1=SLOWCLK/16
  sbit 	DPSEL		= AUX1^0;  //0��ѡ��DPTR;1��ѡ��DPTR1
#define  CLR_WDT  CLRWDT=1 //������������Ź���ʱ��,H/W�Զ���һ��ʱ�����������     	

/*--------------------------------------------------------------------------------------*/
sfr 	ICECON 	      = 0xF9;
	#define 	HWBRK		  0x80		//H/W Break
	#define 	RETROREQ  0x40		//Retro-OPCode Request,HW set at SWBRK,clear at NMI return
	#define 	TXRDY		  0x20		//Transmitt Ready
	#define 	CMDRDY	  0x10		//Ready for Command
	#define 	XFIRCK	  0x08		//Swich to FIRC 4MHZ
	#define 	WRFAIL	  0x01		//EEPROM Write Fail

/*--------------------------------------------------------------------------------------*/
sfr  PCL   = 0xED; //Bit[7:0],PC counter LSB 7~0,Will not display on datasheet, TEST ONLY
sfr  PCH   = 0xEE; //Bit[7:0],PC counter MSB 7~0,Will not display on datasheet, TEST ONLY

sfr  EXA2  = 0xCE;   // Bit[7:0],extra ACC for 32/16 Bit division operation 
sfr  EXA3  = 0xCF;   // Bit[7:0],extra ACC for 32/16 Bit division operation
sfr  EXA   = 0xE6;	 // Bit[7:0],extra ACC for 16 Bit mul/div operation
sfr  EXB   = 0xE7;	 // Bit[7:0],extra B   for 16 Bit mul/div operation
sfr  ACC   = 0xE0;	 // Accumulator

sfr  CFGBG  	= 0xF5; // Bit[4:0]->BGTRIM,VBG trimming value
sfr  CFGWL   	= 0xF6; // Bit[6:0]->FRCF  ,FRC freq
   
sfr  B   		  = 0xF0;	// B Register 
sfr  CRCDL    = 0xF1; // Bit[7:0],CRC16 Data 7~0 
sfr  CRCDH    = 0xF2; // Bit[7:0],CRC16 Data 15~8 
sfr  CRCIN  	= 0xF3; // Bit[7:0],CRC16 input

sfr  RETROCODE = 0xFA;	//ICE Mode Retro-OPCode
sfr  ICERCD 	 = 0xFB;	//ICE Mode Receive Data
sfr  ICECMDL	 = 0xFC;	//ICE Mode Command Low Byte
sfr  ICECMDH	 = 0xFD;	//Bit[3:0],ICE Mode Command High Byte
sfr  ICETXD		 = 0xFE;	//ICE Mode Transmit Data
sfr  INDSFR		 = 0xFF;	//SFR direct Adr replaced by ICECMDL in NMI "mov dir,a" & "mov a,dir"

/*--------------------------------------------------------------------------------------*/
#define	 All_Interrupt_Enable()		EA = 1		//ȫ���ж�ʹ��
#define	 All_Interrupt_Disable()	EA = 0		//ȫ���жϹر�
 
#define	 PowerDown()			PCON = PCON | PD	//�������ģʽ
#define	 PowerIdel()			PCON = PCON | IDL	//����IDELģʽ

/*--------------------------------------------------------------------------------------*/
#endif
