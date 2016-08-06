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

#define RGB_DATA_RQT_CMD_SIZE 3

typedef struct {
    uint8_t     r;
    uint8_t     g;
    uint8_t     b;
} RGB_DATA_RQT_CMD_t; 

void extract_RGB_DATA_RQT_CMD(const Msg_t *pmsg, uint8_t *duty)
{
    RGB_DATA_RQT_CMD_t *prqt;
    prqt = (RGB_DATA_RQT_CMD_t *)pmsg->data;
    duty[0] = prqt->r;
    duty[1] = prqt->g;
    duty[2] = prqt->b;
    
}

#ifdef	__cplusplus
}
#endif

#endif	/* RGB_DATA_H */

