/*
Name: Eric Santana
ID: 015107467
ORG: CSULB
Class: CECS 347
--------------------------
Description: Enable the general purpose timer 1A to produce a 10us delay.
Timer 1A Config: 16bit mode, One shot, down counter
*/

#include "timer1.h"

void Timer1_Init(){
	SYSCTL_RCGCTIMER_R |= TIMER1;      	// Activate TIMER1
	while((SYSCTL_RCGCTIMER_R & TIMER1) != TIMER1){}// wait for timer to activate
		
	TIMER1_CFG_R = MODE_16bit;
	Timer1A_Init();
	Timer1B_Init();
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

void delay(){ // 10 micro second delay
	
    TIMER1_CTL_R |= TIMER1A_MASK;          // Start timer

    while((TIMER1_RIS_R & TIMER_RIS_TATORIS) == 0); // Wait
	
    TIMER1_ICR_R = TIMER1A_MASK;       // Clear flag
	
}

// Timer B Setup
//===========================================================================
void Timer1B_Init(){ // 50ms counting
	
	TIMER1_CTL_R &=~ TIMER1B_MASK;	//Disable Timer1 B during setup
	TIMER1_TBMR_R = PERIODIC_MODE;	//Peridic Mode, down counter
	TIMER1_TBILR_R = TIMERB_RELOAD;	// Reload value for 50ms
	TIMER1_TBPR_R = PRESCALE_B;			// prescale of 12
	TIMER1_ICR_R = TIMER1B_MASK;		// Clear timer flag
	
}
//Stop Timer B
void Start_TimerB(void){
	TIMER1_TBILR_R = TIMERB_RELOAD;	// Fresh reload
	TIMER1_CTL_R |= TIMER1B_MASK;		// Start Timer B
	

}
//Stop Timer B
void Stop_TimerB(){
	TIMER1_CTL_R &=~ TIMER1B_MASK; // stop timer
	TIMER1_ICR_R = TIMER1B_MASK;	// Clear timerB flag
}

// Calculate elapsed cycles
uint32_t Get_Elapsed_MC(){
	
	// (Reload ValueB - CurrentValueB) * PrescaleB
	return (TIMER1_TBILR_R - TIMER1_TBR_R) * PRESCALE_B;
}


