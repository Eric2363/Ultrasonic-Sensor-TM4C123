/*
Name: Eric Santana
ID: 015107467
ORG: CSULB
Class: CECS 347
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
/*
160 = 10us * 16MHz

160 < 65,535, fits inside a 16bit timer so no prescale needed.
Prescale = 0

160 = (0*65,536) + Reload + 1
160 = Reload + 1
160 -1 = Reload

159 = Reload
0 = Prescale
This will make 10us
*/

#define MAX_RELOAD 159
#define PRESCALE 0


// Timer B : Max count time of 50ms
//====================================================
#define TIMER1B_MASK 	0x00000100

/*
total ticks for 50ms
800,000 = 50ms * 16MHz
Total Ticks = (Prescale * 65,535 +1) + Reload +1
try prescale 12
800,000 = (12 * 65,536) + Reload +1
800,000 = 786,432 + Reload + 1
800,000 = 786,433 + Reload
800,000 - 786,433 = Reload

13,567 = Reload
12 = Prescale  

this will makes 50ms
*/

#define TIMERB_RELOAD 13567
#define PRESCALE_B		12

void Timer1_Init(void);
void Timer1A_Init(void);
void Timer1B_Init(void);
void delay();
void Start_TimerB(void);
void Stop_TimerB(void);
uint32_t Get_Elapsed_MC(void);


