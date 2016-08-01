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
    REG_ID_RQT,
    REG_ID_RSP,
    HEART_BEAT_RQT,
    HEART_BEAT_RSP,
    CMD_MAX    
};

extern void handle_REG_ID_RQT_CMD(Msg_t *pmsgi);
extern void handle_HEART_BEAT_RQT_CMD(Msg_t *pmsgi);

uint8_t is_right_addr(Connection_t *pconn, Msg_t *pmsg)
{
    
    return ((pconn->from == pmsg->to) && (pconn->to == pmsg->from));
}

void handle_received_cmds()
{
    if(get_msg(pmsg_rcv) == YES)
    {
        switch(pmsg_rcv->cmd)
        {
#if SERVER_SIDE            
            case REG_ID_RQT:
                handle_REG_ID_RQT_CMD(pmsg_rcv);
                break;
#endif                
#if CLIENT_SIDE            
            case HEART_BEAT_RQT:
                handle_HEART_BEAT_RQT_CMD(pmsg_rcv);
                break;
#endif                
            default:
                break;
        }
//        dump_msg(pmsg_rcv);
        
    }
}
#ifdef	__cplusplus
}
#endif

#endif	/* CMD_H */

