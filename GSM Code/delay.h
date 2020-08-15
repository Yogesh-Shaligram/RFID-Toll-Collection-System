/*----------------------------------------------------------------------------------
                      8051 delay library  with the crystal frequency 11.0592MHz
Filename: delay.c
Controller: P89V51RD2/89c51(8051 family)
Oscillator: 11.0592 MHz
Author: XploreLabz
website: www.xplorelabz.com 
 ----------------------------------------------------------------------------------*/
 
 
#include<reg51.h>
 
void delay_us(unsigned int us_count);
void delay_ms(unsigned int ms_count);
void delay_sec(unsigned char sec_count);
