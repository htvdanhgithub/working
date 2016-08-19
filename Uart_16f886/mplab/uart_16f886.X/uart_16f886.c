#include <xc.h>
#include <pic16f886.h>
#include "lcd_hd44780_pic16.h"
#include "adc_pic16.h"
#include "lm35_pic16.h"
#include "usart_pic16.h"

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = ON        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = ON          // Code Protection bit (Program memory code protection is enabled)
#pragma config CPD = ON         // Data Code Protection bit (Data memory code protection is enabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = ON         // Low Voltage Programming Enable bit (RB3/PGM pin has PGM function, low voltage programming enabled)

// CONFIG2
#pragma config BOR4V = BOR21V   // Brown-out Reset Selection bit (Brown-out Reset set to 2.1V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)



#define IOCB_ENABLE      IOCBbits.IOCB4 = 1
#define IOCB_CLEAR       IOCBbits.IOCB4 = 0
#define INTB_ENABLE      INTCONbits.RBIE = 1
#define INTB_FLAG        INTCONbits.RBIF
#define INT_ENABLE       INTCONbits.INTE = 1
#define GLB_INT_ENABLE   INTCONbits.GIE

//LM35 is connected to Port A bit 2

#define TUNE_BUTTON_PORT      B
#define TUNE_BUTTON_POS       4
#define TUNE_BUTTON_PIN       PIN(TUNE_BUTTON_PORT, TUNE_BUTTON_POS)

#define TUNE_BUTTON                     PORTBIT(TUNE_BUTTON_PIN)
#define TUNE_BUTTON_TRIS                TRISBIT(TUNE_BUTTON_PIN)

#define TRIGGER_DOWN_OUT_PORT      A
#define TRIGGER_DOWN_OUT_POS       1
#define TRIGGER_DOWN_OUT_PIN       PIN(TRIGGER_DOWN_OUT_PORT, TRIGGER_DOWN_OUT_POS)
#define TRIGGER_DOWN_OUT           PORTBIT(TRIGGER_DOWN_OUT_PIN)

#define TRIGGER_UP_OUT_PORT      A
#define TRIGGER_UP_OUT_POS       0
#define TRIGGER_UP_OUT_PIN       PIN(TRIGGER_UP_OUT_PORT, TRIGGER_UP_OUT_POS)
#define TRIGGER_UP_OUT           PORTBIT(TRIGGER_UP_OUT_PIN)


#define TUNE_BUTTON_RAISING_EDGE        IOCPBIT(TUNE_BUTTON_PIN)
#define TUNE_BUTTON_IOC_FLAG            IOCFBIT(TUNE_BUTTON_PIN)


int tuneTemp = 0;
int curTemp = 0;
char tuneTempDir = 1;

//void TriggerOutInit()
//{
//    // 1. Individual pin configuration
//    IO_OUTPUT(TRIGGER_DOWN_OUT_PIN);
////    IO_OUTPUT(TRIGGER_UP_OUT_PIN);
//    // 2. Digital I/O
//    ANSELBIT(TRIGGER_DOWN_OUT_PIN) = 0;
////    ANSELBIT(TRIGGER_UP_OUT_PIN) = 0;
//    
////    APFCONbits.SDOSEL = 0;
////    APFCONbits.T1GSEL = 0;
////    APFCONbits.TXCKSEL = 0;
////    CONFIG1bits.MCLRE = 0;
////    APFCONbits.SSSEL = 0;
//}

void TuneButtonInit() {
    // 2. Individual pin configuration
    IO_INPUT(TUNE_BUTTON_PIN);
    ANSELHbits.ANS11 = 0;

    OPTION_REGbits.INTEDG = 1;
    INTCONbits.PEIE = 1;

    ANSELbits.ANS1 = 0;
    ANSELbits.ANS2 = 0;
    ANSELbits.ANS3 = 0;
    ANSELbits.ANS4 = 0;
    // 5 Peripheral interrupt

    // 1. Interrupt-on-Change enable (Master Switch)
    IOCB_ENABLE;
    INTB_ENABLE;
    INT_ENABLE;

    // 3. Rising and falling edge detection
    //    TUNE_BUTTON_RAISING_EDGE = 1;
    // 4. Individual pin interrupt flags    
    INTB_FLAG = 0;
    //    TUNE_BUTTON_IOC_FLAG = 0;

    // 6. Global Interrupt Enable
    GLB_INT_ENABLE = 1;
}

