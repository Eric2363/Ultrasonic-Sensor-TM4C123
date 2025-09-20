/*
Name: Eric Santana
ID: 015107467
ORG: CSULB
Class: CECS 347
--------------------------
Description: Sytick timer is configured to generate 0.25s delay*/

#include "tm4c123gh6pm.h"
#include "SysTick.h"


void SysTick_Init(){

	NVIC_ST_CTRL_R = CLEAR_REG;	//Disable SysTick.
	NVIC_ST_RELOAD_R = HALF_SEC - 1;	// Load HALF_SEC .
	NVIC_ST_CURRENT_R = CLEAR_REG;	// Clear current value.
  NVIC_ST_CTRL_R = EN_SYSTICK;	// Start timer, use external clk, enable interupt.
	

}




//void SysTick_Handler(void){
//	
//	GPIO_PORTF_DATA_R ^= 0x02;
//}

