/* ==========================================================================*/
/* - - - - - - - - - - - - -  U A R T . H  - - - - - - - - - - - - - - - - */
/* ==========================================================================*/
/* ==========================================================================*/
/*	Created   07-1-2010   GUANPH                                      */
/*	Modified                                                  */

#ifndef UART6_H
#define UART6_H

#define MODUS_ADDR 1
#define YCBUF_LEN  300

#define UART_3 0 //¶Á¿¨Æ÷
#define UART_4 1 //¶Á¿¨Æ÷
#define UART_5 2 //¶Á¿¨Æ÷
#define UART_6 3 //´¥ÃþÆÁ
#define RHRREG 0	//½ÓÊÜ»º³åÆ÷(DLAB=0)
#define THRREG 0	//·¢ËÍ»º³åÆ÷(DLAB=0)
#define DLLREG 0	//³ýÊýËø´æÆ÷ (LSB)(DLAB=1)
#define DLMREG 1	//³ýÊýËø´æÆ÷ (MSB)(DLAB=1)
#define IERREG 1	//ÖÐ¶ÏÊ¹ÄÜ¼Ä´æÆ÷
#define IIRREG 2	//ÖÐ¶ÏÊ¶±ð¼Ä´æÆ÷(Ö»¶Á)
#define FCRREG 2	//FIFO¿ØÖÆ¼Ä´æÆ÷(Ð´)
#define LCRREG 3	//Ïß¿Ø¼Ä´æÆ÷
#define MCRREG 4	//µ÷ÖÆ½âµ÷Æ÷¿ØÖÆ¼Ä´æÆ÷
#define LSRREG 5	//Ïß×´Ì¬¼Ä´æÆ÷
#define MSRREG 6	//µ÷ÖÆ½âµ÷Æ÷×´Ì¬¼Ä´æÆ÷
#define SPRREG 7	//ÔÝ´æ(Scratch)¼Ä´æÆ÷(SCR)



void displayInit(void* yc, void* yx);
void displayCommentHandle(void);
u32 displayReadPassword();
void displayWriteValue(u16 name, u8* value, u8 len);
//
void write_ST554(u8 w2, u8 w1, u8 w0);
u8 read_ST554(u8 w1, u8 w0);
u16 crc16(u8 * w146, u8 w148);

#endif
