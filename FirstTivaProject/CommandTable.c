/*
 * CommandTable.c
 *
 *  Created on: Sep 24, 2019
 *      Author: Liam MacDonald
 */
#include "Time.h"
#include "Date.h"
#include <string.h>
#define GLOBAL_COMMANDTABLE
#include "CommandTable.h"


command commandTable[NUMBER_OF_COMMANDS] =
{
                                           {"time",4,setTime},
                                           {"date",4,setDate},
                                           {0}
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





