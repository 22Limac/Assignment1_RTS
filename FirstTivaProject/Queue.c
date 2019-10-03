/*
 * Queue.c
 *
 *  Created on: Sep 20, 2019
 *      Author: Liam MacDonald
 */
#include <string.h>
#define GLOBAL_QUEUES
#include "Queue.h"
#include "Utilities.h"
#include "UART.h"
#define NUL 0x00


queue intQueues[QUEUE_AMT] ={{{0},0,0},{{0},0,0}};

int enqueue(int queueType,interruptType it)
{

    if((queueType)&&(intQueues[queueType].writePtr == intQueues[queueType].readPtr))//buffer is empty
    {
           forceOutput(it.data);
           return 0;
    }
    unsigned int tmpPtr = (intQueues[queueType].writePtr+1)&(MAX_QSIZE-1);
    if((tmpPtr == intQueues[queueType].readPtr)){return 0;}//FULL

    intQueues[queueType].fifo[intQueues[queueType].writePtr]= it;//put character in queue and increment write ptr
    intQueues[queueType].writePtr =tmpPtr;


    return 1;

}

int dequeue(int queueType,interruptType* it)
{

   if((intQueues[queueType].writePtr == intQueues[queueType].readPtr))//buffer is empty
    {
        return 0;
    }


    it->data = intQueues[queueType].fifo[intQueues[queueType].readPtr].data;
    it->type = intQueues[queueType].fifo[intQueues[queueType].readPtr].type;

    intQueues[queueType].readPtr=(intQueues[queueType].readPtr+1)&(MAX_QSIZE-1);

    return 1;
}



