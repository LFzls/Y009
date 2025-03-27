#ifndef __HTX3736Z_CALC_BSP_H__
#define __HTX3736Z_CALC_BSP_H__

typedef union
{
	unsigned long int us32;
	unsigned int      us16[2];
	unsigned char     us8[4];
	struct
	{
		unsigned char us0;
		unsigned int us12;
		unsigned char us3;
	}tt;
}calc_mid_t;

unsigned int  div_16(unsigned int  a,unsigned int b);
unsigned long mul_32(unsigned int  a,unsigned int b);

unsigned long div_32(unsigned long a,unsigned int b);
unsigned int  mod_32(unsigned long a,unsigned int b);

#endif
