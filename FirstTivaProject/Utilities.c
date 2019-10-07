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
#include    <string.h>
#include    <stdlib.h>
#include    <stdio.h>
#include    <ctype.h>

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
/*
 * @brief   for removing all spaces in a string
 * @param   [in,out] str: string that will have spaces removed
 * @details create a constant char * tmp which acts as an index,
 *          while the current value where tmp points is a space char,
 *          increment where tmp points. When it no longer points to an
 *          address containing a space, the value is written the address
 *          where ptr is pointing than it is incremented until a nul char
 *          is written which breaks the while loop.
 * @details original code slightly altered for readability
 *          https://stackoverflow.com/questions/1726302/removing-spaces-from-a-string-in-c
 *
 */
void spaceFilter(char* str) {
    /*
     *  const used to protect contents of str;
     *  this only allows address pointed to change
     *  not contents
     */
        const char* tmp = str;
        do
        {
            while (*tmp == ' '){++tmp;}
            *str++ = *tmp++;
        }
        while(*str);
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

int parseClock(char* cmd,int* tmpTime)
{
    char timeSplit[TIME_STRING];
    int valid;
    cmd = strtok(cmd,":.");
    strcpy(timeSplit,cmd);
    valid = myAtoi(&tmpTime[HOURS],timeSplit);
    int i = MINUTES;
    while((i<PRECISION)&&valid)
    {
        cmd = strtok(NULL,":.");
        strcpy(timeSplit,cmd);
        valid = myAtoi(&tmpTime[i++],timeSplit);
    }
    return valid;
}

void formatTime(int val, char* rtn)
{
    if(val<TWO_DIGITS)//only values less than ten have zeros added to the tens placement
    {
        sprintf(rtn,"0%d",val);
    }
    else
    {
        sprintf(rtn,"%d",val);
    }
}

void printTime(int * timeToFormat)
{
char digitRtn[PRECISION-1][TIME_STRING];//precision - 1 because tenths dont need to be reformatted
char tmp[20];

int i = 0;

while(i<TIME_STRING){formatTime(timeToFormat[i],digitRtn[i++]);}//check for missing zeros

sprintf(tmp,"%s:%s:%s.%d",digitRtn[HOURS],digitRtn[MINUTES],digitRtn[SECONDS],timeToFormat[TENTHS]);

printString(tmp);
}



