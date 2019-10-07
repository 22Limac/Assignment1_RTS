/*
 * Alarm.h
 *
 *  Created on: Oct 5, 2019
 *      Author: LiamMacDonald
 */
typedef struct alarm_
{
    int enabled;
    int remainingTenths;
} alarm;

#ifndef GLOBAL_ALARM
#define GLOBAL_ALARM

    extern int setAlarm(char*);
    extern alarm alarmState;
    extern void alarmCheck(void);

#else
    int setAlarm(char*);
    void setTenthsRemaining(int *);
    void printAlarmTime(int*);

#endif /* GLOBAL_ALARM */
