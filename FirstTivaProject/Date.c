/*
 * @file    Date.c
 * @brief   Contains all date setting, updating and displaying functionality.
 *          Including argument processing, output string formatting and validity checking.
 *          Contains constant definitions only required by this module.
 * @author  Liam JA MacDonald
 * @date    2-Oct-2019 (Created)
 * @date    9-Oct-2019 (Modified)
 */
#include <string.h>
#include <stdio.h>
#include "Utilities.h"
#define GLOBAL_DATE
#include "Date.h"

/* local constants used only in this module*/
#define MONTHS_IN_YEAR 12
#define MONTH_STRING 4
#define ACCOUNT_LEAP 2
#define VALID_DATE 3
#define MAX_YEAR 9999
#define SEPT_1ST_2019 1,8,2019
#define INITIAL_DATE  SEPT_1ST_2019
#define RESET_DAY   1

/* macro for checking leap year*/
#define LEAPYEAR(YEAR) ((YEAR%400==0)||((YEAR%4==0)&&(YEAR%100!=0)))

/*  Differs from UPDATE in Utilities.h module because reset value
 *  is 1 not 0. I didn't want to have to pass lower bound
 *  to every UPDATE macro.
 */
#define UPDATE_DAY(VAL,LIM,FUNC) VAL = (VAL<LIM) ? VAL+1 : RESET_DAY;\
                                             if(VAL==RESET_DAY){FUNC;}

/*Look up table for month strings*/
static const char monthStrings[MONTHS_IN_YEAR][MONTH_STRING] =
{{"JAN"},{"FEB"},{"MAR"},{"APR"},{"MAY"},{"JUN"},{"JUL"},{"AUG"},{"SEP"},{"OCT"},{"NOV"},{"DEC"}};

/*Look up table for days in a month non-leap and leap years*/
static const int daysInMonth[MONTHS_IN_YEAR][ACCOUNT_LEAP] =
{{31,31},{28,29},{31,31},{30,30},{31,31},{30,30},{31,31},{31,31},{30,30},{31,31},{30,30},{31,31}};

/*currentDate variable defined to 1-Sep-2019*/
static date currentDate = {INITIAL_DATE};

/*
 * @brief   Increments day value of currentDate
 * @details If it's exceeded it's max value
 *          updateMonth function is called
 *          and day is reset to 1
 */
void updateDay(void)
{
    UPDATE_DAY(currentDate.day,
           daysInMonth[currentDate.month][LEAPYEAR(currentDate.year)],
           updateMonth())
}

/*
 * @brief   Increments month value of currentDate
 * @details If it's exceeded it's max value
 *          updateYear function is called
 *          and month is reset
 */
inline void updateMonth(void)
{
    UPDATE(currentDate.month, (MONTHS_IN_YEAR-1), updateYear())
}

/*
 * @brief   Increments year value of currentDate
 * @details If it's exceeded it's max value
 *          the world explodes, and year is
 *          reset
 */
inline void updateYear(void)
{
    currentDate.year = (currentDate.year<MAX_YEAR) ? currentDate.year+1 : RESET;
}

/*
 * @brief   Called from CommandTable.c module to handle
 *          date commands both with and without arguments
 * @param   [in] char* cmd: String containing arguments in DD-MMM-YYYY
 *          format to set Date, or empty string to display
 *          date (whitespaces are allowed)
 * @return  int return Used as a boolean value,
 *          if returns 1; the command was successful.
 *          if returns 0; it failed.
 * @details If cmd string is null the current date is displayed
 *          otherwise, the string is parsed be sscanf function.
 *          Validity of each date value is checked with respect to
 *          leap years, the currentDate struct is populated,
 *          new current date printed to screen
 *
 */
int setDate(char* cmd)
{
    int valid = TRUE;
    char monthStr[MONTH_STRING];
    int tmpDay = RESET, tmpYear = RESET;
    spaceFilter(cmd);

    if(*cmd)
    {
        valid = (sscanf(cmd,"%2d-%3s-%4d",&tmpDay,monthStr,&tmpYear)==VALID_DATE) ?
                 checkDate(tmpYear, monthNumber(monthStr),tmpDay) : FALSE;
        if(!(valid)){return FAILURE;}
    }
    char tmp[OUTPUT_STRING];
    sprintf(tmp,"\n\r%d-%3s-%d",currentDate.day,monthStrings[currentDate.month],currentDate.year);
    printString(tmp);
    return valid;
}

/*
 * @brief   Month string converted to respective month number
 * @param   [in] char* str: month string
 * @return  int: returns the respective month number if found
 * @details use compare month string with strings in the month
 *          string look up table if found return it's index in
 *          the month string table
 */
int monthNumber(char* str)
{
    int i = 0;
    /* MONTH_STRING-1 to exclude the NUL char on the end of the string */
    while(strncmp(str,monthStrings[i],MONTH_STRING-1)&&(i<MONTHS_IN_YEAR)){i++;}
    return i;
}

/*
 * @brief   Check validity of date values, and set currentDate
 *          if valid
 * @param   [in] char* str: month string
 * @return  int return Used as a boolean value,
 *          if returns 1; date values are all valid.
 *          if returns 0; not valid
 */
int checkDate(int year, int month, int day)
{
    int valid = (BOUNDARY_CHECK(year, MAX_YEAR)&&
                 BOUNDARY_CHECK(month,MONTHS_IN_YEAR)&&
                 ((RESET_DAY<=day)&&(day<=daysInMonth[month][LEAPYEAR(year)])));
    if(valid)
    {
        currentDate.month = month;
        currentDate.day = day;
        currentDate.year = year;
    }
    return valid;
}


