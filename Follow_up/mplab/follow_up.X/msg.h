#ifndef MSG_H
#define	MSG_H

#include <xc.h>
#include <string.h>
#include <stdint.h>
#include "myutils.h"
#include "packet.h"
#include "common.h"
#include "circle_buffer.h"

#ifdef	__cplusplus
extern "C" {
#endif

#define MAX_DATA_LEN 1

typedef struct {
    uint8_t     msglen;
    uint16_t    crc;
    uint8_t     from;
    uint8_t     to;
    uint8_t     msgid;
    uint8_t     cmd;
    uint8_t     data[MAX_DATA_LEN];
} Msg_t; 

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
        return YES;
    }
    return NO;
}
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

#ifdef	__cplusplus
}
#endif

#endif	/* MSG_H */

