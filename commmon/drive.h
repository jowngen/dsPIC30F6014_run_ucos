/*
 * drive.h
 *
 *  Created on: 2014-8-15
 *      Author: Administrator
 */

void taskDriveTest();

//------------------硬件相关------------------------//
#define	LED2			LATDbits.LATD14  //
#define	LED3			LATDbits.LATD15  //
#define	LED4			LATFbits.LATF7   //
#define	LED5			LATFbits.LATF6
#define	LED6			LATDbits.LATD11  //
//#define	portActrl		LATCbits.LATC14 //relay1，三相交流
#define	portActrl		LATCbits.LATC3  //A口控制,relay6
#define	portAReadyLamp	LATCbits.LATC4  //A口握手灯,relay7
#define	portALamp		LATDbits.LATD13 //A口充电指示灯,relay3
#define	portBctrl		LATAbits.LATA6  //B口控制,relay4
#define	portBReadyLamp	LATAbits.LATA7  //B口握手灯,relay5
#define	portBLamp		LATDbits.LATD12 //B口充电指示灯,relay2
#define	relay1			LATCbits.LATC14 //relay1
#define	speaker			LATGbits.LATG6 //蜂鸣器
//
#define 	ST16C_RESET		LATCbits.LATC13		//st16c55d的复位
