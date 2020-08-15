/*---------------------------------------------------------------------------------------
                      8051 RFID with the crystal frequency 11.0592MHz
Projectname: RFID
Controller: P89V51RD2/89c51(8051 family)
Oscillator: 11.0592 MHz
Author: Ashish More
Dare :21/1/2017
Description: Take RFID number through serial and compared with stored number and 
							do operarion in main. When flag equals to 1 serial interrupt turned off.
							When operation overs and coming out of flag serial interrupt gets start.

 ---------------------------------------------------------------------------------------*/
 
 
#include<reg51.h>
#include"lcd.h"
#include"delay.h"
#include"uart.h"
#include"string.h"
//void *memset(void *str, int c, size_t n);
void gsm_init(void);
void send_msg(char a);
// char at[]="AT";
// char at1[]="AT+CSMP=49,167,0,0";
// char at2[]="AT+CNMI=2,2,0,1,0";
// char at3[]="AT+CMGS=";
// char at4[]="9960945467";
 //char CtrlZ=0x1A;
 
 char mobnocnt1,k;
// char MSG1[]="Rs.25 Thank you";
// char MSG2[]="Rs.50 Thank you";
//char MSG3[]="Reject. PayCash";
sbit ir=P1^5;
sbit motor=P3^7;
sbit buzzer=P2^0;
    
char RecvBuffer[15];   //Buffer to store serial data
char i=0,isr_flag=0;
char rfid1[]="87"; //Store rfid number A
char rfid2[]="A6"; //Store rfid number B
char rfid3[]="10"; //Store rfid number C
int main(void)
{
	buzzer=0;
	motor=0;
	//buzzer=1;
	LCD_Init();		// Initialise LCD
	delay_ms(1);
		LCD_CmdWrite(0x80);
	LCD_DisplayString("Welcome to ");
		LCD_CmdWrite(0xC0);
	LCD_DisplayString("Auto.TOLL PLAZA");
	delay_ms(1);
	UART_Init();			//initialise uart with interrupt
	delay_sec(6);
	gsm_init();
	LCD_CmdWrite(0x01);delay_ms(2);
	while(1)
	{
		
	
//		if(ir!=1)
//		{motor=1;}
//		else 
//			{motor=0;}
		//if(ir!=1)
		{
						//LCD_CmdWrite(0x01);delay_ms(2);
							LCD_CmdWrite(0x80);delay_ms(2);
						LCD_DisplayString("Swap ur card");
						
					
		if(isr_flag==1)
		{
			IE=0x00;	//	EA=0;ES=0;      //Dnable serial interrupt
			if(strstr (RecvBuffer,rfid1)!=0) //Compare received data with stored data
			{
				
				/********************
				Write operation here
				*********************/
			//	LCD_CmdWrite(0xC0);delay_ms(2);delay_ms(2);
			//	LCD_DisplayString(RecvBuffer);
				LCD_CmdWrite(0x01);
				LCD_CmdWrite(0x84);
				LCD_DisplayString("Thank you ");
				LCD_CmdWrite(0xC3);
				LCD_DisplayString("Rs. 25 paid");
				send_msg(1);
				motor=1;
				delay_ms(200);
				motor=0;
				
				//LCD_DisplayString("Thank you Rs.25");
				delay_ms(2);delay_sec(6);
				LCD_CmdWrite(0x01);
				//UART_TxString(RecvBuffer);					// Transmitting data serialy
			}
			else if(strstr (RecvBuffer, rfid2)!=0)//Compare received data with stored data
			{
				
				/********************
				Write operation here
				*********************/
				//LCD_CmdWrite(0xC0);delay_ms(2);delay_ms(2);
			//	LCD_DisplayString(RecvBuffer);
				LCD_CmdWrite(0x01);
				LCD_CmdWrite(0x84);
				LCD_DisplayString("Thank you ");
				LCD_CmdWrite(0xC3);
				LCD_DisplayString("Rs. 50 paid");
				motor=1;
				delay_ms(200);
				motor=0;
				//LCD_DisplayString("Thank you Rs.50");
				delay_ms(2);delay_sec(6);
				LCD_CmdWrite(0x01);
				send_msg(2);
				//UART_TxString(RecvBuffer);		// Transmitting data serialy
			}
			else if(strstr (RecvBuffer, rfid3)!=0)
			{
				
				/********************
				Write operation here
				*********************/
				//	LCD_CmdWrite(0xC0);delay_ms(2);delay_ms(2);
			//	LCD_DisplayString(RecvBuffer);
				LCD_CmdWrite(0x01);
				LCD_CmdWrite(0x80);
				
				LCD_DisplayString("Insufficient Bal");
				LCD_CmdWrite(0xC3);
				LCD_DisplayString("Pay By Cash");	
				send_msg(3);
				buzzer=1;
				delay_sec(5);
				buzzer=0;				
				//LCD_DisplayString("Reject Pay Cash");
				delay_ms(2);//delay_sec(6);
				while(ir!=0);
				
				
				LCD_CmdWrite(0x01);
				LCD_CmdWrite(0x84);
				LCD_DisplayString("Thank you ");
				LCD_CmdWrite(0xC3);
				LCD_DisplayString("Cash Recieved");
				motor=1;
				delay_ms(200);
				motor=0;
				delay_sec(5);
				LCD_CmdWrite(0x01);
			}
			//LCD_CmdWrite(0xC0);
			//LCD_DisplayString("                ");
			memset  (RecvBuffer,0,15);
			isr_flag=0;
			IE=0x90;	//	EA=1;ES=1;      //Enable serial interrupt
		}
	}
	}
}

