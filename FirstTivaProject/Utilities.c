/*
 * @file    Utilities.c
 * @brief   Contains functions frequently used
 *          over several modules used to format
 *          convert values and printing multiple
 *          characters in varying formats
 * @author  Liam JA MacDonald
 * @date    23-Sep-2019 (created)
 * @date    10-Oct-2019 (modified)
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

/*
 * @brief   Enqueues a complete string onto the OUTPUT
 *          queue
 * @param   [in] char* string: string to be queued
 * @details enqueues one character at a time until
 *          nul character
 */
void printString(char* string)
{
    interruptType out ={UART, NUL};
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

/*
 * @brief   Allows any two seperators next to each other to set
 *          the respective value to 0
 * @param   [in] char* str: string that will analyzed
 *          [out] int* num: array for time values to be passed
 * @return  int: returns the amount of time values that are left to set
 * @details toSet is decremented every time a condition is satisfied
 *
 */
int emptyFilter(char* str, int* num)
{
        int toSetCnt = PRECISION;
        const char* tmp = str;
        if(*tmp==':')
        {
            num[HOURS] = RESET;
            toSetCnt--;
        }
        while(*tmp)
        {
            if((*tmp==':')&&(*(tmp+1)==':'))
            {
                num[MINUTES] = RESET;
                toSetCnt--;
            }
            if((*tmp==':')&&(*(tmp+1)=='.'))
            {
                num[SECONDS] = RESET;
                toSetCnt--;
            }
            if((*tmp=='.')&&(*(tmp+1)==NUL))
            {
                num[TENTHS] = RESET;
                toSetCnt--;
            }
            tmp++;
        }
        return toSetCnt;
}

/*
 * @brief   converts ascii to decimal value
 * @param   [in] char* str: string that will be converted from ascii
 *          [out] int* num: integer passed reference to store decimal value
 * @return  int return used as a boolean value,
 *          if returns 1 string was successfully converted
 *          if returns 0 characters were not digits or the string
 *          too long
 */
int myAtoi(int * num, char* str)
{
    int total = 0;

    while(*str)
    {
        if((*str>='0')&&(*str<='9')&&(strlen(str)<TIME_STRING))
        {
          total = total*10+(*(str++)-'0') ;
        }
        else
        {return FAILURE;}
    }
    *num = total;
    return SUCCESS;
}

/*
 * @brief   parses time formatted argument string
 *          into an int array
 * @param   [in] char* str: string that will be parse
 *          [out] int* num: array for time values to be passed
 * @return  int return used as a boolean value,
 *          if returns 1 string was successfully parsed
 *          if returns 0 characters were not digits or
 *          weren't formatted correctly
 */
int parseClock(char* cmd,int* tmpTime)
{
    char timeSplit[TIME_STRING];
    int valid = TRUE;
    int toSet = emptyFilter(cmd,tmpTime);
    if(toSet==FALSE)
    {
        return valid;
    };
    int i = HOURS;
    /* Check for first non set time value */
    while(tmpTime[i]!=FORBIDDEN){i++;}
    cmd = strtok(cmd,":.");
    strcpy(timeSplit,cmd);
    valid =  myAtoi(&tmpTime[i++],timeSplit);
    toSet--;
    /*the first strtok is different from the rest */
    while(i<PRECISION&&valid&&toSet)
    {
        while(tmpTime[i]!=FORBIDDEN){i++;}
        cmd = strtok(NULL,":.");
        strcpy(timeSplit,cmd);
        valid = myAtoi(&tmpTime[i++],timeSplit);
        toSet--;
    }
    return valid;
}

/*
 * @brief   adds a leading zero if a single digit number
 *          converts digit to a string
 * @param   [in] int val: value to be converted to a string
 *          [out] char* rtn: to return the formatted string
 */
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

/*
 * @brief   prints time array to screen in time format
 * @param   [in] const int* timeToFormat: time array
 * @details each time value is formatted and converted to a string
 *          then printed to the terminal
 */

void printTime(const int * timeToFormat)
{
char digitRtn[PRECISION-1][TIME_STRING];//precision - 1 because tenths dont need to be reformatted
char tmp[OUTPUT_STRING];

int i = 0;
while(i<TIME_STRING){formatTime(timeToFormat[i],digitRtn[i++]);}//check for missing zeros
sprintf(tmp,"%s:%s:%s.%d",digitRtn[HOURS],digitRtn[MINUTES],digitRtn[SECONDS],timeToFormat[TENTHS]);
printString(tmp);

}



