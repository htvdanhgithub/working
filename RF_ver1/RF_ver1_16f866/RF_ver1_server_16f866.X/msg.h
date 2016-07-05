#ifndef MSG_H
#define	MSG_H

#include <xc.h>
#include <string.h>
#include <stdint.h>
#include "myutils.h"
#include "packet.h"
#include "debug.h"
#include "common.h"
#include "circle_buffer.h"

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

void send_msg(Msg_t *pmsg)
{
    send_string(start_mark, 4);
    uint8_t *s = (uint8_t *)pmsg;
    send_string(s, pmsg->msglen);
    send_string(stop_mark, 4);
}

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
void dump_msg(Msg_t *pmsg)
{
    char s[32];
    sprintf(s, "M:%d,%d,%d,%d,%d,%d", pmsg->msglen, pmsg->crc, pmsg->from, pmsg->to, pmsg->msgid, pmsg->cmd);
    DEBUG_LINE_CLEAR; DEBUG_STRING_X(0, s);
}

Msg_t msg_rcv;
Msg_t *pmsg_rcv = &msg_rcv;
uint8_t *pstr_rcv = (uint8_t *)&msg_rcv;
uint8_t low_rcv = 1;
uint8_t count_rcv = 0;;

uint8_t reveive_finished()
{
    return ((count_rcv > 0) && (count_rcv == pstr_rcv[0]));
}
void reveive_reset()
{
    low_rcv = 1;
    count_rcv = 0;
}
#define reveive_timeout(ntimeout) \
{ \
    reveive_reset(); \
    __delay_ms(ntimeout); \
}

uint8_t get_msg(Msg_t* pmsg)
{
    uint8_t *pstr = (uint8_t *)pmsg;
    uint8_t start_index, end_index;
    uint8_t i = 0;
    uint8_t temp;
    if(get_msg_index(&start_index, &end_index) == YES)
    {
        temp = start_index;
        while(1)
        {
            pstr[i++] = buffer_rcv[temp];
            buffer_rcv[temp] = 0;
            if(get_distance(temp, end_index) == 0)
            {
                break;
            }
            temp = get_next_index(temp);
        }
//        debug_1(1);
        return YES;
    }
//        debug_1(0);
    return NO;
}

#ifdef	__cplusplus
}
#endif

#endif	/* MSG_H */

