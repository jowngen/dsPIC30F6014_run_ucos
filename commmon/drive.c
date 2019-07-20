/*
 * drive.c
 *
 *  Created on: 2014-8-15
 *      Author: Administrator
 */

#include "includes.h"

void taskDriveTest() {

	while (1) {
		LED5 = !LED5;
	}
	OSTimeDly(OS_TIME_100ms * 3);
}
