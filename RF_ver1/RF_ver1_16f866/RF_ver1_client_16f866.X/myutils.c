#include <xc.h>
#include "myutils.h"


int8_t compare_4_bits(uint8_t byte1, uint8_t byte2, uint8_t low)
{
    if(low == 1)
    {
        byte1 &= 0b00001111;
        byte2 &= 0b00001111;
    }
    else
    {
        byte1 &= 0b11110000;
        byte2 &= 0b11110000;
    }
    if(byte1 < byte2)
    {
        return -1;
    }
        
    if(byte1 > byte2)
    {
        return 1;
    }
        
    return 0;
}