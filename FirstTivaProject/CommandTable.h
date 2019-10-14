/*
 * @file    CommandTable.h
 * @details Contains process function prototype
 *          and the command structure definition
 * @author  Liam JA MacDonald
 * @date    24-Sep-2019 (Created)
 * @date    9-Oct-2019 (Last Modified)
 */

#pragma once

/*
 * @brief   Command structure
 * @details Holds all variables needed to identify
 *          and execute a command.
 *          char* cmdType: command string
 *          int length: length of the command string
 *          int (*execute)(char*): function pointer that points
 *                                 to the function to call on a
 *                                 successful match
 */
typedef struct command_
{
    char* cmdType;
    int length;
    int (*execute)(char*);
}command;

#ifndef GLOBAL_COMMANDTABLE
#define GLOBAL_COMMANDTABLE

    extern int process(char*);

#endif //GLOBAL_COMMANDTABLE
