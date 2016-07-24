#ifndef HEART_BEAT_H
#define	HEART_BEAT_H

#include <xc.h>
#include <string.h>
#include <stdint.h>
#include "myutils.h"
#include "connection.h"
#include "msg.h"
#include "debug.h"
#include "cmd.h"
#include "common.h"

#ifdef	__cplusplus
extern "C" {
#endif

#define HEART_BEAT_RQT_CMD_SIZE 1
#define HEART_BEAT_RSP_CMD_SIZE 1

typedef struct {
    uint8_t     id;
} HEART_BEAT_RQT_CMD_t; 

typedef struct {
    uint8_t     id;
} HEART_BEAT_RSP_CMD_t; 

#if SERVER_SIDE
void create_HEART_BEAT_RQT_CMD(Connection_t *pconn, const HEART_BEAT_RQT_CMD_t *prqt, Msg_t *pmsg)
{
    create_cmd(pconn, HEART_BEAT_RQT, pconn->msgid++, prqt, HEART_BEAT_RQT_CMD_SIZE, pmsg);
}
void extract_HEART_BEAT_RSP_CMD(const Msg_t *pmsg, HEART_BEAT_RSP_CMD_t *prsp)
{
    memcpy((void *)prsp, (void *)pmsg->data, HEART_BEAT_RSP_CMD_SIZE);
}
uint8_t send_HEART_BEAT_RQT_CMD_and_wait(Connection_t *pconn, const HEART_BEAT_RQT_CMD_t *prqt)
{
    Msg_t msg;
    create_HEART_BEAT_RQT_CMD(pconn, prqt, &msg);
    send_msg(&msg);
//    dump_msg(&msg);
    __delay_ms(200);
    
    if((get_msg(pmsg_rcv) == YES) 
        && (crc_verify(pmsg_rcv) == YES)
        && (is_right_addr(pconn, pmsg_rcv) == YES)
        && (pmsg_rcv->cmd == HEART_BEAT_RSP) 
        && (msg.msgid == pmsg_rcv->msgid))
    {
        pconn->heart_beat_count = 0;
//        dump_msg(pmsg_rcv);

        return YES; 
    }
    pconn->heart_beat_count++;
    if(pconn->heart_beat_count == MAX_HEART_BEAT_COUNT)
    {
        pconn->available = NO;
        pconn->heart_beat_count = 0;
    }
    return NO;
}

#endif
#if CLIENT_SIDE
void extract_HEART_BEAT_RQT_CMD(const Msg_t *pmsg, HEART_BEAT_RQT_CMD_t *prqt)
{
    memcpy((void *)prqt, (void *)pmsg->data, HEART_BEAT_RQT_CMD_SIZE);
}

void create_HEART_BEAT_RSP_CMD(Connection_t *pconn, Msg_t *pmsgi, Msg_t *pmsgo)
{
    HEART_BEAT_RSP_CMD_t rsp;
    HEART_BEAT_RQT_CMD_t rqt;

    extract_HEART_BEAT_RQT_CMD(pmsgi, &rqt);
    rsp.id = rqt.id;
    
    create_cmd(pconn, HEART_BEAT_RSP, pmsgi->msgid, &rsp, HEART_BEAT_RSP_CMD_SIZE, pmsgo);

}
void handle_HEART_BEAT_RQT_CMD(Msg_t *pmsgi)
{
    Msg_t msgo;
    server_conn.available = YES;
    create_HEART_BEAT_RSP_CMD(&server_conn, pmsgi, &msgo);
    send_msg(&msgo);
    dump_msg(&msgo);
}
#endif
#ifdef	__cplusplus
}
#endif

#endif	/* HEART_BEAT_H */

