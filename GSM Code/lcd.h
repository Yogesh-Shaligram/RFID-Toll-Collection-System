
#include<reg51.h>
void LCD_Init();
void LCD_Clear();
void LCD_GoToLineOne();
void LCD_GoToLineTwo();
void LCD_GoToXY(char row, char col);
void LCD_CmdWrite( char cmd);
void LCD_DataWrite( char dat);
void LCD_DisplayString(char *string_ptr);
void LCD_DisplayNumber(unsigned int num);
void LCD_ScrollMessage(char *msg_ptr);
void LCD_DisplayRtcTime(char hour,char min,char sec);
void LCD_DisplayRtcDate(char day,char month,char year);
 