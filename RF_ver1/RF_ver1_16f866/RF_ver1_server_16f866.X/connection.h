#ifndef CONNECTION_H
#define	CONNECTION_H

#include <xc.h>
#include <string.h>
#include <stdint.h>
#include "lcd_hd44780_pic16.h"
#include "myutils.h"
#include "msg.h"
#include "debug.h"
#include "common.h"


#ifdef	__cplusplus
extern "C" {
#endif

#define MAX_CONNECTION 16

typedef struct {
    uint8_t     from;
    uint8_t     to;
    uint8_t     msgid;
    uint8_t     available;
} Connection_t; 
Connection_t g_connection[MAX_CONNECTION];

void init_conn(Connection_t *conn, uint8_t from, uint8_t to)
{
    conn->from = from;
    conn->to   = to;
}
void create_msg_header(Connection_t *conn, Msg_t *pmsg)
{
    pmsg->from = conn->from;
    pmsg->to = conn->to;
    pmsg->msgid = conn->msgid++;
}

#ifdef	__cplusplus
}
#endif

#endif	/* CONNECTION_H */

