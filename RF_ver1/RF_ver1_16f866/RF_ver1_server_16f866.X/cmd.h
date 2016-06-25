#ifndef CMD_H
#define	CMD_H

#include <xc.h>
#include <string.h>
#include <stdint.h>
#include "myutils.h"
#include "connection.h"
#include "msg.h"
#include "debug.h"

#ifdef	__cplusplus
extern "C" {
#endif

typedef enum E_cmd
{
    REG_ID_RQT,
    REG_ID_RSP,
    CMD_MAX    
};

typedef struct {
    uint8_t     your_id;
} REG_ID_RQT_CMD_t; 
#define REG_ID_RQT_CMD_SIZE 1

typedef struct {
    uint8_t     my_id;
} REG_ID_RSP_CMD_t; 
#define REG_ID_RSP_CMD_SIZE 1

void create_REG_ID_RQT_CMD(const Connection_t *conn, const REG_ID_RQT_CMD_t *rqt, Msg_t *pmsg)
{
    compose(pmsg, 
        conn->from,
        conn->to,
        conn->msgid++,
        REG_ID_RQT,
        (uint8_t)*rqt,
        REG_ID_RQT_CMD_SIZE);
}
void extract_REG_ID_RSP_CMD(const Msg_t *pmsg, REG_ID_RSP_CMD_t *rsp)
{
    memcpy((void *)rsp, (void *)pmsg->data, REG_ID_RSP_CMD_SIZE);

}

#define SEND_REG_ID_RQT_CMD(pmsgi, di3, di2, di1, di0, triggeri, pmsgo, do3, do2, do1, do0, triggero) \
{ \
    SEND_MSG(pmsgi, di3, di2, di1, di0, triggeri); \
    RECEIVE_MSG(pmsgo, do3, do2, do1, do0, triggero); \
}

#ifdef	__cplusplus
}
#endif

#endif	/* CMD_H */

