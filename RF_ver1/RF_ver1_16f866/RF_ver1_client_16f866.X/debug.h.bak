#ifndef DEBUG_H
#define	DEBUG_H

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
            
#ifdef	__cplusplus
}
#endif

#endif	/* DEBUG_H */

