/* 
 * File:   myutils.h
 * Author: Avinash
 *
 * Created on 6 June, 2013, 12:30 PM
 */

#ifndef MYUTILS_H
#define	MYUTILS_H

#ifdef	__cplusplus
extern "C" {
#endif

#define _CONCAT(a,b) a##b
#define _CONCAT2(port,pos)  TRIS##port##bits.TRIS##port##pos
#define _CONCAT3(port,pos)  R##port##pos
#define _CONCAT4(port, pos) IOC##port##Pbits.IOC##port##P##pos
#define _CONCAT5(port, pos) IOC##port##Fbits.IOC##port##F##pos
#define _CONCAT6(a,b) a,##b
#define _CONCAT7(port, pos) ANSEL##port##bits.ANS##port##pos

#define PORT(x) _CONCAT(PORT,x)
#define TRIS(x) _CONCAT(TRIS,x)
#define TRISBIT(__port,__pos) _CONCAT2(__port,__pos)
#define PORTBIT(__port,__pos) _CONCAT3(__port,__pos)

#define PIN(__port,__pos)     _CONCAT6(__port,__pos)

#define IOCPBIT(__port,__pos) _CONCAT4(__port,__pos)
#define IOCFBIT(__port,__pos) _CONCAT5(__port,__pos)

#define IO_INPUT(__port,__pos) (TRISBIT(__port,__pos) = 1)
#define IO_OUTPUT(__port,__pos) (TRISBIT(__port,__pos) = 0)
    
#define ANSELBIT(__port,__pos) _CONCAT7(__port,__pos)
    
    
#define GET_CHAR_FROM_4_BITS(b3, b2, b1, b0)    (b0 | (b1 << 1) | (b2 << 2) | (b3 << 3))
#define GET_4_BITS_FROM_CHAR(c, low, b3, b2, b1, b0)    \
{ \
    char t; \
    if(low == 0) \
    { \
        t = c >> 4; \
    } \
    else \
    { \
        t = c; \
    } \
    b0 = t & 0b0001; b1 = (t & 0b0010) >> 1; b2 = (t & 0b0100) >> 2; b3 = (t & 0b1000) >> 3; \
}
#define CLONE_4_BITS(a3, a2, a1, a0, b3, b2, b1, b0)    {a3 = b3; a2 = b2; a1 = b1; a0 = b0;}
#define GET_4_BITS_FROM_STRING(ret, str, half_index)    { \
                                unsigned char index = half_index/2; \
                                if(half_index % 2 == 0) \
                                { \
                                    ret = GET_CHAR_FROM_4_BITS(str[index].B3, str[index].B2, str[index].B1, str[index].B0); \
                                } \
                                else \
                                { \
                                    ret = GET_CHAR_FROM_4_BITS(str[index].B7, str[index].B6, str[index].B5, str[index].B4); \
                                }; \
                            }
    
#define SET_4_BITS_TO_STRING(val, str, half_index)    { \
                                unsigned char index = half_index/2; \
                                if(half_index % 2 == 0) \
                                { \
                                    GET_4_BITS_FROM_CHAR(val, 1, str[index].B3, str[index].B2, str[index].B1, str[index].B0); \
                                } \
                                else \
                                { \
                                    GET_4_BITS_FROM_CHAR(val, 1, str[index].B7, str[index].B6, str[index].B5, str[index].B4); \
                                }; \
                            }
    
#define FLASH(x)    {x = ~x; __delay_us(1); x = ~x;}
    
    
typedef struct {
        unsigned B0                    :1;
        unsigned B1                    :1;
        unsigned B2                    :1;
        unsigned B3                    :1;
        unsigned B4                    :1;
        unsigned B5                    :1;
        unsigned B6                    :1;
        unsigned B7                    :1;
} BITbits_t;    
    
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

#ifdef	__cplusplus
}
#endif

#endif	/* MYUTILS_H */

