#include "tm4c123gh6pm.h"


#define PORTB_MASK 0x02
#define TRIGGER_MASK 0x20
#define ECHO_MASK 0x10

#define B4_B5_MASK 0x30
#define PORTB_PCTL_CODE 0x00FF0000

#define PORTB_PRIORITY_1 0x00002000


void portB_Init();
