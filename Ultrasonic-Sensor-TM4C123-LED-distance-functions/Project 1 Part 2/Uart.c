#include "Uart.h"
#include <stdint.h>



//==================================================================
// UART0 Setup
//==================================================================
void Uart_Init(void){
    SYSCTL_RCGCUART_R  |= UART0_MASK;      // Enable UART0 clock
		while((SYSCTL_RCGCUART_R & UART0_MASK) !=UART0_MASK){}// wait to stablize
	
    SYSCTL_RCGCGPIO_R  |= GPIO_PORTA;      // Enable Port A clock
		while((SYSCTL_RCGCGPIO_R & GPIO_PORTA) !=GPIO_PORTA){}// wait to stablize
			


    UART0_CTL_R &= ~DISABLE_UART0;                // Disable UART0 during config
    UART0_IBRD_R = IBRD_CODE;                    // 16 MHz / (16 * 57,600) = 17.3611
    UART0_FBRD_R = FBRD_CODE;                     // Fraction = 0.3611 * 64 + 0.5 = 23
    UART0_LCRH_R = LCRH_CODE;                   // 8-bit, 1 stop bit, no parity, FIFO
    UART0_CTL_R = CTL_CODE;                   // Enable UART0, RXE, TXE

    GPIO_PORTA_AFSEL_R |= AFSEL_CODE;            // Enable alt funct on PA0, PA1
   GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFFFFFF00)+0x00000011;
    GPIO_PORTA_AMSEL_R &= ~AMSEL_CODE;           // Disable analog on PA0, PA1
    GPIO_PORTA_DEN_R |= DEN_CODE;              // Enable digital on PA0, PA1
}

//==================================================================
//Read an 8bit value being sent to MCU
//==================================================================
char Uart_Recieve(void){
	
	while((UART0_FR_R & UART_FR_RXFE) !=0);//wait to receive char
	
	return ((uint8_t)(UART0_DR_R &0xFF));

}

//==================================================================
//Transmit a 8bit character
//==================================================================
void Uart_Transmit(uint8_t data){
	
	while((UART0_FR_R & UART_FR_TXFF) !=0);//wait for reg to be full
	UART0_DR_R = data;

}

//==================================================================
//Transmit a string of characters
//==================================================================
void Uart_SendString(const char* str){

	while(*str){
		Uart_Transmit(*str++);
	}

}
//==================================================================
// Send an unsigned integer as ASCII decimal string
//==================================================================
void Uart_SendNumber(uint32_t num){
    char buffer[12];   // enough for 32-bit integer
    int i = 0;

    if(num == 0){
        Uart_Transmit('0');
        return;
    }

    // Convert number to string (reverse order)
    while(num > 0 && i < sizeof(buffer)-1){
        buffer[i++] = (num % 10) + '0';
        num /= 10;
    }

    // Send digits in correct order
    while(i > 0){
        Uart_Transmit(buffer[--i]);
    }
}
