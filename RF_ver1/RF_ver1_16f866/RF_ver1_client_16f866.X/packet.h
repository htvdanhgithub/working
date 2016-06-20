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
#define SEND_STRING(str, len, d3, d2, d1, d0, trigger) \
{ \
    for(char i = 0; i < len; i++) \
    { \
        SEND_HALF_BIT(str[i], 1, d3, d2, d1, d0, trigger); \
        __delay_ms(10); \
        SEND_HALF_BIT(str[i], 0, d3, d2, d1, d0, trigger); \
        __delay_ms(10); \
    } \
}

typedef struct {
        unsigned char cmd;
        unsigned char size;
        unsigned char *data;
} Packet_t;     

#ifdef	__cplusplus
}
#endif

#endif	/* PACKET_H */

