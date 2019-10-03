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

#else

int setDate(char*);

#endif /* DATE_H_ */
