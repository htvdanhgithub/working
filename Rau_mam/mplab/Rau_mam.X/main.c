/*
 * File:   main.c
 * Author: Admin
 *
 * Created on April 27, 2017, 8:47 PM
 */
// PIC12F629 Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSC oscillator: I/O function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-Up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // GP3/MCLR pin function select (GP3/MCLR pin function is digital I/O, MCLR internally tied to VDD)
#pragma config BOREN = OFF      // Brown-out Detect Enable bit (BOD disabled)
#pragma config CP = ON          // Code Protection bit (Program Memory code protection is enabled)
#pragma config CPD = ON         // Data Code Protection bit (Data memory code protection is enabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#define _XTAL_FREQ 4000000

#include <xc.h>
#include <pic12f629.h>


#define PUMPING   0  // Pumping
#define WAITING   1  // Waiting

#define PUMP_5_MINS   10  // 300 seconds
#define WAIT_1_HOUR   60 // 3600 seconds

#define DELAY_50_SECS __delay_ms(50000)

#define DELAY_5_MINS \
{\
    DELAY_50_SECS;\
    DELAY_50_SECS;\
    DELAY_50_SECS;\
    DELAY_50_SECS;\
    DELAY_50_SECS;\
    DELAY_50_SECS;\
}


#define DELAY_50_MINS \
{\
    DELAY_5_MINS;\
    DELAY_5_MINS;\
    DELAY_5_MINS;\
    DELAY_5_MINS;\
    DELAY_5_MINS;\
    DELAY_5_MINS;\
    DELAY_5_MINS;\
    DELAY_5_MINS;\
    DELAY_5_MINS;\
    DELAY_5_MINS;\
}


void main(void) {
    TRISIObits.TRISIO1 = 0;
    GPIObits.GP1 = 1;
    while(1)
    {
        OSCCALbits.CAL = 0b000000;
#ifdef TEST
        DELAY_50_SECS;
#else
        DELAY_5_MINS;
#endif        
        GPIObits.GP1 = 0;
        for(int i = 0; i < 3; i++)
        {
#ifdef TEST
            DELAY_50_SECS;
#else
            DELAY_50_MINS;
#endif        
        }
        GPIObits.GP1 = 1;
    }    
}
