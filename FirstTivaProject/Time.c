/*
 * @file    Time.c
 * @brief   Contains all significant time setting, updating and displaying functionality.
 *          including argument processing, output string formatting and validity checking.
 *          Contains constant definitions only required buy this module.
 * @author  Liam JA MacDonald
 * @date    23-Sep-2019 (created)
 * @date    3-Oct-2019 (modified)
 */

#include    <string.h>
#include    <stdlib.h>
#include    <stdio.h>
#include    <ctype.h>
#include    "Utilities.h"
#include    "Date.h"
#define     GLOBAL_TIME
#include    "Time.h"

//Limit Constants
#define TENTHS_LIMIT    10                      //max set value
#define TENTHS_UPDATE_LIMIT     9               //max update value before reset
#define SECONDS_MINUTES_LIMIT   60
#define SECONDS_MINUTES_UPDATE_LIMIT    59
#define HOURS_LIMIT     24
#define HOURS_UPDATE_LIMIT      23
//Misc. Time Constants
#define HOURS       0                           //time array positions
#define MINUTES     1
#define SECONDS     2
#define TENTHS      3
#define TWO_DIGITS  10                          //two digit number musn't be formatted
#define PRECISION   4                           //clock has 4 degrees of precision
#define TIME_STRING     3                       //bytes for time strings when displayed


int time[PRECISION] = {0,0,0,0};

void updateTenths(void)
{
   time[TENTHS] = (time[TENTHS]<TENTHS_UPDATE_LIMIT) ? time[TENTHS]+1 : RESET;
   if(!(time[TENTHS])){updateSeconds();}
}

void updateSeconds(void)
{
    time[SECONDS] = (time[SECONDS]<SECONDS_MINUTES_UPDATE_LIMIT) ? time[SECONDS]+1 : RESET;
    if(!(time[SECONDS])){updateMinutes();}
}

void updateMinutes(void)
{
    time[MINUTES] = (time[MINUTES]<SECONDS_MINUTES_UPDATE_LIMIT) ? time[MINUTES]+1 : RESET;
    if(!(time[MINUTES])){updateHours();}
}

void updateHours(void)
{
    time[HOURS] = (time[HOURS]<HOURS_UPDATE_LIMIT) ? time[HOURS]+1 : RESET;
    if(!(time[HOURS])){updateDay();}
}


int setTime(char* cmd)
{
    int valid = TRUE;
    int tmpTime[PRECISION] = {0,0,0,0};
    char timeSplit[TIME_STRING];

    spaceFilter(cmd);                               //get rid of white space; stated in specifications
/*  if:
 *       command is empty: no arguments passed; print current time
 *       command not empty: process arguments
 */
    if(*cmd)
    {
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
/* check all values are:
 *                        1. valid digit characters
 *                        2. within specified limits
 */
    valid =(valid&&
            BOUNDARY_CHECK(tmpTime[TENTHS],TENTHS_LIMIT)&&
            BOUNDARY_CHECK(tmpTime[SECONDS],SECONDS_MINUTES_LIMIT)&&
            BOUNDARY_CHECK(tmpTime[MINUTES],SECONDS_MINUTES_LIMIT)&&
            BOUNDARY_CHECK(tmpTime[HOURS],HOURS_LIMIT));

    if(!(valid)){return valid;}
    //validity criteria met; set time
    for(i=0;i<PRECISION;i++){time[i]=tmpTime[i];}
    }

    printTime();
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

void printTime(void)
{
char digitRtn[PRECISION-1][TIME_STRING];//precision - 1 because tenths dont need to be reformatted
char tmp[20];

int i = 0;

while(i<TIME_STRING){formatTime(time[i],digitRtn[i++]);}//check for missing zeros

sprintf(tmp,"\n\r%s:%s:%s.%d",digitRtn[HOURS],digitRtn[MINUTES],digitRtn[SECONDS],time[TENTHS]);

printString(tmp);
}





