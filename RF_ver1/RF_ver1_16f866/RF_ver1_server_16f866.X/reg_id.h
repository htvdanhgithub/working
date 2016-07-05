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

void create_REG_ID_RQT_CMD(Connection_t *pconn, const REG_ID_RQT_CMD_t *prqt, Msg_t *pmsg)
{
    compose(pmsg, 
        pconn->from,
        pconn->to,
        pconn->msgid++,
        REG_ID_RQT,
        (uint8_t *)prqt,
        REG_ID_RQT_CMD_SIZE);
}
void extract_REG_ID_RQT_CMD(const Msg_t *pmsg, REG_ID_RQT_CMD_t *prqt)
{
    memcpy((void *)prqt, (void *)pmsg->data, REG_ID_RQT_CMD_SIZE);
}
void extract_REG_ID_RSP_CMD(const Msg_t *pmsg, REG_ID_RSP_CMD_t *prsp)
{
    memcpy((void *)prsp, (void *)pmsg->data, REG_ID_RSP_CMD_SIZE);
}
void create_REG_ID_RSP_CMD(Connection_t *pconn, Msg_t *pmsgi, Msg_t *pmsgo)
{
    REG_ID_RSP_CMD_t rsp;
    REG_ID_RQT_CMD_t rqt;

    extract_REG_ID_RQT_CMD(pmsgi, &rqt);
    rsp.id = rqt.id;
    
    compose(pmsgo, 
        pconn->from,
        pconn->to,
        pmsgi->msgid,
        REG_ID_RSP,
        (uint8_t *)&rsp,
        REG_ID_RSP_CMD_SIZE);
}
uint8_t send_REG_ID_RQT_CMD_and_wait(Connection_t *pconn, const REG_ID_RQT_CMD_t *prqt, Msg_t *pmsg)
{
    create_REG_ID_RQT_CMD(pconn, prqt, pmsg);
    send_msg(pmsg);
    __delay_ms(50);
    
    if((get_msg(pmsg_rcv) == YES) && (pmsg_rcv->cmd == REG_ID_RSP) && (pmsg->msgid == pmsg_rcv->msgid))
    {
       return YES; 
    }
    return NO;
}
void handle_REG_ID_RQT_CMD(Connection_t *pconn, Msg_t *pmsgi)
{
    Msg_t msgo;
    create_REG_ID_RSP_CMD(pconn, pmsgi, &msgo);
    send_msg(&msgo);
}

#ifdef	__cplusplus
}
#endif

#endif	/* REG_ID_H */

