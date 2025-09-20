/*
Name: Eric Santana
ID: 015107467
ORG: CSULB
Class: CECS 347
--------------------------
Description: Enable the use of the red LED on port F*/

#include "PortF.h"

void PortF_Init(void){
	
	// Port F Clk Setup
	//------------------------------
	SYSCTL_RCGCGPIO_R |= GPIOF;
	
	while((SYSCTL_RCGCGPIO_R & GPIOF)== 0){}//wait for Port F clk to startup
	
		
		// GPIO SETUP
		//------------------------------
		GPIO_PORTF_LOCK_R = PORTF_UNLOCK_CODE; // Unlock port F.
		GPIO_PORTF_CR_R |= PORTF_CR_CODE;	// Enable changes to port F.

		//LEDS Setup
	//================================================================
		GPIO_PORTF_DIR_R |= LEDS; // Set F1 as output.
		GPIO_PORTF_AFSEL_R &=~LEDS;// Disable Alternate Function
		GPIO_PORTF_DEN_R |= LEDS;	// Enable F1 pin
		GPIO_PORTF_AMSEL_R &=~LEDS;	// Disable Analog Mode
			
	//Switch 1 setup

		GPIO_PORTF_DIR_R &=~ SW1; // Set Switch 1 as input
		GPIO_PORTF_AFSEL_R &=~ SW1;// Disable Alternate Function for Sw1
		GPIO_PORTF_DEN_R |= SW1; //Enable Switch 1
		GPIO_PORTF_PUR_R |=SW1;
		GPIO_PORTF_AMSEL_R &=~ SW1;
		
			
	//================================================================
		GPIO_PORTF_PCTL_R &=~ PORTF_PCTL_CODE;	// Enable F1 pctl
		
	//================================================================
	
	//Port F Sw1 Interupt Setup
	
		GPIO_PORTF_IS_R &=~ SW1; // F4 is edge sensitive
		GPIO_PORTF_IBE_R &=~ SW1; // F4 is not both edges
		GPIO_PORTF_IEV_R |= SW1; // F4 is rising edge sensitive
		GPIO_PORTF_ICR_R = SW1; // Clear interupt flag
		GPIO_PORTF_IM_R |= SW1; // Arm F4 interupt
		
		NVIC_EN0_R |= (1<<30);
		NVIC_PRI7_R = (NVIC_PRI7_R & 0xFF00FFFF) | (5 << 21);

		
		
}