/*
 * readTime.c
 *
 *  Created on: 2011-12-22
 *      Author: ZhangQiangSheng
 *
 */
#include <i2c.h>
#include "includes.h"

static void i2cWriteRtc(u8 address, u8 data);
static u8 i2cReadRtc(u8 address);
static void init_i2c(void);
void IdleI2C(void);

//I2C初始化函数
static void init_i2c(void) {
	u16 config2, config1;
	//u8 *wrptr;
	/* Baud rate is set for 100 Khz */
//config2 = 0x11;
//config2 = 0x48;   //100KHZ
	config2 = 0x48; //test
	/* Configure I2C for 7 bit address mode */
	config1 = (I2C_ON & I2C_IDLE_CON & I2C_CLK_HLD & I2C_IPMI_DIS & I2C_7BIT_ADD & I2C_SLW_EN & I2C_SM_DIS & I2C_GCALL_DIS & I2C_STR_DIS & I2C_NACK
			& I2C_ACK_DIS & I2C_RCV_DIS & I2C_STOP_DIS & I2C_RESTART_DIS & I2C_START_DIS);

	OpenI2C(config1, config2);
}
//启动条件使能位,停止条件使能位,接收使能位,应答序列使能位,发送状态位
void IdleI2C(void) {
	u16 aa;
	aa = 0;
	while ((I2CCONbits.SEN || I2CCONbits.PEN || I2CCONbits.RCEN || I2CCONbits.ACKEN || I2CSTATbits.TRSTAT) && (aa++ < I2CTIMEOUT))
		;
}
/*
 * FM31256寄存器配置函数
 * */
