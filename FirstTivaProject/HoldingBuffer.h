/*
 * HoldingBuffer.h
 *
 *  Created on: Sep 24, 2019
 *      Author: Liam MacDonald
 */
#pragma once
#define MAX_BUFFER 80
typedef struct holdingBuffer_
{
    char buffer[MAX_BUFFER];
    int writePtr;
} holdingBuffer;

#ifndef GLOBAL_HOLDINGBUFFER
#define GLOBAL_HOLDINGBUFFER


        extern holdingBuffer holdingBuf;
        extern int add(char);
        extern int remove(void);
        extern char* empty(void);
#else

        int add(char);
        int remove(void);
        char* empty(void);

#endif// GLOBAL_HOLDINGBUFFER
