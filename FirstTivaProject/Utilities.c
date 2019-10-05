/*
 * Utilities.c
 *
 *  Created on: Sep 29, 2019
 *      Author: LiamMacDonald
 */
#define UTILITIES
#include "Utilities.h"
#include "UART.h"
#include "Queue.h"
#include "InterruptType.h"

interruptType out ={UART, NUL};



void printChar(char data)
{
    forceOutput(data);
}

void printString(char* string)
{

    while(*string)
    {
        out.data =*(string++);
        enqueue(OUTPUT,out);
    }
}

void spaceFilter(char* str) {
        const char* tmp = str;
        do {while (*tmp == ' '){++tmp;}}
        while (*str++ = *tmp++);
}

int myAtoi(int * num, char* str)
{
    int total = 0;
    if(*str==NUL){*num = 0;}

    while(*str)
    {
        if((*str>='0')&&(*str<='9'))
        {
          total = total*10+(*(str++)-'0') ;
        }
        else
        {return FAILURE;}
    }
    *num = total;
    return SUCESS;
}


