/*
 * @file    Alarm.c
 * @brief   Contains all Alarm setting, updating and clearing functionality,
 *          including argument processing, output string formatting and validity checking.
 *          Initializes the alarmState structure and updates it when called from Time.c module
 *          Contains constant definitions only required by this module.
 * @author  Liam JA MacDonald
 * @date    5-Oct-2019 (created)
 * @date    6-Oct-2019 (modified)
 */
#include    <string.h>
#include    <stdlib.h>
#include    <stdio.h>
#include    <ctype.h>
#include    "Utilities.h"
#include    "Time.h"
#define     GLOBAL_ALARM
#include    "Alarm.h"

#define     TENTHS_IN_SECOND    10
#define     SECONDS_IN_MINUTE   60
#define     MINUTES_IN_HOUR     60
#define     HOURS_IN_DAY        24
#define     ALARM_TRIGGER       0

#define     TENTHS_IN_MINUTE    (TENTHS_IN_SECOND*SECONDS_IN_MINUTE)
#define     TENTHS_IN_HOUR      (TENTHS_IN_MINUTE*MINUTES_IN_HOUR)
/*initialize alarmState structure*/
static alarm alarmState = {FALSE, RESET};

/* Hours handled differently than other time values*/
static const int timeAddingConstants[PRECISION-1] =
{MINUTES_IN_HOUR,SECONDS_IN_MINUTE,TENTHS_IN_SECOND};

/*
 * @brief   sets or clears alarmState structure
 * @param   [in] cmd: string containing the arguments for the command
 * @return  int return used as a boolean value,
 *          if returns 1 the command was successful;
 *          if 0 it failed
 * @details if cmd string is null the alarmState is disabled
 *          otherwise, the string is passed to parseClock in Utilities.c module
 *          validity of each time value is checked; FAILURE is returned if not valid
 *          alarmState.enabled is set
 *          time in tenths of a second calculated
 *          Alarm set string printed to screen
 *
 */
int setAlarm(char* cmd)
{
    int valid = TRUE;
    /*set to forbidden so values that are set to zero are skipped in parseClock*/
    int tmpAlarm[PRECISION] = {FORBIDDEN,FORBIDDEN,FORBIDDEN,FORBIDDEN};

    spaceFilter(cmd);                        //get rid of white space; stated in specifications
/*  if:
 *       command is empty: no arguments passed; turn off alarm
 *       command not empty: process arguments
 */
    if(!*cmd)
    {
        alarmState.enabled = FALSE;
        printString("\n\rAlarm cleared");
        return valid;
    }
    /* check all values are:
     *                        1. valid digit characters
     *                        2. within specified limits
     */
    valid =(    parseClock(cmd,tmpAlarm)&&
                BOUNDARY_CHECK(tmpAlarm[TENTHS],TENTHS_LIMIT)&&
                BOUNDARY_CHECK(tmpAlarm[SECONDS],SECONDS_MINUTES_LIMIT)&&
                BOUNDARY_CHECK(tmpAlarm[MINUTES],SECONDS_MINUTES_LIMIT)&&
                BOUNDARY_CHECK(tmpAlarm[HOURS],HOURS_LIMIT));

    if(valid)
    {
        alarmState.enabled = TRUE; //alarm enabled
        setTenthsRemaining(tmpAlarm);// time in value of tenths of a second
        printAlarmTime(tmpAlarm);// print to screen
    }
    return valid;
}

/*
 * @brief   converts digital time into time in tenths of a second
 * @param   [in] int* alarmTime: digital time in array
 * @details using time in tenths of a second makes updating remaining
 *          time as simple as decrementing a variable, not worrying about
 *          digital time values
 */
void setTenthsRemaining(int * alarmTime)
{
    alarmState.remainingTenths =
                    alarmTime[TENTHS]+
                    alarmTime[SECONDS]*TENTHS_IN_SECOND+
                    alarmTime[MINUTES]*TENTHS_IN_MINUTE+
                    alarmTime[HOURS]*TENTHS_IN_HOUR;
}

/*
 * @brief   adds the alarm time to current time and prints to screen
 * @param   [in] int* alarmTime: digital time in array
 * @details the alarm parameter is the time from current time that the
 *          user desires an alarm to go off. This shows what time the alarm
 *          will go off
 */
void printAlarmTime(int* alarmTime)
{
    int i;
    const int* time = getTime();

    /*      PRECISION-1 because were starting
     *      at tenths and decrementing
     */
    for(i=PRECISION-1;HOURS<i;i--)
    {
         alarmTime[i] += time[i];
         if(alarmTime[i] > timeAddingConstants[i-1])
         {
             alarmTime[i]-=timeAddingConstants[i-1];
             alarmTime[i+1]++;
         }
    }

    //handle hours differently because it doesn't have to carry
    alarmTime[HOURS] += time[HOURS];
    alarmTime[HOURS] = alarmTime[HOURS]%HOURS_IN_DAY;
    printString("\n\rAlarm set for: ");
    printTime(alarmTime);
}

/*
 * @brief   Decrements alarm, checks if alarm is up
 * @details If alarm is enabled, decrement remainingTenths, if
 *          remainingTenths is 0, disable alarm, print to screen.
 */
void alarmCheck(void)
{
    if(alarmState.enabled)
    {
         alarmState.remainingTenths--;
         if(alarmState.remainingTenths<=ALARM_TRIGGER)
         {
             alarmState.enabled = FALSE;
             printString("\n\rALARM * ");
             printTime(getTime());
             printString(" *");
     /*     Need to print the command arrow
      *     because called from ISR not process
      *     function in main
      */
             printString(COMMAND_PROMPT);
         }
   }
}
