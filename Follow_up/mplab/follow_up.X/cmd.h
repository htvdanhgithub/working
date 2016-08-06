#ifndef CMD_H
#define	CMD_H

#include <xc.h>
#include <string.h>
#include <stdint.h>
#include "myutils.h"
#include "connection.h"
#include "msg.h"

#ifdef	__cplusplus
extern "C" {
#endif

typedef enum E_cmd
{
    RGB_DATA_RQT,
    RGB_DATA_RSP,
    CMD_MAX    
};

uint8_t is_right_addr(Connection_t *pconn, Msg_t *pmsg)
{
    
    return ((pconn->from == pmsg->to) && (pconn->to == pmsg->from));
}
void create_cmd(Connection_t *pconn, uint8_t cmd_id, uint8_t msg_id, const void *cmd_data, uint8_t cmd_data_len, Msg_t *pmsg)
{
    compose(pmsg, 
        pconn->from,
        pconn->to,
        msg_id,
        cmd_id,
        (uint8_t *)cmd_data,
        cmd_data_len);
}
#ifdef	__cplusplus
}
#endif

#endif	/* CMD_H */

