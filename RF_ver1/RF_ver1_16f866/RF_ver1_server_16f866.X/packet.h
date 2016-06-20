#ifndef PACKET_H
#define	PACKET_H

#include <xc.h>
#include <stdint.h>
#include "lcd_hd44780_pic16.h"
#include "myutils.h"

#ifdef	__cplusplus
extern "C" {
#endif


#define SEND_HALF_BIT(value, low, d3, d2, d1, d0, trigger) { \
                                            GET_4_BITS_FROM_CHAR(value, low, d3, d2, d1, d0); \
                                            FLASH(trigger); }
#define SEND_BYTE(c, d3, d2, d1, d0, trigger) \
{ \
    SEND_HALF_BIT(c, 1, d3, d2, d1, d0, trigger); \
    __delay_ms(10); \
    SEND_HALF_BIT(c, 0, d3, d2, d1, d0, trigger); \
    __delay_ms(10); \
}

#define SEND_STRING(str, len, d3, d2, d1, d0, trigger) \
{ \
    for(char i = 0; i < len; i++) \
    { \
        SEND_BYTE(str[i], d3, d2, d1, d0, trigger); \
    } \
}

#define RECEIVE_BYTE(c, d3, d2, d1, d0, trigger) \
{ \
    while(trigger == 0) \
    { \
        GET_CHAR_FROM_4_BITS(c, 1, d3, d2, d1, d0); \
        __delay_ms(1); \
    } \
    while(trigger == 0) \
    { \
        GET_CHAR_FROM_4_BITS(c, 0, d3, d2, d1, d0); \
        __delay_ms(1); \
    } \
}
#define RECEIVE_STRING(str, d3, d2, d1, d0, trigger) \
{ \
    RECEIVE_BYTE(str[0], d3, d2, d1, d0, trigger); \
    for(uint8_t i = 1; i < str[0]; i++) \
    { \
        RECEIVE_BYTE(str[i], d3, d2, d1, d0, trigger); \
    } \
}

    
#ifdef	__cplusplus
}
#endif

#endif	/* PACKET_H */

