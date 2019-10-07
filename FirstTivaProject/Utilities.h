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
#define     INPUT       0
#define     OUTPUT      1
#define     TRUE        1
#define     FALSE       0
#define     SUCESS      1
#define     FAILURE     0
#define     RESET       0
#define     HOURS       0                           //time array positions
#define     MINUTES     1
#define     SECONDS     2
#define     TENTHS      3
#define     PRECISION   4
#define     TIME_STRING     3
#define     TENTHS_LIMIT    10                      //max set value
#define     SECONDS_MINUTES_LIMIT   60
#define     HOURS_LIMIT     24
#define     TWO_DIGITS      10                          //two digit number musn't be formatted

#define     BOUNDARY_CHECK(X,Y) (RESET<=X<Y)            //check time or date value is within boundaries
#define     UPDATE(VAL,LIM,FUNC) VAL = (VAL<LIM) ? VAL+1 : RESET;\
                                             if(!(VAL)){FUNC;}

#ifndef     UTILITIES
#define     UTILITIES


    extern void printChar(char);
    extern void printString(char*);
    extern void spaceFilter(char*);
    extern int myAtoi(int *, char*);
    extern int parseClock(char*,int*);
    extern void printTime(int * );

#else

    void printChar(char);
    void printString(char*);
    void spaceFilter(char*);
    int myAtoi(int *, char*);
    int parseClock(char*,int*);
    void formatTime(int, char*);
    void printTime(int *);

#endif /* UTILITIES */
