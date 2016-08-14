#include <xc.h>
#include <pic16f1823.h>
#include "lcd_hd44780_pic16.h"
#include "usart_pic16.h"
#include "myutils.h"

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


#define LED_OUT_PORT      A
#define LED_OUT_POS       4
#define LED_OUT_PIN       PIN(LED_OUT_PORT, LED_OUT_POS)
#define LED_OUT           PORTBIT(LED_OUT_PIN)

#define TRIGGER_PORT      A
#define TRIGGER_POS       2
#define TRIGGER_PIN       PIN(TRIGGER_PORT, TRIGGER_POS)
#define TRIGGER           PORTBIT(TRIGGER_PIN)

char ssend[10] = "Send";
char srecv[10] = "Recv";

void TriggerOutInit()
{
    IO_OUTPUT(LED_OUT_PIN);
    ANSELBIT(LED_OUT_PIN) = 0;
    
    IO_INPUT(TRIGGER_PIN);
    ANSELBIT(TRIGGER_PIN) = 0;
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
    if(INTCONbits.INTF == 1)
    {
        LED_OUT = 1;
        INTCONbits.INTF = 0;
    } 
    if (RCIF == 1) 
    {
        USARTHandleRxInt();
        LED_OUT = 1;

        RCIF = 0;
    }    
}
void main (void)
{
    //Initialize the LCD module
    LCDInit(LS_NONE);

    //Initialize Trigger out
    TriggerOutInit();
    
    InitInputDataInt();
    
////////////////////////////
    //Initialize USART with baud rate 9600
    USARTInit(9600);

    //Write intro text
//    USARTWriteLine("***********************************************");
    USARTWriteString("ab");
//    USARTWriteLine("a");
//    USARTWriteLine("USART Test");
//    USARTWriteLine("----------");
//    USARTWriteLine("Type a character on keyboard");
//    USARTWriteLine("it will reach the PIC MCU via the serial line");
//    USARTWriteLine("PIC MCU will return the same character but ");
//    USARTWriteLine("enclosed in a <>");
//    USARTWriteLine("--");
//    USARTWriteLine("For example if you type 'a' you will see <a>");
//    USARTWriteLine("appear on serial terminal.");
//    USARTWriteLine(" ");
//    USARTWriteLine("This checks both way serial transfers.");
//    USARTWriteLine("");
//    USARTWriteLine("Copyright (C) 2008-2013");
//    USARTWriteLine("www.eXtremeElectronics.co.in");
//    USARTWriteLine("***********************************************");
//    USARTGotoNewLine();
//    USARTGotoNewLine();    
////////////////////////////
    //Clear the LCD
    LCDClear();

    LCDWriteStringXY(0, 0, ssend);
    LCDWriteStringXY(0, 1, srecv);
    LED_OUT = 0;
//    while(1)
//    {
//        __delay_ms(200);
//    }
    while(1)
    {
        //Get the amount of data waiting in USART queue
        uint8_t n= USARTDataAvailable();

        //If we have some data
        if(n!=0)
        {
            //Read it
            char data=USARTReadData();

            //And send back
            USARTWriteChar('<');
            USARTWriteChar(data);
            USARTWriteChar('>');
            LCDClear();
            LCDWriteIntXY(0, 0, data, 3);
            
        }

    }
}