void interrupt ISR() {
    if (INTB_FLAG == 1) {
        //        if(TUNE_BUTTON == 1)
        {
            //Clear the LCD
            LCDClear();

            LCDWriteStringXY(0, 0, "Thermometer set:");

            tuneTemp++;
            if (tuneTemp > 150) {
                tuneTemp = 0;
            }

            //Print it on the LCD
            LCDWriteIntXY(0, 1, tuneTemp, 3);

            //Print the degree symbol and C
            LCDWriteString("%0C");

            __delay_ms(500);
            tuneTempDir = 1;

        }
        INTB_FLAG = 0;
    }
    IOCB_CLEAR;

    if (RCIE && RCIF) {
        USARTHandleRxInt();
        RCIF = 0;
    }
}

void main(void) {
    //Initialize the LCD module
    LCDInit(LS_NONE);

    //Initialize the ADC module
    ADCInit();

    //Initialize Tune button
    TuneButtonInit();
    //    
    //    //Initialize Trigger out
    //    TriggerOutInit();

    //Initialize USART with baud rate 9600
    USARTInit(9600);

    //Write intro text
    USARTWriteLine("***********************************************");
    USARTWriteLine("USART Test");
    USARTWriteLine("----------");
    USARTWriteLine("Type a character on keyboard");
    USARTWriteLine("it will reach the PIC MCU via the serial line");
    USARTWriteLine("PIC MCU will return the same character but ");
    USARTWriteLine("enclosed in a <>");
    USARTWriteLine("--");
    USARTWriteLine("For example if you type 'a' you will see <a>");
    USARTWriteLine("appear on serial terminal.");
    USARTWriteLine(" ");
    USARTWriteLine("This checks both way serial transfers.");
    USARTWriteLine("");
    USARTWriteLine("Copyright (C) 2008-2013");
    USARTWriteLine("www.eXtremeElectronics.co.in");
    USARTWriteLine("***********************************************");
    USARTGotoNewLine();
    USARTGotoNewLine();

    //Clear the LCD
    LCDClear();

    while (1) {
        //    TRIGGER_UP_OUT = 1;
        if (TUNE_BUTTON == 1) {
            //Clear the LCD
            LCDClear();

            LCDWriteStringXY(0, 0, "Thermometer set:");

            tuneTemp++;
            if (tuneTemp > 150) {
                tuneTemp = 0;
            }

            //Print it on the LCD
            LCDWriteIntXY(0, 1, tuneTemp, 3);

            //Print the degree symbol and C
            LCDWriteString("%0C");

            __delay_ms(500);
            tuneTempDir = 1;

        } else {
            //Read the temperature using LM35
            curTemp = LM35ReadTemp();

            if (curTemp >= tuneTemp) {
                TRIGGER_DOWN_OUT = 1;
            } else {
                TRIGGER_DOWN_OUT = 0;
            }

            if (tuneTempDir == 1) {
                //Clear the LCD
                LCDClear();

                LCDWriteStringXY(0, 0, "Thermometer:");
                tuneTempDir = 0;
            }

            //Print it on the LCD
            LCDWriteIntXY(0, 1, curTemp, 3);

            //Print the degree symbol and C
            LCDWriteString("%0C");

            //Wait 200ms before taking next reading
            __delay_ms(200);

        }

        //Get the amount of data waiting in USART queue
        uint8_t n = USARTDataAvailable();

        //If we have some data
        if (n != 0) {
            //Read it
            char data = USARTReadData();

            //And send back
            USARTWriteChar('<');
            USARTWriteChar(data);
            USARTWriteChar('>');
        }

    }
}

//void main()
//{
//  //Initialize USART with baud rate 9600
//  USARTInit(9600);
//
//  //Write intro text
//  USARTWriteLine("***********************************************");
//  USARTWriteLine("USART Test");
//  USARTWriteLine("----------");
//  USARTWriteLine("Type a character on keyboard");
//  USARTWriteLine("it will reach the PIC MCU via the serial line");
//  USARTWriteLine("PIC MCU will return the same character but ");
//  USARTWriteLine("enclosed in a <>");
//  USARTWriteLine("--");
//  USARTWriteLine("For example if you type 'a' you will see <a>");
//  USARTWriteLine("appear on serial terminal.");
//  USARTWriteLine(" ");
//  USARTWriteLine("This checks both way serial transfers.");
//  USARTWriteLine("");
//  USARTWriteLine("Copyright (C) 2008-2013");
//  USARTWriteLine("www.eXtremeElectronics.co.in");
//  USARTWriteLine("***********************************************");
//  USARTGotoNewLine();
//  USARTGotoNewLine();
//
//  while(1)
//  {
//      //Get the amount of data waiting in USART queue
//      uint8_t n= USARTDataAvailable();
//
//      //If we have some data
//      if(n!=0)
//      {
//          //Read it
//          char data=USARTReadData();
//
//          //And send back
//          USARTWriteChar('<');
//          USARTWriteChar(data);
//          USARTWriteChar('>');
//      }
//
//  }
//}