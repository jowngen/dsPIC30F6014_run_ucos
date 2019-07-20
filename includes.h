/* this is common include file for port, uC/OS-II and app */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <ucos_ii.h>

#include "commmon/drive.h"
#include "commmon/common.h"
#include "app/readTime.h"
#include "app/display.h"

#define OS_TIME_1ms   ((INT16U)((INT32U)OS_TICKS_PER_SEC * 1L / 1000L))
#define OS_TIME_10ms  ((INT16U)((INT32U)OS_TICKS_PER_SEC * 10L / 1000L))
#define OS_TIME_100ms ((INT16U)((INT32U)OS_TICKS_PER_SEC * 100L / 1000L))
#define OS_TIME_500ms ((INT16U)((INT32U)OS_TICKS_PER_SEC * 500L / 1000L))

#include <p30f6014a.h>

