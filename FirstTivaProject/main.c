/*
 * main.c
 *
 *  Created on: Sep 23, 2019
 *      Author: LiamMacDonald
 */
#include <string.h>
#include <ctype.h>
#include "Queue.h"
#include "VT100.h"
#include "UART.h"
#include "SysTick.h"
#include "Time.h"
#include "HoldingBuffer.h"
#include "Utilities.h"
#include "CommandTable.h"

#define ENTER 0x0d
#define BS 0x08
#define NUL 0x00
#define AST 0x2a
#define INPUT 0
#define OUTPUT 1

void InterruptMasterEnable(void);
void printChar(char);
void printString(char*);

void main (void)
{
    interruptType inData ={NULL};
    /* Initialize UART */
    UART0_Init();           // Initialize UART0
    InterruptEnable(INT_VEC_UART0);       // Enable UART0 interrupts
    UART0_IntEnable(UART_INT_EOT|UART_INT_RX | UART_INT_TX); // Enable Receive and Transmit interrupts
    SysTickPeriod(TENTH_WAIT);
    SysTickIntEnable();
    SysTickStart();
    enable();     // Enable Master (CPU) Interrupts
    char * cmd;
    printString("\n\r>");
    while(1)
    {
        /* Wait for input data */
        while(!(dequeue(INPUT,&inData)));

            switch(inData.type)
            {
            case UART :
                    /* Input data - xmit directly */
                switch(inData.data)
                {
                case ENTER:
                    cmd = empty();
                    if(process(cmd))
                    {

                        printString("\n\r>");
                    }
                    else
                    {
                        printString("\n\r?\n\r>");
                    }
                    break;
                case BS:
                    if(remove()){printString("\b \b");}
                    break;
                default:
                    enqueue(OUTPUT,inData);
                    add(toupper(inData.data));
                }
                break;
            case SYSTICK:
                updateTenths();
                break;
            default:
                break;
            }

    }
}




