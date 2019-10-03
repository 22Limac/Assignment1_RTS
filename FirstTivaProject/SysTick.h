/*
 * SysTick.h
 *
 *  Created on: Sep 23, 2019
 *      Author: Liam MacDonald
 */
// SysTick Registers
// SysTick Control and Status Register (STCTRL)
#pragma once

#define ST_CTRL_R   (*((volatile unsigned long *)0xE000E010))
// Systick Reload Value Register (STRELOAD)
#define ST_RELOAD_R (*((volatile unsigned long *)0xE000E014))

// SysTick defines
#define ST_CTRL_COUNT      0x00010000  // Count Flag for STCTRL
#define ST_CTRL_CLK_SRC    0x00000004  // Clock Source for STCTRL
#define ST_CTRL_INTEN      0x00000002  // Interrupt Enable for STCTRL
#define ST_CTRL_ENABLE     0x00000001  // Enable for STCTRL

// Maximum period
#define MAX_WAIT           0x1000000   /* 2^24 */
#define TENTH_WAIT         0x186A00 //(2^24)/10
#define SYSTICK 1

#ifndef GLOBAL_SYSTICK
#define GLOBAL_SYSTICK

    extern volatile int elapsed;
    extern volatile char count;
    extern void SysTickStart(void);
    extern void SysTickStop(void);
    extern void SysTickPeriod(unsigned long);
    extern void SysTickIntEnable(void);
    extern void SysTickIntDisable(void);
    extern void SysTickHandler(void);

#else

    volatile int elapsed;
    volatile int count = 0;
    void SysTickStart(void);
    void SysTickStop(void);
    void SysTickPeriod(unsigned long);
    void SysTickIntEnable(void);
    void SysTickIntDisable(void);
    void SysTickHandler(void);

#endif //GLOBAL_SYSTICK
