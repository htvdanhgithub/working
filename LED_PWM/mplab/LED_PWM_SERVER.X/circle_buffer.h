#ifndef CIRCLE_BUFFER_H
#define	CIRCLE_BUFFER_H

#include <xc.h>
#include <stdint.h>
#include "myutils.h"

#ifdef	__cplusplus
extern "C" {
#endif

const char start_mark[4] = {234, 235, 236, 237};
const char stop_mark[4] = {237, 236, 235, 234};

#ifdef	__cplusplus
}
#endif

#endif	/* CIRCLE_BUFFER_H */

