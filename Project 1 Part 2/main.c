/*
Name: Eric Santana
ID: 015107467
ORG: CSULB
Class: CECS 347 Embedded System II
--------------------------
Description: This project aims to implement a HC204 Ultrasonic Distance
Sensor driver to display distance in cm to a pc console via Uart. And blink
the onboard TM4C123 LED's depending on distance.
*/
#include <stdio.h>
#include <stdint.h>
#include "PLL.h"
#include "SysTick.h"
#include "PortF.h"
#include "timer1.h"
#include "portB.h"
#include "Uart.h"

#define RED_LED 0x02


#define ECHO_VALUE 0x10
#define MC_LEN 0.0625
#define SOUND_SPEED 0.0343

uint32_t distance;
int done;


void Trigger(void){
		GPIO_PORTB_DATA_R |= 0x20;
		delay();
		GPIO_PORTB_DATA_R &=~ 0x20;
		delay();
		
}

int main(void){

	PLL_Init();
	PortF_Init();
	Timer1_Init();
	portB_Init();
	Uart_Init();
	
	
	while(1){
		done = 0;
		distance =0;
		
		Trigger();
		
	}


	return 0;
	
}

void GPIOPortB_Handler(void){

	if(GPIO_PORTB_DATA_R & ECHO_VALUE){
		Start_TimerB();
	
	}
	else{
		Stop_TimerB();
		distance = (uint32_t)(Get_Elapsed_MC()*MC_LEN*SOUND_SPEED)/2;
		Uart_SendString("Distance: ");
		Uart_SendNumber(distance);
		Uart_SendString("cm\r\n");		
		done = 1;
	
	}

GPIO_PORTB_ICR_R = ECHO_VALUE;
	

}
