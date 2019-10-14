/*
 * @file    Time.h
 * @brief   Time Function Prototypes
 * @author  Liam JA MacDonald
 * @date    23-Sep-2019 (created)
 * @date    6-Oct-2019 (modified)
 */
#pragma once
#include    "Utilities.h"

#ifndef GLOBAL_TIME
#define GLOBAL_TIME

    extern void updateTenths(void);
    extern int setTime(char*);
    extern const int* getTime(void);

#else

    void updateSeconds(void);
    void updateMinutes(void);
    void updateHours(void);

#endif //GLOBAL_TIME
