/*
 * @file    Alarm.h
 * @details Contains all alarm function prototypes
 *          and the alarm structure definition
 *          Uses header guards so extern definitions
 *          aren't used in Alarm.c module
 * @author  Liam JA MacDonald
 * @date    5-Oct-2019 (Created)
 * @date    9-Oct-2019 (Last Modified)
 */

#pragma once

/*
 * @brief   Alarm structure
 * @details Holds all variables needed for alarms
 *          state.
 *          int enabled:        1 when an alarm is set
 *                              0 when no alarm set
 *          int remainingTenths Amount of time in tenths
 *                              of a second until alarm goes
 *                              off
 *          Set by setAlarm function in Alarm.c
 *          module. Updated by alarmCheck in Alarm.c
 *          module.
 */
typedef struct alarm_
{
    int enabled;
    int remainingTenths;
} alarm;

#ifndef GLOBAL_ALARM
#define GLOBAL_ALARM

    extern int setAlarm(char*);
    extern void alarmCheck(void);

#else

    void setTenthsRemaining(int *);
    void printAlarmTime(int*);

#endif /* GLOBAL_ALARM */
