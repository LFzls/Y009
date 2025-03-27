//module.c
//
#include "Global.h"
/*--------------------------------------------------------------*/
void AdcInitialize(void)
{
	uint8_t TempR;
	TempR = OPTION & 0xF3;
	OPTION = (TempR | AdcClkPsc_32);
	AUX3 = (AUX3&0xfc | 0x04);		//select vcc as ref, enable VBG.
}
/*--------------------------------------------------------------*/
uint16_t  ADCModule(uint8_t AdcChannel,uint8_t AdcNumber)
{
//	uint8_t TempR8;
	uint16_t ADResult;	
//	OPTION = (OPTION & ~OPTION_ADCKS_MASK) | AdcClkPsc_8;//AdcClkPsc_16;   // ADC 时钟频率选择 Fsysclk/32 
	ADCHS  = (ADCHS & 0xE0) | AdcChannel ;             // ADC Channel Select
//	AUX3   = (AUX3 & 0xFE) | 0x04 | ADC_Vref_VCC ;      // ADC 参考电压  vcc	

	ADResult = ADCRead(AdcNumber);
	return ADResult;
}
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
uint16_t ReadAdResult(uint8_t AdcChannel)
{
	uint16_t ad_temp;
//	OPTION = (OPTION &~ OPTION_ADCKS_MASK) | AdcClkPsc_8;//AdcClkPsc_16;   // ADC 时钟频率选择 Fsysclk/32 
//	ADCHS  = (ADCHS &~ ADCHS_MASK) | AdcChannel ;             // ADC Channel Select
//	AUX3   = AUX3=(AUX3&0xfc);//(AUX3 & ~AUX3_ADVREFS_MASK) | ADC_Vref_VCC ;      // ADC 参考电压  vcc	
	ADCHS  = (ADCHS & 0xE0) | AdcChannel ;             // ADC Channel Select
	AUX3   = (AUX3 & 0xFE) | 0x04 | ADC_Vref_VCC ;      // ADC 参考电压  vcc	
	ADSOC = 1;                   // ADC Start      
	while(ADSOC);                // wait ADC finish
	ad_temp  = ADCDH<<4;  
	ad_temp |= ADCDL >>4; 
	return ad_temp;
}
/*----------------------------------------------------------------------------*/
uint16_t ADCRead(uint8_t AdcNumber)
{
	uint8_t i;
	uint16_t max, min, ad_temp,templ,temph;
	uint32_t sum;
    max = 0x00;
    min = 0xfff;
    sum = 0x00;
    
    for (i=0; i<2; i++)
    {
			ADSOC = 1;                
			while(ADSOC);           
			templ = ADCDL;
			temph = ADCDH;         
    }	
    for (i=0; i<AdcNumber; i++)
    {
		ADSOC = 1;                
		while(ADSOC);           
		templ = ADCDL;
		temph = ADCDH;         
		ad_temp  = (temph<<4) &0xff0;
		ad_temp  |= templ>>4;
	  if (ad_temp > max) { max = ad_temp;}
	  if (ad_temp < min) { min = ad_temp;}
	  sum += (uint32_t)ad_temp;
    }
		if(AdcNumber>2)
		{
			sum -= min;
			sum -= max;
			sum /= (AdcNumber-2);
			ad_temp=(uint16_t)sum;
		}
		else { sum /= AdcNumber;ad_temp=(uint16_t)sum;}
		return ad_temp;
}
