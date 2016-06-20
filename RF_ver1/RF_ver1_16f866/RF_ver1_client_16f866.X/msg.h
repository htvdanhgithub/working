#ifndef MSG_H
#define	MSG_H

#include <xc.h>
#include <stdint.h>
#include "lcd_hd44780_pic16.h"
#include "myutils.h"
#include "packet.h"

#ifdef	__cplusplus
extern "C" {
#endif

typedef enum E_cmd
{
    REG_ID,
    CMD_MAX    
};

#define MAX_DATA_LEN 256

typedef struct {
    uint8_t cmd;
    uint8_t datalen;
    uint8_t data[MAX_DATA_LEN];
} Cmd_t; 

typedef struct {
    uint8_t from;
    uint8_t to;
    Cmd_t cmd;
} Msg_t; 

#define SEND_MSG(msg, d3, d2, d1, d0, trigger) SEND_STRING((uint8_t *)msg, (msg->cmd.datalen + 2), d3, d2, d1, d0, trigger)

#ifdef	__cplusplus
}
#endif

#endif	/* MSG_H */

