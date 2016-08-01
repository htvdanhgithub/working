#include <xc.h>
#include <pic16f1823.h>
#include <stdint.h>
#include "io_define.h"
#include "common.h"
#include "circle_buffer.h"
#include "msg.h"
#include "rgb_data.h"

// CONFIG
// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select (MCLR/VPP pin function is digital input)
#pragma config CP = ON          // Flash Program Memory Code Protection (Program memory code protection is enabled)
#pragma config CPD = ON         // Data Memory Code Protection (Data memory code protection is enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = ON        // Internal/External Switchover (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN = ON       // PLL Enable (4x PLL enabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)


#define RED   0
#define GREEN 1
#define BLUE  2

uint8_t duty[3] = {50, 125, 200};
uint8_t time = 0;
Msg_t msg;
Msg_t *pmsg = &msg;
void InitIO()
{
    IO_INPUT(KICK_OFF_TRIGGER_PIN);
    ANSELBIT(KICK_OFF_TRIGGER_AN_PIN) = 0;

    IO_OUTPUT(LED_A_OUT_PIN);
    ANSELBIT(LED_A_AN_PIN) = 0;

    IO_OUTPUT(LED_B_OUT_PIN);
    ANSELBIT(LED_B_AN_PIN) = 0;

    IO_OUTPUT(LED_C_OUT_PIN);
    ANSELBIT(LED_C_AN_PIN) = 0;

    IO_INPUT(DATA_IN0_PIN);
    ANSELBIT(DATA_IN0_AN_PIN) = 0;

    IO_INPUT(DATA_IN1_PIN);
    ANSELBIT(DATA_IN1_AN_PIN) = 0;

    IO_INPUT(DATA_IN2_PIN);
//    ANSELBIT(DATA_IN2_AN_PIN) = 0;

    IO_INPUT(DATA_IN3_PIN);
//    ANSELBIT(DATA_IN3_AN_PIN) = 0;
}
void InitTimerInt()
{
    OPTION_REGbits.INTEDG = 0; // on falling edge
    OPTION_REGbits.T0CS = 0;   // Internal instruction cycle clock (FOSC/4)
    OPTION_REGbits.PSA = 1;    // No scale

    CPSCON0bits.T0XCS = 1;     
    
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.T0IE = 1;
    INTCONbits.T0IF = 0;
    
    
}
void InitInputDataInt()
{
    INTCONbits.GIE = 1;
    INTCONbits.INTE = 1;
    INTCONbits.INTF = 0;
    OPTION_REGbits.INTEDG = 0;
}
void interrupt ISR()
{
//    if(T0IF == 1) // T0 overflowed ?
//    {
//        T0IF = 0;
//        
//        // Fosc/4 x (Prescale) x (count to overflow) = repeat rate.
//        // 1us    x 1        x 100                 = 100us*256 = 25600us = 25ms repeat rate.
//        TMR0 = 159; // 256-(100 - 3);  // need 141 but looses TMR0 looses 2 so use 142
//
//        if (time == 0) 
//        {
//            time = 0;
//            LED_A_OUT = 1;
//            LED_B_OUT = 1;
//            LED_C_OUT = 1;
//        }
//        if(time == duty[RED])
//        {
//            LED_A_OUT = 0;
//        }
//        if(time == duty[GREEN])
//        {
//            LED_B_OUT = 0;
//        }
//        if(time == duty[BLUE])
//        {
//            LED_C_OUT = 0;
//        }
//        time++;
//        
//    }
    if(INTCONbits.INTF == 1)
    {
        LED_A_OUT = 1;
        LED_B_OUT = 0;
        LED_C_OUT = 1;
        RECEIVE_INPUT(DATA_IN3, DATA_IN2, DATA_IN1, DATA_IN0);
        INTCONbits.INTF = 0;
    }    
}
void main (void)
{
    InitIO();
    InitTimerInt();
    InitInputDataInt();
    
    LED_A_OUT = 0;
    LED_B_OUT = 0;
    LED_C_OUT = 0;
   
    while(1)
    {
        if(get_msg(pmsg) == YES)
        {
            extract_RGB_DATA_RQT_CMD(pmsg, duty);
        }        
    }
}

