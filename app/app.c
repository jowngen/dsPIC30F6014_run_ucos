/* This is simple test application.
 * It starts some tasks and use LEDs on Microchip
 * dsPIC development board with dsPIC30F6014 */

#include "includes.h"

static void hardwareInit();
static void timer1Init();

OS_STK StartTaskStk[64];
OS_EVENT *pevent;

u16 ycBuf[300];
u16 yxBuf[10];

void StartTask(void *pdata) {
	while (1) {
		LED2 = !LED2; /* turn ON led, don't turn it off until reset */
		i2cReadTimeToU16(((pYCBUF) pdata)->realTime);
		I2cWdtReset();

		OSTimeDly(OS_TIME_500ms);
	}
}

_FOSC(CSW_FSCM_OFF & XT_PLL4);
//_FWDT(WDT_OFF);
_FWDT(WDT_ON & WDTPSA_512 & WDTPSB_3);
//3072ms
_FBORPOR(PBOR_OFF & MCLR_EN);
_FGS(CODE_PROT_OFF);

int main(void) {
	pYCBUF pyc = (pYCBUF) &ycBuf;
	pYXBUF pyx = (pYXBUF) &yxBuf;

	OSInit();
	hardwareInit();
	i2cTimeInit();
	timer1Init(); //

	OSTaskCreate(StartTask, pyc, &StartTaskStk[0], 0);
	displayInit(pyc, pyx);
//	OSTaskCreate(dummy_task, NULL, &dummyStk[0], 20);
	pevent = OSSemCreate(0);
	OSStart();
	return 0;
}

static void portInit(void) {
	LATA = 0xF000;
	TRISA = 0xF000;
	LATB = 0xFFFF;
	TRISB = 0xFFFF;
	ADPCFG = 0x007F;
	LATC = 0x8006;
	TRISC = 0x8000;
	LATD = 0xC800;
	TRISD = 0x0;
	LATF = 0xC0;
	TRISF = 0x03F; /*原来为13F，修改后可是通过485输出数据*/
	LATG = 0xF000; /*11110000 01000000 //启动是蜂鸣器*/
	TRISG = 0x383; /*11 10000011*/
}

void timer1Init(void) {
	T1CON = 0;
	//Timer1寄存器
	TMR1 = 0;
	/*定时器将在每个指令周期递增，直到等于PR1 中预先装入的值，
	 然后复位至0，继续计数。*/
	//Timer1 周期寄存器
	PR1 = 8000000 / OS_TICKS_PER_SEC; //10000,1.25mS
	//定时器预分频器,预分频比是1:1
	T1CONbits.TCKPS = 0b00;
	// 启动定时器
	T1CONbits.TON = 1;
	//T1CON = 0x8000;
	//Timer1中断优先级位
	IPC0bits.T1IP = 6;
	//Timer1中断标志状态位
	IFS0bits.T1IF = 0;
	//Timer1中断允许位
	IEC0bits.T1IE = 1;
}

static void hardwareInit() {
	portInit();
	ST16C_RESET = 1; //16c54D复位
//	OSTimeDly(OS_TIME_10ms); //
	ST16C_RESET = 0; //16c54D复位
//	OSTimeDly(OS_TIME_10ms);  //
}

