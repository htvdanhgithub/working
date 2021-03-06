/* 
 * File:   myutils.h
 * Author: Avinash
 *
 * Created on 6 June, 2013, 12:30 PM
 */

#ifndef MYUTILS_H
#define	MYUTILS_H

#include <xc.h>
#include <stdint.h>

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
    
#define MAKE_CHAR_FROM_4_BITS(c, b3, b2, b1, b0) \
{ \
    c = 0; \
    BITbits_t *byte = (BITbits_t *)&c; \
    byte->B0 = b0; \
    byte->B1 = b1; \
    byte->B2 = b2; \
    byte->B3 = b3; \
}
    
#define COPY_CHAR_FROM_4_BITS(c, low, d) \
{ \
    BITbits_t *byte1 = (BITbits_t *)&c; \
    BITbits_t *byte2 = (BITbits_t *)&d; \
    if(low == 1) \
    { \
        byte1->B0 = byte2->B0; \
        byte1->B1 = byte2->B1; \
        byte1->B2 = byte2->B2; \
        byte1->B3 = byte2->B3; \
    } \
    else \
    { \
        byte1->B4 = byte2->B0; \
        byte1->B5 = byte2->B1; \
        byte1->B6 = byte2->B2; \
        byte1->B7 = byte2->B3; \
    } \
}

#define GET_4_BITS_FROM_CHAR(c, low, b3, b2, b1, b0)    \
{ \
    BITbits_t *byte = (BITbits_t *)&c; \
    if(low == 1) \
    { \
        b0 = byte->B0; \
        b1 = byte->B1; \
        b2 = byte->B2; \
        b3 = byte->B3; \
    } \
    else \
    { \
        b0 = byte->B4; \
        b1 = byte->B5; \
        b2 = byte->B6; \
        b3 = byte->B7; \
    } \
}
#define CLONE_4_BITS(a3, a2, a1, a0, b3, b2, b1, b0)    {a3 = b3; a2 = b2; a1 = b1; a0 = b0;}
   
#define FLASH(x)    {x = ~x; __delay_us(1); x = ~x;}
#define FLASH_DOWN(x)    {x = 0; __delay_us(1); x = 1;}
#define FLASH_UP(x)    {x = 1; __delay_us(1); x = 0;}
    
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
    





#define DEBUG(msg) {LCDWriteStringXYCLEAR(0, 1, msg);}

extern int8_t compare_4_bits(uint8_t byte1, uint8_t byte2, uint8_t low);

#ifdef	__cplusplus
}
#endif

#endif	/* MYUTILS_H */

