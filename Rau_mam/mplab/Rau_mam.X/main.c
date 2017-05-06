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

#define DELAY_40_SECS __delay_ms(50000)

#define DELAY_5_MINS \
{\
    DELAY_40_SECS;\
    DELAY_40_SECS;\
    DELAY_40_SECS;\
    DELAY_40_SECS;\
    DELAY_40_SECS;\
    DELAY_40_SECS;\
    DELAY_40_SECS;\
}


#define DELAY_1_HOUR \
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
}

void main(void) {
    TRISIObits.TRISIO4 = 0;
    GPIObits.GP4 = 1;
    while(1)
    {
        DELAY_5_MINS;
        GPIObits.GP4 = 0;
        DELAY_1_HOUR;
        GPIObits.GP4 = 1;
    }    
}
/*void main(void) {
    // Initial
    int count = 0;
    char mode = PUMPING; // 0: pumping, 1: waiting
    TRISIObits.TRISIO0 = 0;
    GPIObits.GP0 = 1;
    while(1)
    {
        count++;
        __delay_ms (1000);
        switch (mode)
        {
            case PUMPING:
                if (count == PUMP_5_MINS)
                {
                    count = 0;
                    mode = WAIT_1_HOUR;
                    GPIObits.GP0 = 0;
                }
                break;
            case WAITING:
                if (count == WAIT_1_HOUR)
                {
                    count = 0;
                    mode = PUMP_5_MINS;
                    GPIObits.GP0 = 0;
                }
                break;
        }
    }
}*/
