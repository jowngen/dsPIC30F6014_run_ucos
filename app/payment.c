/*
 * uart2.c
 *
 *  Created on: 2011-12-24
 *      Author: ZhangQiangSheng
 *      与通讯板通信程序
 */

#include "includes.h"

#define STO_LEN	13
const u8 sto[STO_LEN] = { 0xFE, 0xFE, 0xFE, 0xFE, 0x68, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x68, 0x05 };
static u8 rxd2Buf[100];
static u8 txd2Buf[100];
static UartTag uart2;

/*
 * 与通讯板通信程序初始化
 * */
void uart2Init() {
	//UARTX 波特率寄存器
	U2BRG = 0x33;
	//U2RXIP<2:0>：  UART2 接收器中断优先级位
	IPC6bits.U2RXIP = 0b010;
	//U2TXIP<2:0>：  UART2发送器中断优先级位
	IPC6bits.U2TXIP = 0b001;
	//UARTX 模式寄存器
	U2MODE = 0x8800;
	//UARTX 状态和控制寄存器
	U2STA = 0x8400;
	//UART1 接收器中断标志状态位
	IFS1bits.U2RXIF = 0;
	//UART1发送器中断标志状态位
	IFS1bits.U2TXIF = 0;
	//UART1接收器中断允许位
	IEC1bits.U2RXIE = 1;
	//UART1发送器中断允许位
	IEC1bits.U2TXIE = 1;
	uart2.resBegin = 0;
	uart2.resLen = 0;
	uart2.resFinish = 0;
	uart2.enableSend = 0;
	uart2.faultPtr = 0;
	uart2.pRxdBuf = (u8 *) &rxd2Buf;
	uart2.pTxdBuf = (u8 *) &txd2Buf;
}
void startSend(u8 len) {
	u8 bcc = 0, i;
	for (i = 4; i < len; i++) {
		bcc += txd2Buf[i];
	}
	txd2Buf[len++] = bcc; //校验
	txd2Buf[len++] = 0x16; //结束符
	uart2.txdptr = 1;
	uart2.txdlen = len;
	uart2.enableSend = 1;
	U2TXREG = 0xFE;
}
void payReadCard() {
	u8 len = STO_LEN;
	memCpy(&txd2Buf, &sto, STO_LEN);
	txd2Buf[len++] = 4;
	txd2Buf[len++] = DI0 + ADD_VALUE;
	txd2Buf[len++] = DI1 + ADD_VALUE;
	txd2Buf[len++] = CMD_READ_CARD + ADD_VALUE;
	txd2Buf[len++] = DI3 + ADD_VALUE;
	startSend(len);
}
void payVerityPwd(u32 pwd) {
	u8 len = STO_LEN;
	memCpy(&txd2Buf, &sto, STO_LEN);
	txd2Buf[len++] = 7;
	txd2Buf[len++] = DI0 + ADD_VALUE;
	txd2Buf[len++] = DI1 + ADD_VALUE;
	txd2Buf[len++] = CMD_VERIFY_PWD + ADD_VALUE;
	txd2Buf[len++] = DI3 + ADD_VALUE;
	txd2Buf[len++] = (u8) pwd + ADD_VALUE;
	txd2Buf[len++] = (u8) (pwd >> 8) + ADD_VALUE;
	txd2Buf[len++] = (u8) (pwd >> 16) + ADD_VALUE;
	startSend(len);
}
/* 30aa
 * 处理从通讯板接收到的数据
 * */
void u2rxDataHandle() {
	unsigned char i, sum, len;
	unsigned char di0, di1, di2, di3;
	if (uart2.resFinish != 0) {
		uart2.faultPtr = 0;
		uart2.uartState = 0;
		len = rxd2Buf[9] + 10; //包括起始符、控制码等，共10个。
		while (len--) {
			sum += rxd2Buf[i++];
		}
		if (rxd2Buf[i] == sum) {
			sum = rxd2Buf[8];
			len = rxd2Buf[9];
			di0 = rxd2Buf[10] - 0x33;
			di1 = rxd2Buf[11] - 0x33;
			di2 = rxd2Buf[12] - 0x33;
			di3 = rxd2Buf[13] - 0x33;
			switch (di2) {
			case CMD_READ_CARD: //1、充电装发送读卡,返回数据
				if (rxd2Buf[26] == 0x33) {

				} else if (rxd2Buf[26] == 0xcc) {

				} else if (rxd2Buf[26] == 0x34) {

				} else {

				}
				break;
			case CMD_VERIFY_PWD: //2、充电装发送密码确认,返回数据

				break;
			case CMD_SET_CHARGE_MODE: //3、充电装发送充电方式选择,返回数据

				break;
			}
		}
		uart2.resFinish = 0;
	}
}

/*
 * 与通讯板通信程序
 * */
void __attribute__((__interrupt__, no_auto_psv)) _U2TXInterrupt() {
	unsigned int i;
	IFS1bits.U2TXIF = 0;
	if (uart2.enableSend) {
		if (uart2.txdptr > uart2.txdlen) {
			uart2.enableSend = 0;
		} else {
			for (i = 0; (i < 4) && (uart2.txdptr <= uart2.txdlen); i++) {
				U2TXREG = txd2Buf[uart2.txdptr];
				uart2.txdptr++;
			}
		}
	}
}

/*
 *
 * */
void __attribute__((__interrupt__, no_auto_psv)) _U2RXInterrupt() {
	IFS1bits.U2RXIF = 0;
	unsigned char temp;
	temp = U2RXREG;
	if (U2STAbits.OERR == 1) { //OERR：  接收缓冲器溢出错误状态位（只读 /清零）
		U2STAbits.OERR = 0; //缓冲器中所有的数据丢失
		uart2.resBegin = 0;
	} else if (U2STAbits.PERR == 1) { //bit 3 PERR：奇偶校验错误状态位（只读）
		U2STAbits.PERR = 0;
		uart2.resBegin = 0;
	} else if (U2STAbits.FERR == 1) { //bit 2 FERR：帧错误状态位（只读）
		U2STAbits.FERR = 0;
		uart2.resBegin = 0;
	} else {
		if (uart2.resFinish == 0) {
			if (uart2.resBegin == 0) {
				if (temp == 0x68) { //帧起始符
					uart2.resBegin = 1;
					uart2.resLen = 0;
					uart2.resFinish = 0;
					uart2.rxdptr = 1;
					rxd2Buf[0] = temp;
				}
			} else if (uart2.resLen == 0) {
				switch (uart2.rxdptr) {
				case 7:
					if (temp == 0x68) { //第二个帧起始符
						rxd2Buf[uart2.rxdptr++] = temp;
					} else {
						uart2.resBegin = 0;
					}
					break;
				case 9:
					rxd2Buf[uart2.rxdptr++] = temp;
					uart2.rxdlen = temp + 12;
					uart2.resLen = 1;
					break;
				default:
					rxd2Buf[uart2.rxdptr++] = temp;
					break;
				}
			} else {
				rxd2Buf[uart2.rxdptr++] = temp;
				if (uart2.rxdptr >= uart2.rxdlen) {
					uart2.resBegin = 0;
					uart2.resLen = 0;
					uart2.resFinish = 1;
				}
			}
		}
	}
}

