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
void create_REG_ID_RSP_CMD(Connection_t *pconn, const REG_ID_RSP_CMD_t *prsp, Msg_t *pmsg)
{
    compose(pmsg, 
        pconn->from,
        pconn->to,
        pconn->msgid++,
        REG_ID_RSP,
        (uint8_t *)prsp,
        REG_ID_RSP_CMD_SIZE);
}
void extract_REG_ID_RQT_CMD(const Msg_t *pmsg, REG_ID_RQT_CMD_t *prqt)
{
    memcpy((void *)prqt, (void *)pmsg->data, REG_ID_RQT_CMD_SIZE);
}
void extract_REG_ID_RSP_CMD(const Msg_t *pmsg, REG_ID_RSP_CMD_t *prsp)
{
    memcpy((void *)prsp, (void *)pmsg->data, REG_ID_RSP_CMD_SIZE);
}

//#define SERVER_REG_ID(pmsgi, pconn, prqt, prsp, di3, di2, di1, di0, triggeri, pmsgo, do3, do2, do1, do0, triggero) \
{ \
    create_REG_ID_RQT_CMD(pconn, prqt, pmsgo); \
    SEND_MSG(pmsgo, do3, do2, do1, do0, triggero); \
    RECEIVE_MSG(pmsgi, di3, di2, di1, di0, triggeri); \
    if(is_right_addr(pconn, pmsgi)) \
    { \
        extract_REG_ID_RSP_CMD(pmsgi, prsp); \
        pconn->available = YES; \
        DEBUG_LINE_CLEAR; DEBUG_STRING_X(0, "SND:"); DEBUG_INT(prsp->id, 3); \
    } \
}
#define SERVER_REG_ID(pmsgi, pconn, prqt, prsp, di3, di2, di1, di0, triggeri, pmsgo, do3, do2, do1, do0, triggero) \
{ \
    create_REG_ID_RQT_CMD(pconn, prqt, pmsgo); \
    SEND_MSG(pmsgo, do3, do2, do1, do0, triggero); \
    dum_msg(pmsgo); \
}
//#define CLIENT_REG_ID(pmsgi, pconn, di3, di2, di1, di0, triggeri, pmsgo, do3, do2, do1, do0, triggero) \
{ \
    RECEIVE_MSG(pmsgi, di3, di2, di1, di0, triggeri); \
    if(is_right_addr(pconn, pmsg)) \
    { \
        REG_ID_RQT_CMD_t rqt; \
        REG_ID_RSP_CMD_t rsp; \
        extract_REG_ID_RQT_CMD(pmsgi, &rqt); \
        rsp.id = rqt.id; \
        DEBUG_LINE_CLEAR; DEBUG_STRING_X(0, "RCV:"); DEBUG_INT(rqt.id, 3); \
        create_REG_ID_RSP_CMD(pconn, &rsp, pmsgo); \
        SEND_MSG(pmsgo, do3, do2, do1, do0, triggero); \
    } \
}
#define CLIENT_REG_ID(pmsgi, pconn, di3, di2, di1, di0, triggeri, pmsgo, do3, do2, do1, do0, triggero) \
{ \
    RECEIVE_MSG(pmsgi, di3, di2, di1, di0, triggeri); \
    { \
        REG_ID_RQT_CMD_t rqt; \
        REG_ID_RSP_CMD_t rsp; \
        extract_REG_ID_RQT_CMD(pmsgi, &rqt); \
        rsp.id = rqt.id; \
        dum_msg(pmsgi); \
    } \
}

#ifdef	__cplusplus
}
#endif

#endif	/* REG_ID_H */

