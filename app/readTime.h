/*
 * adcHandle.h
 *
 *  Created on: 2011-12-24
 *      Author: ZhangQiangSheng
 */

#ifndef READTIME_H_
#define READTIME_H_


#define I2CTIMEOUT 300
//FM31256寄存器定义
#define FM31_FLAGS_CONTROL 0
#define FM31_CAL_CONTROL 1
#define FM31_SECONDS 2
#define FM31_MINUTES 3
#define FM31_HOURS 4
#define FM31_DAY_WEEK 5
#define FM31_DATE_MONTH 6
#define FM31_MONTHS 7
#define FM31_YEARS 8
#define FM31_WRT_FLAGS 9
#define FM31_WATCHDOG_CONTROL 0xa
#define DIS_6INT __asm__ volatile("disi #0x3FFF") /* disable interrupts */
#define EN_6INT __asm__ volatile("disi #0x0000") /* enable interrupts */

typedef struct {
	u8 second;
	u8 minute;
	u8 hour;
	u8 date;
	u8 month;
	u8 yearsL;
	u8 yearsH;
} TimeBCD, *pTimeBCD;

typedef struct {
	u8 second2;
	u8 second;
	u8 minute;
	u8 hour;
	u8 date;
	u8 month;
	u8 yearsL;
} TimeBIN, *pTimeBIN;

// 从FM31256中读取时间到内存
void i2cReadTime(pTimeBIN pt);
//设置时间：0-设置成功，其他为失败。
u8 i2cSetTime(pTimeBIN pt);
/*
 * 写数据到FM31256的存储器
 * memAddr，存储器起始地址
 * pData，数据起始地址
 * len，数据长度
 * */
void i2cWriteMemory(u16 memAddr, u8* pData, u8 len);
/*
 * 读数据到FM31256的存储器,这个函数运行是比较稳定的
 * memAddr，存储器起始地址
 * pData，数据起始地址
 * len，数据长度
 * */
void i2cReadMemory(u16 memAddr, u8* pData, u8 len);
//复位看门狗
void I2cWdtReset();
//FM31256寄存器配置函数
void i2cTimeInit();
/*
 * 连续清除EEPROM中的数据。
 * memAddr-开始地址，len-长度。
 * */
void i2cClearMemory(u16 memAddr, u8 len);

void i2cReadTimeToU16(u16* ptime);

#endif /* ADCHANDLE_H_ */
