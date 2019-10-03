/*
 * Date.h
 *
 *  Created on: Oct 2, 2019
 *      Author: LiamMacDonald
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

int setDate(char*);
int monthNumber(char*, int*);
int setDay(int,int,int,int);
void updateDay(void);
void updateMonth(void);
void updateYear(void);

#endif /* DATE_H_ */
