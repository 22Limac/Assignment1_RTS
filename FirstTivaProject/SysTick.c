/*
 - SysTick sample code
 - Originally written for the Stellaris (2013)
 - Will need to use debugger to "see" interrupts
 - Code uses bit-operations to access SysTick bits
*/
#define GLOBAL_SYSTICK
#include "SysTick.h"
#include "InterruptType.h"
#include "Utilities.h"
#include "Queue.h"


#define TRUE 1
#define FALSE 0
/* Global to signal SysTick interrupt */
interruptType sysInt = {SYSTICK,NUL};

void SysTickStart(void)
{
// Set the clock source to internal and enable the counter to interrupt
ST_CTRL_R |= ST_CTRL_CLK_SRC | ST_CTRL_ENABLE;  
}

void SysTickStop(void)
{
// Clear the enable bit to stop the counter
ST_CTRL_R &= ~(ST_CTRL_ENABLE);  
}

void SysTickPeriod(unsigned long Period)
{
/*
 For an interrupt, must be between 2 and 16777216 (0x100.0000 or 2^24)
*/
ST_RELOAD_R = Period - 1;  /* 1 to 0xff.ffff */
}

void SysTickIntEnable(void)
{
// Set the interrupt bit in STCTRL
ST_CTRL_R |= ST_CTRL_INTEN;	
}

void SysTickIntDisable(void)
{
// Clear the interrupt bit in STCTRL
ST_CTRL_R &= ~(ST_CTRL_INTEN);	
}	

// global variable to count number of interrupts on PORTF0 (falling edge)



void SysTickHandler(void)
{
    enqueue(INPUT,sysInt);
}
