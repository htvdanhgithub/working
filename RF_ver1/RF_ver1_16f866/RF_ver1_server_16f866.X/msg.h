#ifndef MSG_H
#define	MSG_H

#include <xc.h>
#include <string.h>
#include <stdint.h>
#include "lcd_hd44780_pic16.h"
#include "myutils.h"
#include "packet.h"
#include "debug.h"

#ifdef	__cplusplus
extern "C" {
#endif

#define MAX_DATA_LEN 16

typedef struct {
    uint8_t     msglen;
    uint16_t    crc;
    uint8_t     from;
    uint8_t     to;
    uint8_t     msgid;
    uint8_t     cmd;
    uint8_t     data[MAX_DATA_LEN];
} Msg_t; 

#define SEND_MSG(pmsg, d3, d2, d1, d0, trigger) {uint8_t *s = (uint8_t *)pmsg; SEND_STRING(s, pmsg->msglen, d3, d2, d1, d0, trigger);}
#define RECEIVE_MSG(pmsg, d3, d2, d1, d0, trigger) {uint8_t *smsg = (uint8_t *)pmsg; RECEIVE_STRING(smsg, d3, d2, d1, d0, trigger);}

#define SEND_MSG_ACK(msg, di3, di2, di1, di0, triggeri, do3, do2, do1, do0, triggero) {uint8_t *s = (uint8_t *)msg; SEND_STRING_ACK(s, msg->msglen, di3, di2, di1, di0, triggeri, do3, do2, do1, do0, triggero);}
#define RECEIVE_MSG_ACK(msg, di3, di2, di1, di0, triggeri, do3, do2, do1, do0, triggero) {uint8_t *smsg = (uint8_t *)&msg; RECEIVE_STRING_ACK(smsg, di3, di2, di1, di0, triggeri, do3, do2, do1, do0, triggero);}

uint16_t crc_calculate(Msg_t *pmsg)
{
    uint16_t crc;
    crc  = (uint8_t)pmsg->msglen;
    crc += (uint8_t)pmsg->from;
    crc += (uint8_t)pmsg->to;
    crc += (uint8_t)pmsg->msgid;
    crc += (uint8_t)pmsg->cmd;
    
    for(uint8_t i = 0; i < pmsg->msglen - 7; i++)
    {
        crc += (uint8_t)pmsg->data[i];
    }
    
    return crc;
}
uint8_t crc_verify(Msg_t *pmsg)
{
    return ((crc_calculate(pmsg) == pmsg->crc) ? 1 : 0);
}
void compose(Msg_t *pmsg, 
        uint8_t     from,
        uint8_t     to,
        uint8_t     msgid,
        uint8_t     cmd,
        uint8_t     *data,
        uint8_t     datalen)
{
    register size_t len = datalen;
    pmsg->from  = from;
    pmsg->to    = to;
    pmsg->msgid = msgid;
    pmsg->cmd   = cmd;
    memcpy((void *)pmsg->data, (void *)data, len);
    pmsg->msglen = datalen + 7;
    // Must be at last
    pmsg->crc  = crc_calculate(pmsg);
}
void dum_msg(Msg_t *pmsg)
{
    char s[32];
    sprintf(s, "M:%d,%d,%d,%d,%d,%d", pmsg->msglen, pmsg->crc, pmsg->from, pmsg->to, pmsg->msgid, pmsg->cmd);
    DEBUG_LINE_CLEAR; DEBUG_STRING_X(0, s);
}
#ifdef	__cplusplus
}
#endif

#endif	/* MSG_H */

