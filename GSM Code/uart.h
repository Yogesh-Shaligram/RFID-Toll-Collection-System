#include<reg51.h>
void UART_Init();
char UART_RxChar();
void UART_TxChar(char ch);
void UART_TxString(char *string_ptr);
void UART_RxString(char *string_ptr);
void UART_TxNumber(unsigned int num);

  