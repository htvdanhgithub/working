#ifndef CIRCLE_BUFFER_H
#define	CIRCLE_BUFFER_H

#include <xc.h>
#include <stdint.h>
#include "myutils.h"

#ifdef	__cplusplus
extern "C" {
#endif

#define MAX_CIRCLE_BUFFER_LEN 32
uint8_t buffer_rcv[MAX_CIRCLE_BUFFER_LEN];
uint8_t end_index_rcv;
uint8_t start_index_rcv;
uint8_t low_half_rcv = 1;

const char start_mark[4] = {234, 235, 236, 237};
const char stop_mark[4] = {237, 236, 235, 234};


#define RECEIVE_INPUT(d3, d2, d1, d0) \
{ \
    uint8_t value; \
    MAKE_CHAR_FROM_4_BITS(value, d3, d2, d1, d0); \
    receive_input(value); \
}

uint8_t get_next_index(uint8_t index)
{
    if(index == MAX_CIRCLE_BUFFER_LEN - 1)
    {
        return 0;
    }
    else
    {
        return (index + 1);
    }
}
void receive_input(uint8_t value)
{
    COPY_CHAR_FROM_4_BITS(buffer_rcv[end_index_rcv], low_half_rcv, value);
    if(low_half_rcv == 1)
    {
        low_half_rcv = 0;
    }
    else
    {
        low_half_rcv = 1;
        end_index_rcv = get_next_index(end_index_rcv);
    }
//    debug_2(start_index_rcv, end_index_rcv);
}
uint8_t get_plus_index(uint8_t index, uint8_t add)
{
    index += add;
    if(index >= MAX_CIRCLE_BUFFER_LEN)
    {
        index -= MAX_CIRCLE_BUFFER_LEN;
    }
    return index;
}
uint8_t get_minus_index(uint8_t index, uint8_t sub)
{
    if(index  < sub)
    {
        return index + MAX_CIRCLE_BUFFER_LEN - sub;
    }
    return index - sub;
}
uint8_t get_distance(uint8_t start_index, uint8_t end_index)
{
    if(end_index < start_index)
    {
        return end_index + MAX_CIRCLE_BUFFER_LEN - start_index;
    }
    else
    {
        return (end_index - start_index);
    }
}
uint8_t get_msg_index(uint8_t *start_index, uint8_t *end_index)
{
////////////////////////////////////////
//    low_half_rcv = 1;
//    start_index_rcv = 6;
//    end_index_rcv = 5;
//    memset(buffer_rcv, 0, MAX_CIRCLE_BUFFER_LEN);
//    buffer_rcv[6] = start_mark[0];
//    buffer_rcv[7] = start_mark[1];
//    buffer_rcv[8] = start_mark[2];
//    buffer_rcv[9] = start_mark[3];
//
//    buffer_rcv[2] = stop_mark[0];
//    buffer_rcv[3] = stop_mark[1];
//    buffer_rcv[4] = stop_mark[2];
//    buffer_rcv[5] = stop_mark[3];
//
//    //    memcpy(&buffer_rcv[0], start_mark, 4);
//    buffer_rcv[0] = 99;
//    buffer_rcv[1] = 55;
////    memcpy(&buffer_rcv[6], stop_mark, 4);
//////////////////////////////////////    
    uint8_t i;
    *start_index = 0xFF;
    *end_index = 0xFF;

    if(low_half_rcv == 0)
    {
        return NO;
    }
    if(get_distance(start_index_rcv, end_index_rcv) <= 7)
    {
        return NO;
    }
    i = start_index_rcv;
    while(get_distance(i, end_index_rcv) >= 3)
    {
//        debug_1(i);
//        __delay_us(500);
        if((buffer_rcv[i] == start_mark[0]) && (buffer_rcv[get_plus_index(i, 1)] == start_mark[1]) 
        && (buffer_rcv[get_plus_index(i, 2)] == start_mark[2]) && (buffer_rcv[get_plus_index(i, 3)] == start_mark[3]))
        {
            if(*start_index != -1)
            {
                *start_index = get_plus_index(i, 4);
            }
        }
        else if((buffer_rcv[i] == stop_mark[0]) && (buffer_rcv[get_plus_index(i, 1)] == stop_mark[1]) 
        && (buffer_rcv[get_plus_index(i, 2)] == stop_mark[2]) && (buffer_rcv[get_plus_index(i, 3)] == stop_mark[3]))
        {
            if(*end_index != -1)
            {
                *end_index = get_minus_index(i, 1);
            }
        }
        
        i = get_next_index(i);
    }
//    debug_3(*start_index, *end_index, ((*start_index != 0xFF) && (*end_index != 0xFF)));
    if(((*start_index != 0xFF) && (*end_index != 0xFF)) == YES)
    {
        start_index_rcv = get_plus_index(*end_index, 5);
        return YES;
    }
    return NO;
}

#ifdef	__cplusplus
}
#endif

#endif	/* CIRCLE_BUFFER_H */

