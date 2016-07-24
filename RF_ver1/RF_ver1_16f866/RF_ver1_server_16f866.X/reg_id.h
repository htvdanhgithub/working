#ifndef REG_ID_H
#define	REG_ID_H

#include <xc.h>
#include <string.h>
#include <stdint.h>
#include "myutils.h"
#include "connection.h"
#include "msg.h"
#include "debug.h"
#include "cmd.h"

#ifdef	__cplusplus
extern "C" {
#endif

#define REG_ID_RQT_CMD_SIZE 1
#define REG_ID_RSP_CMD_SIZE 1

typedef struct {
    uint8_t     id;
} REG_ID_RQT_CMD_t; 

typedef struct {
    uint8_t     id;
} REG_ID_RSP_CMD_t; 

#if CLIENT_SIDE
void create_REG_ID_RQT_CMD(Connection_t *pconn, const REG_ID_RQT_CMD_t *prqt, Msg_t *pmsg)
{
    create_cmd(pconn, REG_ID_RQT, pconn->msgid++, prqt, REG_ID_RQT_CMD_SIZE, pmsg);
}
void extract_REG_ID_RSP_CMD(const Msg_t *pmsg, REG_ID_RSP_CMD_t *prsp)
{
    memcpy((void *)prsp, (void *)pmsg->data, REG_ID_RSP_CMD_SIZE);
}
uint8_t send_REG_ID_RQT_CMD_and_wait(Connection_t *pconn, const REG_ID_RQT_CMD_t *prqt)
{
    Msg_t msg;
    create_REG_ID_RQT_CMD(pconn, prqt, &msg);
    send_msg(&msg);
//    dump_msg(&msg);
    __delay_ms(200);
    
    if((get_msg(pmsg_rcv) == YES) 
        && (crc_verify(pmsg_rcv) == YES)
        && (is_right_addr(pconn, pmsg_rcv) == YES)
        && (pmsg_rcv->cmd == REG_ID_RSP) 
        && (msg.msgid == pmsg_rcv->msgid))
    {
        pconn->available = YES;
        dump_msg(pmsg_rcv);

        return YES; 
    }
    return NO;
}

#endif
#if SERVER_SIDE
void extract_REG_ID_RQT_CMD(const Msg_t *pmsg, REG_ID_RQT_CMD_t *prqt)
{
    memcpy((void *)prqt, (void *)pmsg->data, REG_ID_RQT_CMD_SIZE);
}

void create_REG_ID_RSP_CMD(Connection_t *pconn, Msg_t *pmsgi, Msg_t *pmsgo)
{
    REG_ID_RSP_CMD_t rsp;
    REG_ID_RQT_CMD_t rqt;

    extract_REG_ID_RQT_CMD(pmsgi, &rqt);
    rsp.id = rqt.id;
    
    create_cmd(pconn, REG_ID_RSP, pmsgi->msgid, &rsp, REG_ID_RSP_CMD_SIZE, pmsgo);

}
void handle_REG_ID_RQT_CMD(Msg_t *pmsgi)
{
    Connection_t *pconn = find_conn_entry(pmsgi->to, pmsgi->from);

    if(pconn != NULL)
    {
        Msg_t msgo;
        create_REG_ID_RSP_CMD(pconn, pmsgi, &msgo);
        pconn->available = YES;
        send_msg(&msgo);
//        dump_msg(&msgo);
    }
    
}
#endif
#ifdef	__cplusplus
}
#endif

#endif	/* REG_ID_H */

