/*
 * common.c
 *
 *  Created on: 2014-8-13
 *      Author: Administrator
 */

#include "commmon.h"

void memCpy(u8* pDst, u8* pSrc, u16 len) {
	if (pDst == NULL || pSrc == NULL || len == 0)
		return;
	while (len--)
		*pDst++ = *pSrc++;
	return;
}

u8 memComp(u8* pDst, u8* pSrc, u16 len) {
	if (pDst == NULL || pSrc == NULL || len == 0)
		return false;
	while (len--)
		if (*pDst++ != *pSrc++)
			return false;
	return true;
}

void copyU16ToU8(u8*pdst, u16*psrc, u8 len) {
	if (pdst == NULL || psrc == NULL || len == 0)
		return;
	while (len--)
		*pdst++ = (u8) *psrc++;
	return;
}

void copyU8ToU16(u16*pdst, u8*psrc, u8 len) {
	if (pdst == NULL || psrc == NULL || len == 0)
		return;
	while (len--)
		*pdst++ = *psrc++;
	return;
}

void clrMem(u8*psrc, u16 len) {
	if (psrc == NULL || len == 0)
		return;
	while (len--)
		*psrc++ = 0;
	return;
}

