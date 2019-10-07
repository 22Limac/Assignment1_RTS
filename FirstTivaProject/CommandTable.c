/*
 * CommandTable.c
 *
 *  Created on: Sep 24, 2019
 *      Author: Liam MacDonald
 */
#include "Time.h"
#include "Date.h"
#include "Alarm.h"
#include <string.h>
#define GLOBAL_COMMANDTABLE
#include "CommandTable.h"


command commandTable[NUMBER_OF_COMMANDS] =
{
                                           {"TIME",4,setTime},
                                           {"DATE",4,setDate},
                                           {"ALARM",5,setAlarm}
};

int process(char* cmd)
{
    int count = 0;
    while(count<NUMBER_OF_COMMANDS)
    {
        if(!strncmp(cmd,commandTable[count].cmdType,commandTable[count].length))
        {
            return(commandTable[count].execute(cmd+commandTable[count].length));
        }
        count++;
    }
    return 0;
}





