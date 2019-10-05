/*
 * HoldingBuffer.c
 *
 *  Created on: Sep 24, 2019
 *      Author: LiamMacDonald
 */
#define NUL 0x00

#define GLOBAL_HOLDINGBUFFER
#include "HoldingBuffer.h"
holdingBuffer holdingBuf={{0},0};

int add(char c)
{
    if(holdingBuf.writePtr<MAX_BUFFER)
    {
        holdingBuf.buffer[holdingBuf.writePtr++] = c;
        return 1;
    }
    return 0;
}

int remove(void)
{
    if(holdingBuf.writePtr>0)
    {
            holdingBuf.writePtr--;
            return 1;
    }
    return 0;
}

char * empty(void)
{
   add(NUL);
   holdingBuf.writePtr=0;
   return holdingBuf.buffer;
}
