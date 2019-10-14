/*
 * @file    SysTick.c
 * @brief   Contains initialization routines to set
 *          a systick interrupt every tenth of a second.
 *          Stop and Start functions. Definition of the
 *          SysTick ISR
 * @author  Liam JA MacDonald (Edited) Emad Khan (Original)
 * @date    23-Sep-2019 (Created)
 * @date    10-Oct-2019 (Modified)
 */

#define GLOBAL_SYSTICK
#include "SysTick.h"
#include "InterruptType.h"
#include "Utilities.h"
#include "Queue.h"

/*SysTick interrupt buffer */
static interruptType sysInt = {SYSTICK,NUL};

/*
 * @brief   Set the clock source to internal and enable the counter to interrupt
 */
void SysTickStart(void)
{
ST_CTRL_R |= ST_CTRL_CLK_SRC | ST_CTRL_ENABLE;  
}

/*
 * @brief   Clear the enable bit to stop the counter
 */
void SysTickStop(void)
{
ST_CTRL_R &= ~(ST_CTRL_ENABLE);  
}

/*
 * @brief   Set interrupt period
 */
void SysTickPeriod(unsigned long Period)
{
/*
 For an interrupt, must be between 2 and 16777216 (0x100.0000 or 2^24)
*/
ST_RELOAD_R = Period - 1;  /* 1 to 0xff.ffff */
}

/*
 * @brief   Enable Systick interrupts
 */
void SysTickIntEnable(void)
{
// Set the interrupt bit in STCTRL
ST_CTRL_R |= ST_CTRL_INTEN;	
}

/*
 * @brief   disable Systick interrupts
 */
void SysTickIntDisable(void)
{
// Clear the interrupt bit in STCTRL
ST_CTRL_R &= ~(ST_CTRL_INTEN);	
}	

/*
 * @brief   SysTick ISR, enqueue a SysTick interrupt
 *          in the INPUT queue
 */
void SysTickHandler(void)
{
    enqueue(INPUT,sysInt);
}