void i2cTimeInit() {
	u8 tbuf[sizeof(TimeBIN)];
	pTimeBIN pt = (pTimeBIN) &tbuf;

	init_i2c();
	i2cWriteRtc(0xa, 0x9e); //看门狗溢出时间3s，
	i2cWriteRtc(1, 0); //配置寄存器
	i2cWriteRtc(0xb, 6); //低电压复位动作值3.9V，允许充电
	i2cReadTime(pt);

	if ((pt->yearsL > 99) && (pt->month > 12) && (pt->date > 31) && (pt->hour > 23) && (pt->minute > 59) && (pt->second > 59)) {
		pt->yearsL = 13;
		pt->month = 3;
		pt->date = 1;
		pt->hour = 0;
		pt->minute = 0;
		pt->second = 0;
		i2cSetTime(pt);
	}
}
void bcdTimeToBin(pTimeBIN bin, pTimeBCD bcd) {
	bin->yearsL = ((bcd->yearsL & 0xf0) >> 4) * 10 + (bcd->yearsL & 0x0f);
	bin->month = ((bcd->month & 0xf0) >> 4) * 10 + (bcd->month & 0x0f);
	bin->date = ((bcd->date & 0xf0) >> 4) * 10 + (bcd->date & 0x0f);
	bin->hour = ((bcd->hour & 0xf0) >> 4) * 10 + (bcd->hour & 0x0f);
	bin->minute = ((bcd->minute & 0xf0) >> 4) * 10 + (bcd->minute & 0x0f);
	bin->second = ((bcd->second & 0xf0) >> 4) * 10 + (bcd->second & 0x0f);
}
void binTimeToBcd(pTimeBCD bcd, pTimeBIN bin) {
	bcd->yearsH = 0x20;
	bcd->yearsL = ((bin->yearsL / 10) << 4) + bin->yearsL % 10;
	bcd->month = ((bin->month / 10) << 4) + bin->month % 10;
	bcd->date = ((bin->date / 10) << 4) + bin->date % 10;
	bcd->hour = ((bin->hour / 10) << 4) + bin->hour % 10;
	bcd->minute = ((bin->minute / 10) << 4) + bin->minute % 10;
	bcd->second = ((bin->second / 10) << 4) + bin->second % 10;
}
void i2cReadTime(pTimeBIN pt) {
	u8 data;
	i2cWriteRtc(FM31_FLAGS_CONTROL, 1); //开始读时间
	data = i2cReadRtc(FM31_YEARS);
	pt->yearsL = ((data & 0xf0) >> 4) * 10 + (data & 0x0f);
	data = i2cReadRtc(FM31_MONTHS);
	pt->month = ((data & 0xf0) >> 4) * 10 + (data & 0x0f);
	data = i2cReadRtc(FM31_DATE_MONTH); //
	pt->date = ((data & 0xf0) >> 4) * 10 + (data & 0x0f);
	data = i2cReadRtc(FM31_HOURS);
	pt->hour = ((data & 0xf0) >> 4) * 10 + (data & 0x0f);
	data = i2cReadRtc(FM31_MINUTES);
	pt->minute = ((data & 0xf0) >> 4) * 10 + (data & 0x0f);
	data = i2cReadRtc(FM31_SECONDS);
	pt->second = ((data & 0xf0) >> 4) * 10 + (data & 0x0f);
	i2cWriteRtc(FM31_FLAGS_CONTROL, 0); //结束读时间
}
void i2cReadTimeToU16(u16* ptime) {
	TimeBIN t;
	i2cReadTime(&t);
	*ptime++ = t.yearsL;
	*ptime++ = t.month;
	*ptime++ = t.date;
	*ptime++ = t.hour;
	*ptime++ = t.minute;
	*ptime++ = t.second;
}
u8 i2cSetTime(pTimeBIN pt) {
	u8 data;
	if ((pt->yearsL < 99) && (pt->month < 13) && (pt->date < 32) && (pt->hour < 24) && (pt->minute < 60) && (pt->second < 60)) {
		data = i2cReadRtc(FM31_FLAGS_CONTROL);
		data |= 0x02;
		i2cWriteRtc(0x00, data);
		data = ((pt->yearsL / 10) << 4) + pt->yearsL % 10;
		i2cWriteRtc(FM31_YEARS, data);
		data = ((pt->month / 10) << 4) + pt->month % 10;
		i2cWriteRtc(FM31_MONTHS, data);
		data = ((pt->date / 10) << 4) + pt->date % 10;
		i2cWriteRtc(FM31_DATE_MONTH, data);
		data = ((pt->hour / 10) << 4) + pt->hour % 10;
		i2cWriteRtc(FM31_HOURS, data);
		data = ((pt->minute / 10) << 4) + pt->minute % 10;
		i2cWriteRtc(FM31_MINUTES, data);
		data = ((pt->second / 10) << 4) + pt->second % 10;
		i2cWriteRtc(FM31_SECONDS, data);
		data = i2cReadRtc(0x00);
		data &= 0xfd;
		i2cWriteRtc(0x00, data);
		return 0;
	} else {
		return 1;
	}
}

/*
 * 读取从机上的数据，
 * address-从机里的寄存器地址
 * */
static u8 i2cReadRtc(u8 address) {
	u8 data;
	u16 aa;
	DIS_6INT;
	IdleI2C(); //该函数产生等待条件直到I2C 总线空闲为止             ******sw:需改为等待超时退出！！！

	StartI2C(); //产生开始条件
//等待开始条件完成
	aa = 0;
	while (I2CCONbits.SEN && (aa++ < I2CTIMEOUT))
		; //在主器件启动序列结束时由硬件清零。

//发送从机地址,写操作
	IdleI2C();
	MasterWriteI2C(0xd0); //1101 X A1 A0 R/W
	aa = 0;
	while (I2CSTATbits.TBF && (aa++ < I2CTIMEOUT))
		;
	aa = 0;
	while (I2CSTATbits.ACKSTAT && (aa++ < I2CTIMEOUT))
		;

//寄存器地址
	IdleI2C();
	MasterWriteI2C(address);
	while (I2CSTATbits.TBF && (aa++ < I2CTIMEOUT))
		;
	aa = 0;
	while (I2CSTATbits.ACKSTAT && (aa++ < I2CTIMEOUT))
		;

//产生I2C 总线重复启动条件
	IdleI2C();
	RestartI2C(); //产生I2C 总线重复启动条件
	while (I2CCONbits.RSEN && (aa++ < I2CTIMEOUT))
		;

////1101 X A1 A0 R/W\  //读
	IdleI2C();
	MasterWriteI2C(0xd1);
	aa = 0;
	while (I2CSTATbits.ACKSTAT && (aa++ < I2CTIMEOUT))
		;

//读数据
	IdleI2C();
	data = MasterReadI2C(); //存在查RCEN的等待！！！！

	NotAckI2C();
	aa = 0;
	while (I2CCONbits.ACKEN && (aa++ < I2CTIMEOUT))
		;

	IdleI2C(); //屏蔽则芯片坏？？？！！！！
	StopI2C();
	/* Wait till stop sequence is completed */
	while (I2CCONbits.PEN && (aa++ < I2CTIMEOUT))
		;
	EN_6INT;
	return data;
}
/*
 * 写数据到从机的寄存器
 * address-寄存器地址
 * data-数据
 * */
