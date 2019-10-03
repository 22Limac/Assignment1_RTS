/*
 * Time.h
 *
 *  Created on: Sep 23, 2019
 *      Author: Liam MacDonald
 */
#pragma once

#ifndef GLOBAL_TIME
#define GLOBAL_TIME

    extern void updateTenths(void);
    extern int setTime(char*);

#else

    void updateTenths(void);
    void updateSeconds(void);
    void updateMinutes(void);
    void updateHours(void);
    void displayTime(int,char*);
    void printTime(void);
    int  myAtoi(int * num, char* str);

#endif //GLOBAL_TIME
