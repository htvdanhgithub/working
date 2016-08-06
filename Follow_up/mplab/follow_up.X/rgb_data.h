#ifndef RGB_DATA_H
#define	RGB_DATA_H

#include <xc.h>
#include <string.h>
#include <stdint.h>
#include "myutils.h"
#include "connection.h"
#include "msg.h"
#include "cmd.h"

#ifdef	__cplusplus
extern "C" {
#endif

#define RGB_DATA_RQT_CMD_SIZE 1

typedef struct {
    uint8_t     id;
} RGB_DATA_RQT_CMD_t; 

void create_RGB_DATA_RQT_CMD(Connection_t *pconn, const RGB_DATA_RQT_CMD_t *prqt, Msg_t *pmsg)
{
    create_cmd(pconn, RGB_DATA_RQT, pconn->msgid++, prqt, RGB_DATA_RQT_CMD_SIZE, pmsg);
}
uint8_t send_RGB_DATA_RQT_CMD(Connection_t *pconn, const RGB_DATA_RQT_CMD_t *prqt)
{
    Msg_t msg;
    create_RGB_DATA_RQT_CMD(pconn, prqt, &msg);
    send_msg(&msg);
}
#ifdef	__cplusplus
}
#endif

#endif	/* RGB_DATA_H */

