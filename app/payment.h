/*
 * uart2.h
 *
 *  Created on: 2011-12-24
 *      Author: ZhangQiangSheng
 */

#ifndef UART2_H_
#define UART2_H_

#define ADD_VALUE				0x33
#define DI3					0x90
#define DI1					0x00
#define DI0					0x00
#define CMD_READ_CARD			0x01
#define CMD_VERIFY_PWD			0x02
#define CMD_SET_CHARGE_MODE	0x03
#define CMD_START_CHARGE		0x04
#define CMD_STOP_CHARGE		0x05
#define CMD_SET_TIME			0x06
#define CMD_REALTIME_INFO		0x07
#define CMD_SETTLEMENT			0x08
#define CMD_ERROR_INFO			0x09
#define CMD_SETTLEMENT_INFO	0x10
#define CMD_POP_CARD			0x11
#define CMD_READ_PRICE			0x13
#define CMD_READ_VER			0x14

void uart2Init();
unsigned char asciiToDec(unsigned char asc);
void u2rxDataHandle();
void sendDataToCom(unsigned char w142);

void payReadCard();

#endif /* UART2_H_ */
