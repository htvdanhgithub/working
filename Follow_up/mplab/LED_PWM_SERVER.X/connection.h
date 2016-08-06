#ifndef CONNECTION_H
#define	CONNECTION_H

#include <xc.h>
#include <string.h>
#include <stdint.h>
#include "myutils.h"
#include "msg.h"
#include "common.h"


#ifdef	__cplusplus
extern "C" {
#endif

typedef struct {
    uint8_t     from;
    uint8_t     to;
    uint8_t     msgid;
    uint8_t     heart_beat_count;
    uint8_t     available;
} Connection_t; 

Connection_t client_conn;


#ifdef	__cplusplus
}
#endif

#endif	/* CONNECTION_H */