static void i2cWriteRtc(u8 address, u8 data) {
	u16 aa;

	DIS_6INT;
	IdleI2C(); //该函数产生等待条件直到I2C 总线空闲为止
	StartI2C(); //产生I2C 总线启动条件
	/* Wait till Start sequence is completed */
	while (I2CCONbits.SEN && (aa++ < I2CTIMEOUT))
		;

//rtc,写操作
	IdleI2C();
	MasterWriteI2C(0xd0);
	aa = 0;
	while (I2CSTATbits.TBF && (aa++ < I2CTIMEOUT))
		;
	aa = 0;
	while (I2CSTATbits.ACKSTAT && (aa++ < I2CTIMEOUT))
		;
//地址位
	IdleI2C();
	MasterWriteI2C(address);
	aa = 0;
	while (I2CSTATbits.TBF && (aa++ < I2CTIMEOUT))
		;
	aa = 0;
	while (I2CSTATbits.ACKSTAT && (aa++ < I2CTIMEOUT))
		;

//写入数据
	IdleI2C();
	MasterWriteI2C(data);
	aa = 0;
	while (I2CSTATbits.TBF && (aa++ < I2CTIMEOUT))
		;
	aa = 0;
	while (I2CSTATbits.ACKSTAT && (aa++ < I2CTIMEOUT))
		;

	IdleI2C();
	StopI2C();
//I2CCON|=0X0004;
	/* Wait till stop sequence is completed */
	while (I2CCONbits.PEN && (aa++ < I2CTIMEOUT))
		;
	EN_6INT;
}

void i2cReadMemory(u16 memAddr, u8* pData, u8 len) {

	u16 aa;
	DIS_6INT;
	IdleI2C();
	StartI2C();
	aa = 0;
	while (I2CCONbits.SEN && (aa++ < I2CTIMEOUT))
		;
//寄存器写指令
	IdleI2C();
	MasterWriteI2C(0xa0);
	aa = 0;
	while (I2CSTATbits.TBF && (aa++ < I2CTIMEOUT))
		;
	aa = 0;
	while (I2CSTATbits.ACKSTAT && (aa++ < I2CTIMEOUT))
		;
//地址高位
	IdleI2C();
	aa = 0;
	MasterWriteI2C((u8) (memAddr >> 8));
	while (I2CSTATbits.TBF && (aa++ < I2CTIMEOUT))
		;
	aa = 0;
	while (I2CSTATbits.ACKSTAT && (aa++ < I2CTIMEOUT))
		;
//地址低位
	IdleI2C();
	MasterWriteI2C((u8) memAddr);
	aa = 0;
	while (I2CSTATbits.TBF && (aa++ < I2CTIMEOUT))
		;
	aa = 0;
	while (I2CSTATbits.ACKSTAT && (aa++ < I2CTIMEOUT))
		;
//重复启动
	IdleI2C();
	RestartI2C();
	aa = 0;
	while (I2CCONbits.RSEN && (aa++ < I2CTIMEOUT))
		;
//寄存器读指令
	IdleI2C();
	MasterWriteI2C(0xa1);
	aa = 0;
	while (I2CSTATbits.TBF && (aa++ < I2CTIMEOUT))
		;
	aa = 0;
	while (I2CSTATbits.ACKSTAT && (aa++ < I2CTIMEOUT))
		;

	IdleI2C();
	MastergetsI2C(len, pData, I2CTIMEOUT);
	IdleI2C();
	StopI2C();
	aa = 0;
	while (I2CCONbits.PEN && (aa++ < I2CTIMEOUT))
		;
	EN_6INT;
}

