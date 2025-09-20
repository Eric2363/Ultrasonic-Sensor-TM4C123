#include <stdint.h>
//==================================================================
//UART0 and GPIO PORT A Addresses
//==================================================================
#include "tm4c123gh6pm.h"



#define UART0_MASK 0x0001
#define GPIO_PORTA 0x01
#define DISABLE_UART0 0x0001
#define IBRD_CODE 17
#define FBRD_CODE 23
#define LCRH_CODE 0x70
#define CTL_CODE 0x301
#define AFSEL_CODE 0x03
#define AMSEL_CODE 0x03
#define DEN_CODE 0x03

void Uart_Init(void);

char Uart_Recieve(void);

void Uart_Transmit(char data);

void Uart_SendString(const char* str);

void Uart_SendNumber(uint32_t num);
