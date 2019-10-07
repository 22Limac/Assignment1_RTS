/*
 * Time.h
 *
 *  Created on: Sep 23, 2019
 *      Author: Liam MacDonald
 */
#pragma once
#include    "Utilities.h"

#ifndef GLOBAL_TIME
#define GLOBAL_TIME

    extern void updateTenths(void);
    extern int setTime(char*);
    extern int time[PRECISION];

#else

    void updateTenths(void);
    void updateSeconds(void);
    void updateMinutes(void);
    void updateHours(void);

#endif //GLOBAL_TIME
