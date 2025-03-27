
#include <intrins.h>

#include "REGtenxTM52F1376.h"

#include "TM52F1376_calc_bsp.h"


/* 中间值定义成全局变量，不用定义局部变量节省时间 
 * 使用时，该函数是不可重载函数，需要特别注意不能在中断和主函数中同时使用
 * 建议使用该函数前关闭中断 
 */
calc_mid_t clac_mid;
unsigned char mid_1,mid_2;

/*-------------------------------------------------------------------------
  16bit无符号数  乘以 16bit 无符号数
  返回结果为32bit 无符号数
  -------------------------------------------------------------------------*/
unsigned long mul_32(unsigned int a,unsigned int b)
{
	clac_mid.us16[0] = a;			   
	mid_1 = clac_mid.us8[1];	  
	EXA   = clac_mid.us8[0];
	
	clac_mid.us16[0] = b;			   
	mid_2 = clac_mid.us8[1];	  
	EXB   = clac_mid.us8[0];
	
	AUX2 = (AUX2&0xf6)|0x1;

	clac_mid.tt.us12 = mid_1*mid_2;
	clac_mid.tt.us3 = EXA;
	clac_mid.tt.us0 = EXB;
	AUX2 = (AUX2&0xf6);
	return clac_mid.us32;
}

/*-------------------------------------------------------------------------
  16bit 无符号数   除以  16bit无符号数 
  返回结果为 16bit无符号数
  -------------------------------------------------------------------------*/
unsigned int div_16(unsigned int a, unsigned int b)
{
//	calc_mid_t clac_mid;
//	unsigned char mid_1,mid_2;

	clac_mid.us16[0] = a;	   			   
	mid_1 = clac_mid.us8[1];		   	  
	EXA = clac_mid.us8[0];	
	clac_mid.us16[0] = b;	   			   
	mid_2 = clac_mid.us8[1];		   	  
	EXB = clac_mid.us8[0];
	
	AUX2 = (AUX2&0xf6)|0x1;		   
	clac_mid.us8[0] = mid_1/mid_2;		   
	clac_mid.us8[1] = EXA;
	AUX2 = (AUX2&0xf6);
	return clac_mid.us16[0];			
}
 
/*-------------------------------------------------------------------------
  32bit 无符号数   除以  16bit无符号数 
  返回结果为 32bit无符号数
  -------------------------------------------------------------------------*/
unsigned long div_32(unsigned long a,unsigned int b)
{
//	calc_mid_t clac_mid;
//	unsigned char mid_1,mid_2;

	clac_mid.us32 = a;		   
 	mid_1 = clac_mid.us8[3];		   
	EXA = clac_mid.us8[2];		   		   
	EXA2 = clac_mid.us8[1];		   	   
	EXA3 = clac_mid.us8[0];		   	
	clac_mid.us16[0] = b;	   			   
	mid_2 = clac_mid.us8[1];		   	  
	EXB = clac_mid.us8[0];		   
	AUX2 = (AUX2&0xf6)|0x9;	
		   			   
	clac_mid.us8[0] = mid_1/mid_2;
  
	clac_mid.us8[1] = EXA;		   
	clac_mid.us8[2] = EXA2;		   
	clac_mid.us8[3] = EXA3;		   		   
	AUX2 = (AUX2&0xf6);	
	return clac_mid.us32;		   
}

unsigned int mod_32(unsigned long a,unsigned int b)
{
	clac_mid.us32 = a;		   
 	mid_1 = clac_mid.us8[3];		   
	EXA = clac_mid.us8[2];		   		   
	EXA2 = clac_mid.us8[1];		   	   
	EXA3 = clac_mid.us8[0];		   	
	clac_mid.us16[0] = b;	   			   
	mid_2 = clac_mid.us8[1];		   	  
	EXB = clac_mid.us8[0];		   
	AUX2 = (AUX2&0xf6)|0x9;	
		   			   
	clac_mid.us8[0] = mid_1%mid_2;  
	clac_mid.us8[1] = EXB;		   
//	clac_mid.us8[2] = EXA2;		   
//	clac_mid.us8[3] = EXA3;		   		   
	AUX2 = (AUX2&0xf6);	
	return clac_mid.us16[0];		   
}














