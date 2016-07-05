#ifndef PACKET_H
#define	PACKET_H

#include <xc.h>
#include <stdint.h>
#include "myutils.h"
#include "io_define.h"

#ifdef	__cplusplus
extern "C" {
#endif

#define SEND_HALF_BYTE_TIMEOUT  5
void send_half_byte(uint8_t value, uint8_t low) 
{
    GET_4_BITS_FROM_CHAR(value, low, DATA_OUT3, DATA_OUT2, DATA_OUT1, DATA_OUT0);
    FLASH_DOWN(DATA_OUT_TRIGGER); 
}

void send_byte(uint8_t c)
{
    send_half_byte(c, 1);
    __delay_ms(5);
    send_half_byte(c, 0);
    __delay_ms(5);
}

    
void send_string(uint8_t *str, uint8_t len)
{
    for(uint8_t i = 0; i < len; i++)
    {
        send_byte(str[i]);
    }
}


#ifdef	__cplusplus
}
#endif

#endif	/* PACKET_H */

