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
#pragma config WDTE = ON        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = ON       // Power-Up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = OFF      // GP3/MCLR pin function select (GP3/MCLR pin function is digital I/O, MCLR internally tied to VDD)
#pragma config BOREN = OFF      // Brown-out Detect Enable bit (BOD disabled)
#pragma config CP = ON          // Code Protection bit (Program Memory code protection is enabled)
#pragma config CPD = ON         // Data Code Protection bit (Data memory code protection is enabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#define _XTAL_FREQ 4000000

#include <xc.h>
#include <pic12f629.h>

#define DELAY_5_MINS   300  // 300 seconds
#define DELAY_1_HOURS  3600 // 3600 seconds

void delay_n_secs(int second)
{
    for (int i = 0; i < second; i++)
    {
        __delay_ms(1000);
    }
}

void main(void) {
    // Initial
    TRISIObits.TRISIO4 = 0;
    GPIObits.GP4 = 1;
    delay_n_secs(DELAY_5_MINS);
    GPIObits.GP4 = 0;
    while(1)
    {
        delay_n_secs(DELAY_1_HOURS);
        GPIObits.GP4 = 1;
        delay_n_secs(DELAY_5_MINS);
        GPIObits.GP4 = 0;
    }
}
