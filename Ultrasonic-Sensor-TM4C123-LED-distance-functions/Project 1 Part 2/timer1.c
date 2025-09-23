/*
Group:4
Eric Santana
Hector Polanco
Kero Samaan
Mason Doan
ORG: CSULB
Class: CECS 347 Embedded System II
--------------------------
Description: Enable the general purpose timer 1A to produce a 10us delay.
Timer 1A Config: 16bit mode, One shot, down counter
*/

#include "timer1.h"

void Timer1_Init(){
	SYSCTL_RCGCTIMER_R |= TIMER1;      	// Activate TIMER1
	while((SYSCTL_RCGCTIMER_R & TIMER1) != TIMER1);// wait to until timer1 is active
	TIMER1_CFG_R = MODE_16bit;
	Timer1A_Init();
	EchoTimer1_Init();
}
//Timer 1 Setup
//===========================================================================
void Timer1A_Init(void){
	

  TIMER1_CTL_R &=~ TIMER1A_MASK;       // Disable TIMER1 A during setup
  TIMER1_TAMR_R = PERIODIC_MODE;      // Periodic Mode, down-counter
  TIMER1_TAILR_R = MAX_RELOAD;        // Reload value (16-bit max)
  TIMER1_TAPR_R = PRESCALE;           // prescale = 0. Withing resoultion of 16 bits.
	TIMER1_ICR_R = TIMER1A_MASK;				// Clear TIMER1A timeout flag

}
// 
void delay(uint32_t ticks){
    
		TIMER1_TAILR_R = ticks;				//load Timer1A with ticks
    TIMER1_CTL_R |= TIMER1A_MASK;          // Start timer

    while(TIMER1_TAR_R != 0); // Wait for timer to run out
}

// Echo Timer config Setup
//===========================================================================
void EchoTimer1_Init(){ // 38ms counting
	
	TIMER1_CTL_R &=~ TIMER1A_MASK;	//Disable Timer1 B during setup
	TIMER1_TAMR_R = PERIODIC_MODE;	//Peridic Mode, down counter
	TIMER1_TAILR_R = TIMERB_RELOAD;	// Reload value for 50ms
	TIMER1_TAPR_R = PRESCALE_B;			// prescale of 12
	TIMER1_ICR_R = TIMER1A_MASK;		// Clear timer flag
	
}
//Start Timer1A Echo config
void Start_EchoTimer(void){
	TIMER1_TAILR_R = TIMERB_RELOAD; // Load 38ms
  TIMER1_TAPR_R  = PRESCALE_B;    // Load Prescale value of 12
  TIMER1_ICR_R   = TIMER1A_MASK;  // clear intterupt flag
  TIMER1_CTL_R  |= TIMER1A_MASK;  // Enable timer
}

//Stop Timer1A Echo config
void Stop_EchoTimer(){
	TIMER1_CTL_R &=~ TIMER1A_MASK; // stop timer
	TIMER1_ICR_R = TIMER1A_MASK;	// Clear timerB flag
}

// Calculate elapsed cycles
uint32_t Get_Elapsed_MC(){
	
	// (Reload ValueB - CurrentValueB) * PrescaleB + 1
	return (TIMER1_TAILR_R - TIMER1_TAR_R) * (PRESCALE_B + 1);
}


