/*
 * VT100.h
 *
 *  Created on: Sep 22, 2019
 *      Author: LiamMacDonald
 */
#pragma once

#define NUL 0x00
#define ESC 0x1b

/* Cursor position string */

/* Define the cursor position data structure */

typedef struct CUP
{
    char esc;
    char sqrbrkt;
    char line[2];   /* 01 through 24 */
    char semicolon;
    char col[2];    /* 01 through 80 */
    char cmdchar;
    char nul;
}cursor;

#ifndef GLOBAL_VT100
#define GLOBAL_VT100

    extern cursor cursorPosition;
    extern void forward(cursor*);
    extern void backward(cursor*);
    extern void down(cursor*);
    extern void up(cursor*);
#else
    void forward(cursor*);
    void backward(cursor*);
    void down(cursor*);
    void up(cursor*);

#endif// GLOBAL_VT100