void Receiver_isr() interrupt 4
{
	volatile char Rx_Buffer=0;
	if(RI)					//If RI==1
	{
		Rx_Buffer=SBUF;   //Store bit in char
		RecvBuffer[i]=Rx_Buffer;	//Store received char in array 
		i++;
		if(i>=12)					
		{
			isr_flag=1;		//Set flag
			i=0;
		}
		RI=0;
		//UART_TxChar(Rx_Buffer);		//transmit char which is receiving.
	}
}


void gsm_init()
{
	UART_TxString("AT");                                                              //Send AT command on terminal
	delay_ms(200);
	
	UART_TxChar(0x0D);                                                       //For ENTER 
  delay_ms(200);
	UART_TxString("AT+CMGF=1");                                        		//Command for message format int text
	delay_ms(50);
	UART_TxChar(0x0D);
 	delay_ms(200);
}//End of gsm

void send_msg(char a)
{
	UART_TxString("AT+CSCS=\"GSM\"");	                                           //GSM 7 bit default alphabet
	delay_ms(100);
  UART_TxChar(0x0D);
 	delay_ms(300);
  UART_TxString("AT+CMGS=\"9881759638\"");			//9881759638
	delay_ms(100);
	UART_TxChar(0x0D);
	delay_ms(300);
	delay_ms(200);
	switch(a)
	{
		case 1:
			UART_TxString("Your Account has been debited Rs.25");
		break;
		case 2:
			UART_TxString("Your Account has been debited Rs.25");
		break;
		case 3:
			UART_TxString("Low Balance");
		break;
	}
	delay_ms(300);
	
	UART_TxChar(0x0D); 
	delay_ms(300);
	delay_ms(300);
	delay_ms(300);
	UART_TxChar(0x1A);
	delay_ms(300);
	delay_ms(200);
	UART_TxChar(0x0D);
	delay_ms(300);
	delay_ms(300);
	delay_ms(300);
	delay_ms(300);
}//End of send msg

