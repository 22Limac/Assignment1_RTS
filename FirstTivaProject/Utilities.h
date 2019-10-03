/*
 * Utilities.h
 *
 *  Created on: Sep 29, 2019
 *      Author: Liam MacDonald
 */
#pragma     once
#define     disable()   __asm(" cpsid i")
#define     enable()    __asm(" cpsie i")
#define     ENTER       0x0d
#define     BS          0x08
#define     NUL         0x00
#define     AST         0x2a
#define     TRUE        1
#define     FALSE       0
#define     SUCESS      1
#define     FAILURE     0
#define     RESET       0
#define     BOUNDARY_CHECK(X,Y) (RESET<=X<Y)            //check time or date value is within boundaries

#ifndef     UTILITIES
#define     UTILITIES


    extern void printChar(char);
    extern void printString(char*);
    extern void spaceFilter(char*);

#else

    void InterruptMasterEnable(void);
    void printChar(char);
    void printString(char*);
    void spaceFilter(char*);

#endif /* UTILITIES */
