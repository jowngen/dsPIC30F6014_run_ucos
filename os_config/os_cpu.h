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

#include <p30f6014A.h>

/* data types C30 compiler */
typedef unsigned char   BOOLEAN;
typedef unsigned char   INT8U;
typedef signed char     INT8S;
typedef unsigned int    INT16U;
typedef signed int      INT16S;
typedef unsigned long   INT32U;
typedef signed long     INT32S;
typedef float           FP32;
typedef long double     FP64;

typedef INT16U          OS_STK;     /* each stack entry size */
typedef INT16U          OS_CPU_SR;  /* size of CPU status register */

/* processor specific defines */
#define OS_CRITICAL_METHOD  3

#define OS_STK_GROWTH       0       /* stack grows towards high memory */

#define OS_TASK_SW()  {__asm__ volatile("call _OSCtxSw");}

#if OS_CRITICAL_METHOD == 1
#define OS_ENTER_CRITICAL() SRbits.IPL = 6  /* disable interrupts (all but 7) */
#define OS_EXIT_CRITICAL()  SRbits.IPL = 0  /* enable interrupts */
#endif

#if OS_CRITICAL_METHOD == 3
#define OS_ENTER_CRITICAL() {cpu_sr = SR; SRbits.IPL = 6;}
#define OS_EXIT_CRITICAL() SR = cpu_sr;



/*
*********************************************************************************************************
*                                          FUNCTION PROTOTYPES
*这是我拷贝的
* IMPORTANT: These prototypes MUST be placed in OS_CPU.H
*********************************************************************************************************
*/
//#if 0
void          OSStartHighRdy          (void);
void          OSIntCtxSw              (void);
void          OSCtxSw                 (void);
//#endif


#endif

