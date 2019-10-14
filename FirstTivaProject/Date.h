/*
 * @file    Alarm.h
 * @details Contains all alarm function prototypes
 *          and the alarm structure definition
 *          Uses header guards so extern definitions
 *          aren't used in Alarm.c module
 * @author  Liam JA MacDonald
 * @date    2-Oct-2019 (Created)
 * @date    9-Oct-2019 (Last Modified)
 */

#pragma once

/*
 * @brief   date structure
 * @details Holds all variables needed for date
 *          state.
 *          int day:    holds current day
 *          int month:  holds current month
 *          int year:   holds current year
 *          Set by setDate function in Date.c module.
 *          Each member variable has an update function
 */
typedef struct date_
{
    int day;
    int month;
    int year;
}date;

#ifndef GLOBAL_DATE
#define GLOBAL_DATE

extern int setDate(char*);
extern void updateDay(void);

#else

int monthNumber(char*);
int checkDate(int,int,int);
void updateMonth(void);
void updateYear(void);

#endif /* DATE_H_ */
