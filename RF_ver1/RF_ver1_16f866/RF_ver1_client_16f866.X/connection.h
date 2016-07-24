#ifndef CONNECTION_H
#define	CONNECTION_H

#include <xc.h>
#include <string.h>
#include <stdint.h>
#include "myutils.h"
#include "msg.h"
#include "debug.h"
#include "common.h"


#ifdef	__cplusplus
extern "C" {
#endif

#define MAX_CLIENT_CONNECTION   8
#define SERVER_ID                MAX_CLIENT_CONNECTION
#define MAX_HEART_BEAT_COUNT   5

typedef struct {
    uint8_t     from;
    uint8_t     to;
    uint8_t     msgid;
    uint8_t     heart_beat_count;
    uint8_t     available;
} Connection_t; 

#if SERVER_SIDE
Connection_t client_conn[MAX_CLIENT_CONNECTION];
#endif

#if CLIENT_SIDE
Connection_t server_conn;
#endif

void create_msg_header(Connection_t *pconn, Msg_t *pmsg)
{
    pmsg->from = pconn->from;
    pmsg->to = pconn->to;
    pmsg->msgid = pconn->msgid++;
}
void dump_conn(Connection_t *pconn)
{
    char s[32];
    sprintf(s, "C:%d,%d,%d,%d", pconn->from, pconn->to, pconn->msgid, pconn->available);
    DEBUG_LINE_CLEAR; DEBUG_STRING_X(0, s);
}
#if SERVER_SIDE
Connection_t* find_conn_entry(uint8_t from, uint8_t to)
{
    for(uint8_t i = 0; i < MAX_CLIENT_CONNECTION; i++)
    {
        if((client_conn[i].from == from) && (client_conn[i].to == to))
        {
            return &client_conn[i];
        }
    }
    return NULL;
}
#endif
#ifdef	__cplusplus
}
#endif

#endif	/* CONNECTION_H */

