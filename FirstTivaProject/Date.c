/*
 * Date.c
 *
 *  Created on: Oct 2, 2019
 *      Author: LiamMacDonald
 */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Utilities.h"
#define GLOBAL_DATE
#include "Date.h"

#define MONTHS_IN_YEAR 12
#define MONTH_STRING 4
#define ACCOUNT_LEAP 2
#define VALID_DATE 3
#define MAX_YEAR 9999

#define LEAPYEAR(YEAR) (YEAR%400||((YEAR%4)&&!(YEAR%100)))

const char monthStrings[MONTHS_IN_YEAR][MONTH_STRING] =
{{"JAN"},{"FEB"},{"MAR"},{"APR"},{"MAY"},{"JUN"},{"JUL"},{"AUG"},{"SEP"},{"OCT"},{"NOV"},{"DEC"}};

const int daysInMonth[MONTHS_IN_YEAR][ACCOUNT_LEAP] =
{{31,31},{28,29},{31,31},{30,30},{31,31},{30,30},{31,31},{31,31},{30,30},{31,31},{30,30},{31,31}};

date currentDate = {0,0,0};

void updateDay(void)
{
    UPDATE(currentDate.day,
           daysInMonth[currentDate.month][LEAPYEAR(currentDate.year)],
           updateMonth())
}

void updateMonth(void)
{
    UPDATE(currentDate.month,MONTHS_IN_YEAR,updateYear())
}

void updateYear(void)
{
    currentDate.year = (currentDate.year<MAX_YEAR) ? currentDate.year+1 : RESET;
}
/*
 * @brief   called from CommandTable.c module to handle
 *          date commands both with and without arguments
 * @param   [in] cmd:string containing arguments in DD-MMM-YYYY
 *          format to set Date, or empty string to display
 *          date (whitespaces are allowed)
 */
int setDate(char* cmd)
{
    int valid = TRUE;
    char monthStr[MONTH_STRING];
    date tmpDate = {0,0,0};
    spaceFilter(cmd);

    if(*cmd)
    {
        //check that three vars were set
        valid = (sscanf(cmd,"%2d-%3s-%4d",&tmpDate.day,monthStr,&tmpDate.year)==VALID_DATE) ?
                  setDay(BOUNDARY_CHECK(tmpDate.year, MAX_YEAR),
                         monthNumber(monthStr,&tmpDate.month),
                         LEAPYEAR(tmpDate.year),
                         tmpDate.day) : FALSE;

        if(!(valid)){return valid;}
        currentDate.day =tmpDate.day;
        currentDate.month =tmpDate.month;
        currentDate.year = tmpDate.year;
    }
    char tmp[20];
    sprintf(tmp,"\n\r%d-%3s-%d",currentDate.day,monthStrings[currentDate.month],currentDate.year);
    printString(tmp);
    return valid;
}

int monthNumber(char* str, int* month )
{
    int i = 0;
    while(strncmp(str,monthStrings[i],MONTH_STRING-1)&&(i<MONTHS_IN_YEAR)){i++;}
    *month = i;
    return i;
}

int setDay(int validYear, int month, int leap, int day)
{
    int valid = (validYear&&BOUNDARY_CHECK(month,MONTHS_IN_YEAR));
    if(valid){return BOUNDARY_CHECK(day,daysInMonth[month][leap]);}
    return valid;
}


