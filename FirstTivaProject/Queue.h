#pragma once
#include "InterruptType.h"

#define MAX_QSIZE 128
#define QUEUE_AMT 2
#define INPUT 0
#define OUTPUT 1

typedef struct queue_
{
    interruptType fifo[MAX_QSIZE];
    unsigned int writePtr, readPtr;

} queue;

#ifndef GLOBAL_QUEUES
#define GLOBAL_QUEUES

        extern int enqueue(int,interruptType);
        extern int dequeue(int,interruptType*);

#else

        int enqueue(int,interruptType);
        int dequeue(int,interruptType*);


#endif// GLOBAL_QUEUES
