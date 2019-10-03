/*
 * VT100.c
 *
 *  Created on: Sep 22, 2019
 *      Author: LiamMacDonald
 */
#define GLOBAL_VT100
#include "VT100.h"

#define ONES 1
#define TENS 0

cursor cursorPosition = {ESC, '[', '0', '0', ';', '0', '0', 'H', NUL};

void forward(cursor* cp)
{
    if((cp->col[ONES]=='4')&&(cp->col[TENS]=='2'))
    {
        cp->col[ONES]='0';
        cp->col[TENS]='0';
    }
    else if(cp->col[ONES]<'9')
        {
            cp->col[ONES]++;
        }
        else
        {
            cp->col[ONES]='0';
            cp->col[TENS]++;
        };

}

void backward(cursor* cp)
{
    if((cp->col[ONES]=='0')&&(cp->col[TENS]=='0'))
    {
        cp->col[ONES]='4';
        cp->col[TENS]='2';
    }
    else if(cp->col[ONES]>'0')
        {
            cp->col[ONES]--;
        }
        else
            {
                cp->col[ONES]='9';
                cp->col[TENS]--;
            };
}

void down(cursor* cp)
{
    if((cp->line[ONES]=='0')&&(cp->line[TENS]=='8'))
    {
        cp->line[TENS]='0';
    }
    else if(cp->col[ONES]<'9')
        {
            cp->line[ONES]++;
        }
        else
            {
                cp->line[ONES]='0';
                cp->line[TENS]++;
            };

}

void up(cursor* cp)
{
    if((cp->line[ONES]=='0')&&(cp->line[TENS]=='0'))
    {
        cp->line[TENS]='8';
    }
    else if(cp->col[ONES]>'0')
        {
            cp->line[ONES]--;
        }
        else
            {
                cp->line[ONES]='9';
                cp->line[TENS]--;
            };

}
