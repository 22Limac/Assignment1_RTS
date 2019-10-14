/*
 * @file    Time.c
 * @brief   Contains all time setting, updating and displaying functionality.
 *          Including argument processing, output string formatting and validity checking.
 *          Contains constant definitions only required by this module.
 * @author  Liam JA MacDonald
 * @date    23-Sep-2019 (created)
 * @date    6-Oct-2019 (modified)
 */

#include    <string.h>
#include    <stdlib.h>
#include    <stdio.h>
#include    <ctype.h>
#include    "Date.h"
#include    "Alarm.h"
#define     GLOBAL_TIME
#include    "Time.h"

//Limit Constants
#define TENTHS_UPDATE_LIMIT     9               //max update value before reset
#define SECONDS_MINUTES_UPDATE_LIMIT    59
#define HOURS_UPDATE_LIMIT      23



static int time[PRECISION] = {RESET,RESET,RESET,RESET}; // used for storing current time

/*
 * @brief   Increments tenths of a second time value
 * @details Increments tenths of a second value in
 *          the time array. If it's exceeded it's max
 *          value updateSeconds function is called.
 *          calls alarmCheck function from Alarm.c module
 *
 */
void updateTenths(void)
{
   UPDATE(time[TENTHS],TENTHS_UPDATE_LIMIT,updateSeconds())
   alarmCheck();
}

/*
 * @brief   Increments seconds time value
 * @details Increments the seconds value in
 *          the time array. If it's exceeded it's max
 *          value updateMinutes function is called.
 */
inline void updateSeconds(void)
{
    UPDATE(time[SECONDS],SECONDS_MINUTES_UPDATE_LIMIT,updateMinutes())
}

/*
 * @brief   Increments minutes time value
 * @details Increments the minutes value in
 *          the time array. If it's exceeded it's max
 *          value updateHours function is called.
 */
inline void updateMinutes(void)
{
    UPDATE(time[MINUTES],SECONDS_MINUTES_UPDATE_LIMIT,updateHours())
}
/*
 * @brief   Increments hours time value
 * @details Increments the hours value in
 *          the time array. If it's exceeded it's max
 *          value updateDays function is called.
 */
inline void updateHours(void)
{
    UPDATE(time[HOURS],HOURS_UPDATE_LIMIT,updateDay())
}

/*
 * @brief   sets or displays current time
 * @param   [in] cmd: string containing the arguments for the command
 * @return  int return used as a boolean value,
 *          if returns 1 the command was successful;
 *          if 0 it failed
 * @details if cmd string is null the current time is displayed
 *          otherwise, the string is passed to parseClock in Utilities.c module
 *          validity of each time value is checked; FAILURE is returned if not valid
 *          the current time array is populated
 *          new current time printed to screen
 *
 */
int setTime(char* cmd)
{
    int valid = TRUE;
    /*set to forbidden so values that are set to zero are skipped in parseClock*/
    int tmpTime[PRECISION] = {FORBIDDEN,FORBIDDEN,FORBIDDEN,FORBIDDEN};

    spaceFilter(cmd);                               //get rid of white space; stated in specifications
/*  if:
 *       command is empty: no arguments passed; print current time
 *       command not empty: process arguments
 */
    if(*cmd)
    {
/* check all values are:
 *                        1. valid digit characters
 *                        2. within specified limits
 */
        valid =(parseClock(cmd,tmpTime)&&
                BOUNDARY_CHECK(tmpTime[TENTHS],TENTHS_LIMIT)&&
                BOUNDARY_CHECK(tmpTime[SECONDS],SECONDS_MINUTES_LIMIT)&&
                BOUNDARY_CHECK(tmpTime[MINUTES],SECONDS_MINUTES_LIMIT)&&
                BOUNDARY_CHECK(tmpTime[HOURS],HOURS_LIMIT));

        if(!(valid)){return valid;}
        //validity criteria met; set time
        int i;
        for(i=0;i<PRECISION;i++){time[i]=tmpTime[i];}
    }

    printString("\n\r");
    printTime(time);
    return valid;
}

const int* getTime(void)
{
    return time;
}





