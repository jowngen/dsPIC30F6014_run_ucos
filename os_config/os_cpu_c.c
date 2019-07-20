/*
This file is part of "uC/OS-II port to dsPIC30 microcontroller"
Copyright (C) 2004 Zoran Bosnjak <zoran.bosnjak at trio-b.si>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#include "includes.h"

/* OS C rutines */

/* stack init for new tasks */
OS_STK *OSTaskStkInit(  void (*task)(void *pd), void *pdata, OS_STK *ptos, INT16U opt) {
    INT16U x;

    /* simulate a call to my task... put dummy address on the stack (32 bits) */
    *ptos++ = (OS_STK)task; 
    *ptos++ = 0;

    /* simulate interrupt */
    *ptos++ = (OS_STK)task;
    x = (SR << 8);
    x &= 0xFF00;  
    if (CORCONbits.IPL3) {
        x |= 0x0080;
    }
    *ptos++ = x;

    /* push all registers to stack */
    *ptos++ = (OS_STK)pdata;    /* W0 */
    *ptos++ = 0x1111;
    *ptos++ = 0x2222;
    *ptos++ = 0x3333; 
    *ptos++ = 0x4444;
    *ptos++ = 0x5555;
    *ptos++ = 0x6666;
    *ptos++ = 0x7777;
    *ptos++ = 0x8888;
    *ptos++ = 0x9999;
    *ptos++ = 0xAAAA;
    *ptos++ = 0xBBBB; 
    *ptos++ = 0xCCCC;
    *ptos++ = 0xDDDD;
    *ptos++ = 0xEEEE;

    *ptos++ = ACCAL;
    *ptos++ = ACCAH;
    *ptos++ = ACCAU;
    *ptos++ = ACCBL;
    *ptos++ = ACCBH;
    *ptos++ = ACCBU;
    *ptos++ = TBLPAG;
    *ptos++ = PSVPAG;
    *ptos++ = RCOUNT;
    *ptos++ = DCOUNT;
    *ptos++ = DOSTARTL;
    *ptos++ = DOSTARTH;
    *ptos++ = DOENDL;
    *ptos++ = DOENDH;

    *ptos++ = SR;
    *ptos++ = CORCON;

    
    /* return new stack pointer */
    return ptos;
}

void OSInitHookBegin(void) {
}

void OSInitHookEnd(void) {
}

void OSTaskCreateHook(OS_TCB *ptcb) {
    ptcb = ptcb;    /* make compiler happy */
}

void OSTaskDelHook(OS_TCB *ptcb) {
    ptcb = ptcb;    /* make compiler happy */
}

void OSTaskSwHook(void) {
}

void OSTaskStatHook(void) {
}

void OSTCBInitHook(OS_TCB *ptcb) {
    ptcb = ptcb;    /* make compiler happy */
}

void OSTimeTickHook(void) {
}

void OSTaskIdleHook(void) {
}
   
