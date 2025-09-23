
#include "tm4c123gh6pm.h"

#define PORTF_UNLOCK_CODE 0x4C4F434B // Unlocks port F.
#define PORTF_CR_CODE 0x1F // Allow changes to portF. 
#define GPIOF 0x20 // GPIO portF

#define RED 0x02 // Bit mask for Red LED.
#define BLUE 0x04 //Bit mask for Blue LED.
#define GREEN 0x08 // Bit mask for Green LED.
#define LEDS 0x0E// Bit mask for all LEDS

#define SW1 0x10 // Bit mask for Switch 1

#define PORTF_PCTL_CODE 0xFFFF0// PCTL for Sw1,Green,Blue,Red


// interupt setup

void PortF_Init(void);