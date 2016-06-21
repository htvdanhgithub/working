#ifndef MSG_H
#define	MSG_H

#include <xc.h>
#include <string.h>
#include <stdint.h>
#include "lcd_hd44780_pic16.h"
#include "myutils.h"
#include "packet.h"

#ifdef	__cplusplus
extern "C" {
#endif

typedef enum E_cmd
{
    REG_ID,
    CMD_MAX    
};

#define MAX_DATA_LEN 16

typedef struct {
    uint8_t msglen;
    uint8_t from;
    uint8_t to;
    uint8_t msgid;
    uint8_t cmd;
    uint8_t data[MAX_DATA_LEN];
} Msg_t; 

#define SEND_MSG(msg, d3, d2, d1, d0, trigger) {uint8_t *s = (uint8_t *)msg; SEND_STRING(s, msg->msglen, d3, d2, d1, d0, trigger);}
#define RECEIVE_MSG(msg, d3, d2, d1, d0, trigger) {uint8_t *s = (uint8_t *)msg; RECEIVE_STRING(s, d3, d2, d1, d0, trigger);}

void compose(Msg_t *pmsg, 
        uint8_t from,
        uint8_t to,
        uint8_t msgid,
        uint8_t cmd,
        uint8_t *data,
        uint8_t datalen)
{
    register size_t len = datalen;
    pmsg->from = from;
    pmsg->to = to;
    pmsg->msgid = msgid;
    pmsg->cmd = cmd;
    memcpy((void *)pmsg->data, (void *)data, len);
    pmsg->msglen = datalen + 5;
}
#ifdef	__cplusplus
}
#endif

#endif	/* MSG_H */

