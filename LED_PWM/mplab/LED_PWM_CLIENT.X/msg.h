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

#define MAX_DATA_LEN 3

typedef struct {
    uint8_t     msglen;
    uint16_t    crc;
    uint8_t     from;
    uint8_t     to;
    uint8_t     msgid;
    uint8_t     cmd;
    uint8_t     data[MAX_DATA_LEN];
} Msg_t; 


Msg_t msg_rcv;
Msg_t *pmsg_rcv = &msg_rcv;
uint8_t *pstr_rcv = (uint8_t *)&msg_rcv;

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

#ifdef	__cplusplus
}
#endif

#endif	/* MSG_H */

