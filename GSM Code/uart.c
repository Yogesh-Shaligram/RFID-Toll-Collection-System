/*--------------------------------------------------------------------------------
   8051 UART library for Serial Communication at 9600 baud rate
   with the crystal frequency 11.0592MHz
 
Filename: uart.c
Controller: P89V51RD2/89c51(8051 family)
Oscillator: 11.0592 MHz
Author: XploreLabz
website: www.xplorelabz.com 
 ---------------------------------------------------------------------------------*/
 
 
 #include<reg51.h>
 #include"uart.h"
 
 
/*-------------------------------------------------------------------------------
                         void UART_Init()
----------------------------------------------------------------------------------
 * I/P Arguments: none.
 * Return value : none
 
 * description  :This function is used to initialize the UART at 9600 baud rate
                  by below configuration.
    1.Timer 1 is run in Mode2(auto reload mode) to generate the required Baud Rate.
    2.9600 baud rate is generate by loading -3(0XFD) in TH1 register.
    3.SCON is configured in MODE1 ie. 8bit Data 1-Start and 1-Stop bit.
    4.Finally the timer is turned ON by setting TR1 bit to generate the baud rate.
----------------------------------------------------------------------------------*/
void UART_Init()
{
      TMOD |=0x20; //Timer1 in Mode2.
      TH1=-3;    // 9600 Baud rate at 11.0592MHz
      SCON=0x50; // Asynchronous mode 8-bit data and 1-stop bit
			IE=0x90;	//	EA=1;ES=1;      //Enable serial interrupt
			TR1=1;     //Turn ON the timer.
  }
 
 
 
 
 
/*----------------------------------------------------------------------------------
                              char UART_RxChar()
  ----------------------------------------------------------------------------------
 * I/P Arguments: none.
 * Return value : char
 
 * description :This function is used to receive a char from UART module.
                It waits till a char is received ie.till RI is set,
                RI will be set once a CHAR is received.
              Finally it clears the RI for next cycle and returns the received char.
----------------------------------------------------------------------------------_*/
char UART_RxChar()
{
  while(RI==0);   // Wait till the data is received
     RI=0;        // Clear Receive Interrupt Flag for next cycle
  return(SBUF);   // return the received char
}
 
 

/*----------------------------------------------------------------------------------
                         void UART_TxChar(char ch)
------------------------------------------------------------------------------------
 * I/P Arguments: char--> data to be transmitted.
 * Return value : none.
 
 * description  :This function is used to transmit a char through UART module.
                 The Char to be transmitted is loaded into SBUF.
                 It waits till char is transmitted ie.till TI is set.
                 TI will be set once a CHAR is transmitted.
                 Finally it clears the TI for next operation.
 ----------------------------------------------------------------------------------*/
 void UART_TxChar(char ch)
{
    SBUF=ch;       // Load the data to be transmitted
  while(TI==0);    // Wait till the data is trasmitted
     TI=0;         //Clear the flag for next cycle.
}
 
 
 
 
 
 
 
 
 
/*----------------------------------------------------------------------------------
                         void UART_TxString(char *string_ptr)
 -----------------------------------------------------------------------------------
 * I/P Arguments: String(Address of the string) to be transmitted.
 * Return value : none
 
 * description :This function is used to transmit the ASCII string through UART..
                The string_ptr points to the first char of the string.
                And it is incremented each time to traverse till the end(NULL CHAR).
               Each time a char is sent to UART_TxChar() fun to transmit it through UART
----------------------------------------------------------------------------------_*/
void UART_TxString(char *string_ptr)
 {
          while(*string_ptr)
           UART_TxChar(*string_ptr++);
   }
 
 
 
/*---------------------------------------------------------------------------------
                         void UART_RxString(char *string_ptr)
 ----------------------------------------------------------------------------------
 * I/P Arguments: *string_ptr
                   Address of the string where the received data needs to be stored
 * Return value : none
 
 * description  :
                1.This function is used to receive a ASCII string through UART
                  till the carriage_return/New_line
                2.The string_ptr points to the begining of the string and each
                  time UART_RxChar() function is called to receive a char and copy
                  it into the buffer(STRING) and incrment string_ptr.
                3.Once the carriage_return/New_line is encountered the loop
                  is breaked and the String is NULL terminated.
 
 *****NOTE*******:
  1.The received char is ECHOED back,
    if not required then comment UART_TxChar(ch) in the code.
  2.BackSlash is not taken care.
----------------------------------------------------------------------------------_*/
void UART_RxString(char *string_ptr)
 {
     char ch;
     while(1)
       {
          ch=UART_RxChar();    //Reaceive a char
          UART_TxChar(ch);     //Echo back the received char
 
         if((ch=='\r') || (ch=='\n')) //read till enter key is pressed
           {                          //once enter key is pressed
              *string_ptr=0;          //null terminate the string
                break;                //and break the loop
             }
         *string_ptr=ch;              //copy the char into string.
         string_ptr++;                //and increment the pointer
      }
 }
 
  
/*----------------------------------------------------------------------------------
                      void  UART_TxNumber(unsigned int num)
------------------------------------------------------------------------------------
 * I/P Arguments: unsigned int.
 * Return value : none
 
 * description  :This function is used to transmit a 5-digit integer(0-65535).
                 ex: if the number is 12345 then 12345 is transmitted.
                     if the number is 123 then 00123 is transmitted.
 
 
 ----------Take 1 by dividing by 10000 and add 0X30 to obtain the ASCII value,
|          then take the 4-digit remainder(2345).
|
| ---------Take 2 by dividing by 1000  and add 0X30 to obtain the ASCII value,
||         then take the 3-digit remainder(345)
||
|| --------Take 3 by dividing by 100   and add 0X30 to obtain the ASCII value,
|||        then take the 2-digit remainder(45).
|||
||| -------Take 4 by dividing by 10    and add 0X30 to obtain the ASCII value,
|||| ------Take 5 the remainder of 45  and add 0X30 to obtain the ASCII value,.
|||||
12345
------------------------------------------------------------------------------------*/
 
void UART_TxNumber(unsigned int num)
{
 
       UART_TxChar((num/10000)+0x30);
       num=num%10000;
 
       UART_TxChar((num/1000)+0x30);
       num=num%1000;
 
       UART_TxChar((num/100)+0x30);
       num=num%100;
 
       UART_TxChar((num/10)+0x30);
 
       UART_TxChar((num%10)+0x30);
}
  