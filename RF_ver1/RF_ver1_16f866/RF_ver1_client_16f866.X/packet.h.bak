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
#define RECEIVE_HALF_BIT(value, low, d3, d2, d1, d0, trigger) \
{ \
    while(1) \
    { \
        if(trigger == 0) \
        { \
            GET_CHAR_FROM_4_BITS(value, low, d3, d2, d1, d0); \
            DEBUG_LINE_CLEAR; DEBUG_STRING_X(0, "rcv:"); DEBUG_INT(value, 3); \
            break; \
        } \
    } \
}


#define SEND_BYTE(c, d3, d2, d1, d0, trigger) \
{ \
    SEND_HALF_BIT(c, 1, d3, d2, d1, d0, trigger); \
    __delay_ms(5); \
    SEND_HALF_BIT(c, 0, d3, d2, d1, d0, trigger); \
    __delay_ms(5); \
}

#define SEND_BYTE_ACK(c, di3, di2, di1, di0, triggeri, do3, do2, do1, do0, triggero) \
{ \
    SEND_HALF_BIT(c, 1, do3, do2, do1, do0, triggero); \
    RECEIVE_HALF_BIT(c, 1, di3, di2, di1, di0, triggeri); \
    __delay_ms(5); \
    SEND_HALF_BIT(c, 0, do3, do2, do1, do0, triggero); \
    RECEIVE_HALF_BIT(c, 0, di3, di2, di1, di0, triggeri); \
    __delay_ms(5); \
}

#define SEND_STRING(str, len, d3, d2, d1, d0, trigger) \
{ \
    for(uint8_t i = 0; i < len; i++) \
    { \
        SEND_BYTE(str[i], d3, d2, d1, d0, trigger); \
    } \
}
#define SEND_STRING_ACK(str, len, di3, di2, di1, di0, triggeri, do3, do2, do1, do0, triggero) \
{ \
    for(uint8_t i = 0; i < len; i++) \
    { \
        SEND_BYTE_ACK(str[i], di3, di2, di1, di0, triggeri, do3, do2, do1, do0, triggero); \
    } \
}
    
#define RECEIVE_STRING(str, d3, d2, d1, d0, trigger) \
{ \
    uint8_t count = 0; \
    uint8_t low = 1; \
    while(1) \
    { \
        if(trigger == 0) \
        { \
            GET_CHAR_FROM_4_BITS(str[count], low, d3, d2, d1, d0); \
            low = ((low == 1) ? 0 : 1); \
            if(low == 1) \
            { \
                count++; \
                if(count == str[0]) \
                { \
                    break; \
                    count = 0; \
                } \
            } \
        } \
    } \
}    

#define RECEIVE_STRING_ACK(str, di3, di2, di1, di0, triggeri, do3, do2, do1, do0, triggero) \
{ \
    uint8_t count = 0; \
    uint8_t low = 1; \
    while(1) \
    { \
        if(triggeri == 0) \
        { \
            GET_CHAR_FROM_4_BITS(str[count], low, di3, di2, di1, di0); \
            SEND_HALF_BIT(c, 1, do3, do2, do1, do0, triggero); \            
            low = ((low == 1) ? 0 : 1); \
            if(low == 1) \
            { \
                count++; \
                if(count == str[0]) \
                { \
                    break; \
                    count = 0; \
                } \
            } \
            DEBUG_LINE_CLEAR; DEBUG_STRING_X(0, "RCV:"); DEBUG_INT(pmsg->data[2], 3); \
        } \
    } \
}    
#ifdef	__cplusplus
}
#endif

#endif	/* PACKET_H */

