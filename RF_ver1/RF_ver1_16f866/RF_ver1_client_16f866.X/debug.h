#ifndef DEBUG_H
#define	DEBUG_H

#include	<stdio.h>
#include	<stdarg.h>

#include "lcd_hd44780_pic16.h"
#ifdef	__cplusplus
extern "C" {
#endif

#define DEBUG_LINE 1
    
#define DEBUG_INT(value, len) {LCDWriteInt(value, len);}
#define DEBUG_INT_X(x, value, len) {LCDWriteIntXY(x, DEBUG_LINE, value, len);}
#define DEBUG_INT_X_CLEAR(x, value, len) {LCDWriteIntXYCLEAR(x, DEBUG_LINE, value, len);}
#define DEBUG_INT_CLEAR(value, len) {DEBUG_INT_X_CLEAR(0, value, len);}
    
#define DEBUG_STRING(msg) {LCDWriteString(msg);}
#define DEBUG_STRING_X(x, msg) {LCDWriteStringXY(x, DEBUG_LINE, msg);}
#define DEBUG_STRING_X_CLEAR(x, msg) {LCDWriteStringXYCLEAR(x, DEBUG_LINE, msg);}
#define DEBUG_STRING_CLEAR(msg) {DEBUG_STRING_X_CLEAR(0, msg);}

#define DEBUG_LINE_CLEAR LCDClearLine(DEBUG_LINE)
            
char sdebug[32];    
#define debug_print DEBUG_LINE_CLEAR; DEBUG_STRING_X(0, sdebug);

void debug_1(uint8_t v1)
{
    sprintf(sdebug, "%d", v1);
    debug_print;
}
void debug_2(uint8_t v1, uint8_t v2)
{
    sprintf(sdebug, "%d,%d", v1, v2);
    debug_print;
}
void debug_3(uint8_t v1, uint8_t v2, uint8_t v3)
{
    sprintf(sdebug, "%d,%d,%d", v1, v2, v3);
    debug_print;
}
void debug_4(uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4)
{
    sprintf(sdebug, "%d,%d,%d,%d", v1, v2, v3, v4);
    debug_print;
}
void debug_5(uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5)
{
    sprintf(sdebug, "%d,%d,%d,%d,%d", v1, v2, v3, v4, v5);
    debug_print;
}
#ifdef	__cplusplus
}
#endif

#endif	/* DEBUG_H */