void i2cWriteMemory(u16 memAddr, u8* pData, u8 len) {

	u16 aa;
	u16 i;

	DIS_6INT;
	IdleI2C();
	StartI2C();
	aa = 0;
	while (I2CCONbits.SEN && (aa++ < I2CTIMEOUT))
		;

//发送从机地址,写操作
	IdleI2C();
	MasterWriteI2C(0xa0); //访问存储器
	aa = 0;
	while (I2CSTATbits.TBF && (aa++ < I2CTIMEOUT))
		;
	aa = 0;
	while (I2CSTATbits.ACKSTAT && (aa++ < I2CTIMEOUT))
		;
//地址高位
	IdleI2C();
	MasterWriteI2C((u8) (memAddr >> 8));
	while (I2CSTATbits.TBF && (aa++ < I2CTIMEOUT))
		;
	aa = 0;
	while (I2CSTATbits.ACKSTAT && (aa++ < I2CTIMEOUT))
		;
//地址低位
	IdleI2C();
	MasterWriteI2C((u8) memAddr);
	while (I2CSTATbits.TBF && (aa++ < I2CTIMEOUT))
		;
	aa = 0;
	while (I2CSTATbits.ACKSTAT && (aa++ < I2CTIMEOUT))
		;

	for (i = 0; i < len; i++) {
		IdleI2C();
		MasterWriteI2C(*pData);
		pData++;
		aa = 0;
		while (I2CSTATbits.TBF && (aa++ < I2CTIMEOUT))
			;
		aa = 0;
		while (I2CSTATbits.ACKSTAT && (aa++ < I2CTIMEOUT))
			;
	}

	IdleI2C();
	StopI2C();
	aa = 0;
	while (I2CCONbits.PEN && (aa++ < I2CTIMEOUT))
		;
	EN_6INT;
}

void I2cWdtReset() {
	ClrWdt()
	;
	i2cWriteRtc(0x9, 0xa);
}

void i2cClearMemory(u16 memAddr, u8 len) {

	u16 aa;
	u16 i;

	DIS_6INT;
	IdleI2C();
	StartI2C();
	aa = 0;
	while (I2CCONbits.SEN && (aa++ < I2CTIMEOUT))
		;

//发送从机地址,写操作
	IdleI2C();
	MasterWriteI2C(0xa0); //访问存储器
	aa = 0;
	while (I2CSTATbits.TBF && (aa++ < I2CTIMEOUT))
		;
	aa = 0;
	while (I2CSTATbits.ACKSTAT && (aa++ < I2CTIMEOUT))
		;
//地址高位
	IdleI2C();
	MasterWriteI2C((u8) (memAddr >> 8));
	while (I2CSTATbits.TBF && (aa++ < I2CTIMEOUT))
		;
	aa = 0;
	while (I2CSTATbits.ACKSTAT && (aa++ < I2CTIMEOUT))
		;
//地址低位
	IdleI2C();
	MasterWriteI2C((u8) memAddr);
	while (I2CSTATbits.TBF && (aa++ < I2CTIMEOUT))
		;
	aa = 0;
	while (I2CSTATbits.ACKSTAT && (aa++ < I2CTIMEOUT))
		;

	for (i = 0; i < len; i++) {
		IdleI2C();
		MasterWriteI2C(0x0);
		aa = 0;
		while (I2CSTATbits.TBF && (aa++ < I2CTIMEOUT))
			;
		aa = 0;
		while (I2CSTATbits.ACKSTAT && (aa++ < I2CTIMEOUT))
			;
	}

	IdleI2C();
	StopI2C();
	aa = 0;
	while (I2CCONbits.PEN && (aa++ < I2CTIMEOUT))
		;
	EN_6INT;
}
