/* 
 * File:   lcd_hd44780_pic16.h
 * Author: Avinash
 *
 * Created on 6 June, 2013, 11:51 AM
 */

#ifndef LCD_HD44780_PIC16_H
#define	LCD_HD44780_PIC16_H

#include <xc.h>
#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif


/************************************************
	LCD CONNECTIONS
*************************************************/

//LCD Data Port
//Port PD0-PD3 are connected to D4-D7
#define LCD_DATA        C   //Port PC2-PC5 are connected to D4-D7
#define LCD_DATA_POS    4

//Register Select (RS)
//RS is connected to Port C bit 0
#define LCD_RS_PORT     C
#define LCD_RS_POS      1

//Read/Write (RW)
//RW is connected to Port A bit 4
#define LCD_RW_PORT     C
#define LCD_RW_POS      2

//Enable signal (E)
//E is connected to Port C bit 1
#define LCD_E_PORT      C
#define LCD_E_POS       3

/***********************************************

LCD Type Selection
Uncomment Just one of them

************************************************/

//#define LCD_TYPE_202	//For 20 Chars by 2 lines

//#define LCD_TYPE_204	//For 20 Chars by 4 lines

#define LCD_TYPE_162	//For 16 Chars by 2 lines

//#define LCD_TYPE_164	//For 16 Chars by 4 lines


//************************************************




//************************************************

#define LS_BLINK 0B00000001
#define LS_ULINE 0B00000010
#define LS_NONE	 0B00000000



/***************************************************
			F U N C T I O N S
****************************************************/



void LCDInit(uint8_t style);
void LCDSetStyle(uint8_t style);
int8_t LCDWriteString(const char *msg);
int8_t LCDWriteInt(int val,int8_t field_length);
void LCDGotoXY(uint8_t x,uint8_t y);

//Low level
void LCDByte(uint8_t,uint8_t);
#define LCDCmd(c) (LCDByte(c,0))
#define LCDData(d) (LCDByte(d,1))

void LCDBusyLoop();

/***************************************************
			F U N C T I O N S     E N D
****************************************************/


/***************************************************
	M A C R O S
***************************************************/
#define LCDClear() LCDCmd(0b00000001)
#define LCDHome()  LCDCmd(0b00000010)

#define LCDWriteStringXY(x,y,msg) {\
 LCDGotoXY(x,y);\
 LCDWriteString(msg);\
}

#define LCDWriteStringXYCLEAR(x,y,msg) {\
    LCDGotoXY(x,y);\
    int8_t count = LCDWriteString(msg);\
    for(int8_t i = count + x; i < 16; i++) \
    { \
       LCDData(' '); \
    } \
}

#define LCDWriteIntXY(x,y,val,fl) {\
 LCDGotoXY(x,y);\
 LCDWriteInt(val,fl);\
}

#define LCDWriteIntXYCLEAR(x,y,val,fl) {\
    LCDWriteIntXY(x,y,val,fl);\
    for(int8_t i = fl + x; i < 16; i++) \
    { \
       LCDData(' '); \
    } \
}

#define LCDClearLine(x) {LCDWriteStringXY(0, x, "", 1);}

/***************************************************/




/*_________________________________________________________________________________________*/

#ifdef	__cplusplus
}
#endif

#endif	/* LCD_HD44780_PIC16_H */

