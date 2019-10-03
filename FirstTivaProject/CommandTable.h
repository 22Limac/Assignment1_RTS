/*
 * CommandTable.h
 *
 *  Created on: Sep 24, 2019
 *      Author: LiamMacDonald
 */
#define NUMBER_OF_COMMANDS 3
typedef struct command_
{
    char* cmdType;
    int length;
    int (*execute)(char*);
}command;

#ifndef GLOBAL_COMMANDTABLE
#define GLOBAL_COMMANDTABLE

    extern command commandTable[NUMBER_OF_COMMANDS];
    extern int process(char*);
#else

    int process(char*);
#endif //GLOBAL_COMMANDTABLE
