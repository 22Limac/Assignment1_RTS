/*
 * @file    CommandTable.c
 * @brief   Defines the commandTable.
 *          Contains functionality to identify command
 *          passed from holding buffer and call its respective
 *          function with arguments
 * @author  Liam JA MacDonald
 * @date    24-Sep-2019 (created)
 * @date    9-Oct-2019 (modified)
 */
#include "Time.h"
#include "Date.h"
#include "Alarm.h"
#include <string.h>
#define GLOBAL_COMMANDTABLE
#include "CommandTable.h"

/* local constants used only in this module*/
#define TIME_DATE_STRING_LENGTH 4
#define ALARM_STRING_LENGTH     5
#define NUMBER_OF_COMMANDS 3

/*  define the commandTable as an array of type
 *  command with a size of three, as that is the
 *  current number of commands
 */
static const command commandTable[NUMBER_OF_COMMANDS] =
{
     {"TIME",TIME_DATE_STRING_LENGTH,setTime},
     {"DATE",TIME_DATE_STRING_LENGTH,setDate},
     {"ALARM",ALARM_STRING_LENGTH,setAlarm}
};

/*
 * @brief   Match command string and pass arguments to it's
 *          intended function
 * @param   [in, out] cmd: string passed from holding buffer.
 *          chars following the command string passed to the
 *          respective function as a parameter
 * @return  int return used as a boolean value,
 *          returns 1 the command was matched and executed successfully;
 *          if 0 it wasn't matched or execution failed
 * @details the cmd strings first 4 or 5 characters are compared
 *          to the commandType strings in the command table
 *          if matched the chars following the command string
 *          are passed to the respective function
 *
 */
int process(char* cmd)
{
    int count = RESET;
    while(count<NUMBER_OF_COMMANDS)
    {
        if(!strncmp(cmd,commandTable[count].cmdType,commandTable[count].length))
        {
            return(commandTable[count].execute(cmd+commandTable[count].length));
        }
        count++;
    }
    return FAILURE;
}