////void gsm_init()
////{
//////// UART_TxChar(at);
////////	delay_ms(100);delay_ms(100);	delay_ms(100);delay_ms(100);
////////	UART_TxChar(at1);
////////	delay_ms(100);delay_ms(100); 	delay_ms(100);delay_ms(100);
////////	UART_TxChar(at2);
////////	delay_ms(100);delay_ms(100);	delay_ms(100);delay_ms(100);
////////	UART_TxChar(at3);
////////	UART_TxChar('"');
////////		UART_TxChar(at4);
////////	UART_TxChar('"');
////////	delay_ms(100);delay_ms(100);	delay_ms(100);delay_ms(100);
////////	UART_TxChar(CtrlZ);
////////		delay_ms(100);delay_ms(100);	delay_ms(100);delay_ms(100);	
////////	delay_ms(100);delay_ms(100);	delay_ms(100);delay_ms(100);	delay_ms(100);delay_ms(100);
//////	
////	   UART_TxChar('A');
////		   	UART_TxChar('T');
////			  UART_TxChar('\r');
////				delay_ms(100);delay_ms(100);delay_ms(100);delay_ms(100);
////				UART_TxChar('A');
////		     	  UART_TxChar('T');
////			       UART_TxChar('\r');
////		   	 delay_ms(100);delay_ms(100);delay_ms(100);delay_ms(100);    
////		  	   UART_TxChar('A');
////		     	  UART_TxChar('T');
////			       UART_TxChar('\r');
////				  delay_ms(100);delay_ms(100);delay_ms(100);delay_ms(100); 		
//////		   	        k=SBUF;
//////				      while(RI==0);
//////				       RI=0;
////			  		 
////		/****************END AT*********************************/
//////					  lcddata('d');
////   delay_ms(100);delay_ms(100);
////		/**************** AT+CSMP=49,167,0,0*********************************/	
////					  UART_TxChar('A');
////					   UART_TxChar('T');
////					    UART_TxChar('+');
////			 		     UART_TxChar('C');
////					 	  UART_TxChar('S');
////						   UART_TxChar('M');
////						    UART_TxChar('P');
////							 UART_TxChar('=');
////						      UART_TxChar('4');
////							   UART_TxChar('9');
////							    UART_TxChar(',');
////								 UART_TxChar('1');
////								  UART_TxChar('6');
////								   UART_TxChar('7');
////								    UART_TxChar(',');
////									 UART_TxChar('0');
////									  UART_TxChar(',');
////									   UART_TxChar('0');
////									    UART_TxChar('\r');
//////					  				     k=SBUF;
//////				                          while(RI==0);
//////				                           RI=0;

////										  // lcddata('e');
////										 delay_ms(100);delay_ms(100);delay_ms(100);delay_ms(100);
////		 /*****************END OF AT+CSMP=49,167,0,0**************************************/
////		 /***************** AT+CNMI=2,2,0,1,0*********************************************/
////	  	               UART_TxChar('A');
////		   	            UART_TxChar('T');
////		   	       		 UART_TxChar('+');
////						  UART_TxChar('C');
////					       UART_TxChar('N');
////						    UART_TxChar('M');
////							 UART_TxChar('I');
////							  UART_TxChar('=');
////							   UART_TxChar('2');
////							    UART_TxChar(',');
////								 UART_TxChar('2');
////								  UART_TxChar(',');
////								   UART_TxChar('0');
////								    UART_TxChar(',');
////									 UART_TxChar('1');
////									  UART_TxChar(',');
////									   UART_TxChar('0');;
////									    UART_TxChar('\r');
////										 k=SBUF;
////				                          while(RI==0);
////				                           RI=0;
////									  delay_ms(100);delay_ms(100);
////	/***************** END OF AT+CNMI=2,2,0,1,0*********************************************/
////	 	
////							//lcddata('f');
////	/***************** AT+CMGS="MOBILE NO";*********************************************/
////			UART_TxChar('A');
////			 UART_TxChar('T');
////			  UART_TxChar('+');
////			   UART_TxChar('C');
////			    UART_TxChar('M');
////				 UART_TxChar('G');
////				  UART_TxChar('S');
////				   UART_TxChar('=');
////				    UART_TxChar('"');
////					  UART_TxChar('+');
////					   UART_TxChar('9');
////					    UART_TxChar('1');
////					
////						while(at4[i]!='\0')
////						  {
////						   UART_TxChar(at4[mobnocnt1]);
////							mobnocnt1++;
////						   }
////						   mobnocnt1=0;		  
////					  	  UART_TxChar('"');
////						   UART_TxChar('\r');
//////						    k=SBUF;
//////				             while(RI==0);
//////				              RI=0;
////							 delay_ms(100);delay_ms(100);delay_ms(100);delay_ms(100);delay_ms(100);delay_ms(100);
////							 // lcddata('g');
////							
///////***************** end of AT+CMGS="MOBILE NO";*********************************************/
////       
//// }
