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

uint8_t is_right_addr(Connection_t *pconn, Msg_t *pmsg)
{
    
    return ((pconn->from == pmsg->to) && (pconn->to == pmsg->from));
}

#ifdef	__cplusplus
}
#endif

#endif	/* CMD_H */

