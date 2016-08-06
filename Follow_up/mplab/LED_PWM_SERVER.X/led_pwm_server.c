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

    IO_OUTPUT(DATA_OUT_TRIGGER_PIN);
    ANSELBIT(DATA_OUT_TRIGGER_AN_PIN) = 0;
            
    IO_OUTPUT(DATA_OUT0_PIN);
    ANSELBIT(DATA_OUT0_AN_PIN) = 0;

    IO_OUTPUT(DATA_OUT1_PIN);
    ANSELBIT(DATA_OUT1_AN_PIN) = 0;

    IO_OUTPUT(DATA_OUT2_PIN);
//    ANSELBIT(DATA_OUT2_AN_PIN) = 0;

    IO_OUTPUT(DATA_OUT3_PIN);
//    ANSELBIT(DATA_OUT3_AN_PIN) = 0;
}
//void InitTimerInt()
//{
//    OPTION_REGbits.INTEDG = 0; // on falling edge
//    OPTION_REGbits.T0CS = 0;   // Internal instruction cycle clock (FOSC/4)
//    OPTION_REGbits.PSA = 1;    // No scale
//
//    CPSCON0bits.T0XCS = 1;     
//    
//    INTCONbits.GIE = 1;
//    INTCONbits.PEIE = 1;
//    INTCONbits.T0IE = 1;
//    INTCONbits.T0IF = 0;
//    
//    
//}
void InitInputDataInt()
{
    INTCONbits.GIE = 1;
    INTCONbits.INTE = 1;
    INTCONbits.INTF = 0;
    OPTION_REGbits.INTEDG = 0;
}
void interrupt ISR()
{
    if(INTCONbits.INTF == 1)
    {
        Connection_t conn;
        RGB_DATA_RQT_CMD_t rqt;
        rqt.r = 255;
        rqt.g = 0;
        rqt.b = 255;
        send_RGB_DATA_RQT_CMD(&conn, &rqt);        
        INTCONbits.INTF = 0;
    }    
}
void main (void)
{
    InitIO();
//    InitTimerInt();
    InitInputDataInt();
    
    DATA_OUT_TRIGGER = 0;
   
    while(1)
    {
    }
}

