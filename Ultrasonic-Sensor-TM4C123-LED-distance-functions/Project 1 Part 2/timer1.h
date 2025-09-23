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

#include "tm4c123gh6pm.h"
#include <stdint.h>


// Timer1 Setup
#define TIMER1 0x02
#define MODE_16bit 0x00000004
#define PERIODIC_MODE 0x00000002 // Periodic mode


// Timer A : 10us delay
//====================================================
#define TIMER1A_MASK 0x00000001
#define MAX_RELOAD 159
#define PRESCALE 0


// Timer B : Max count time of 50ms
//====================================================
#define TIMER1B_MASK 	0x00000100
#define TIMERB_RELOAD 50666
#define PRESCALE_B		12

void Timer1_Init(void);
void Timer1A_Init(void);
void EchoTimer1_Init(void);
void delay(uint32_t ticks);
void Start_EchoTimer(void);
void Stop_EchoTimer(void);
uint32_t Get_Elapsed_MC(void);


