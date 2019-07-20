
	This is uC/OS-II port to dsPIC30 microcontroller version 1.1.

	To use this software:
		- read MicroC/OS-II book
		- first get the uC/OS-II itself (http://www.ucos-ii.com/)
		- put this port in proper folder 
		  (\Micrium\SOFTWARE\uCOS-II\ports\dsPIC30\MPLAB-C30\zoran_bosnjak)
		- put your (test) application files in any folder
		- compile, assemble and link:
			- this port, 
			- uc/OS-II,
			- your application files

	This software is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	This port was partialy tested on dsPIC development board from
	Microchip (dsPIC30F6014, C30 tools, MPLAB IDE, uc/OS-II v2.76).
	task_switch_test_1 folder contains simple test with a few tasks and LED
	output. It includes also MPLAB project files.
	Main purpose of this test is to check "interrupt-level context switch"
	and "task-level context switch" (which are port-dependant).

	Please send any bug report or comment about this port 
	to <zoran.bosnjak at trio-b.si>.

	Check http://www.trio-b.si/~zoran/dsPIC_uC_OS-II_port/ 
	for updates.

