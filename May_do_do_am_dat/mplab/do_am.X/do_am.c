#include <xc.h>
#include <pic16f1823.h>
#include "lcd_hd44780_pic16.h"
#include "adc_pic16.h"
#include "lm35_pic16.h"

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


#define IOC_ENABLE      INTCONbits.IOCIE
#define IOC_FLAG        INTCONbits.IOCIF
#define PER_INT_ENABLE  INTCONbits.PEIE
#define GLB_INT_ENABLE  INTCONbits.GIE

//LM35 is connected to Port A bit 2

#define TUNE_BUTTON_PORT      A
#define TUNE_BUTTON_POS       1
#define TUNE_BUTTON_PIN       PIN(TUNE_BUTTON_PORT, TUNE_BUTTON_POS)

#define TUNE_BUTTON                     PORTBIT(TUNE_BUTTON_PIN)
#define TUNE_BUTTON_TRIS                TRISBIT(TUNE_BUTTON_PIN)

#define TRIGGER_OPEN_OUT_PORT      A
#define TRIGGER_OPEN_OUT_POS       4
#define TRIGGER_OPEN_OUT_PIN       PIN(TRIGGER_OPEN_OUT_PORT, TRIGGER_OPEN_OUT_POS)
#define TRIGGER_OPEN_OUT           PORTBIT(TRIGGER_OPEN_OUT_PIN)

#define TRIGGER_CLOSE_OUT_PORT      A
#define TRIGGER_CLOSE_OUT_POS       5
#define TRIGGER_CLOSE_OUT_PIN       PIN(TRIGGER_CLOSE_OUT_PORT, TRIGGER_CLOSE_OUT_POS)
#define TRIGGER_CLOSE_OUT           PORTBIT(TRIGGER_CLOSE_OUT_PIN)


#define TUNE_BUTTON_RAISING_EDGE        IOCPBIT(TUNE_BUTTON_PIN)
#define TUNE_BUTTON_IOC_FLAG            IOCFBIT(TUNE_BUTTON_PIN)


int tuneUpTemp = 0;
int curTemp = 0;
char tuneUpTempDir = 1;

void TriggerOutInit()
{
    // 1. Individual pin configuration
    IO_OUTPUT(TRIGGER_OPEN_OUT_PIN);
    IO_OUTPUT(TRIGGER_CLOSE_OUT_PIN);
    // 2. Digital I/O
    ANSELBIT(TRIGGER_OPEN_OUT_PIN) = 0;
//    ANSELBIT(TRIGGER_CLOSE_OUT_PIN) = 0;
    
//    APFCONbits.SDOSEL = 0;
//    APFCONbits.T1GSEL = 0;
//    APFCONbits.TXCKSEL = 0;
//    CONFIG1bits.MCLRE = 0;
//    APFCONbits.SSSEL = 0;
}
void TuneButtonInit()
{
    // 1. Interrupt-on-Change enable (Master Switch)
    IOC_ENABLE = 1;
    // 2. Individual pin configuration
    IO_INPUT(TUNE_BUTTON_PIN);
    ANSELBIT(TUNE_BUTTON_PIN) = 0;

    // 3. Rising and falling edge detection
//    TUNE_BUTTON_RAISING_EDGE = 1;
    // 4. Individual pin interrupt flags    
//    IOC_FLAG = 0;
//    TUNE_BUTTON_IOC_FLAG = 0;
    
    // 5 Peripheral interrupt
//    PER_INT_ENABLE = 1;
    // 6. Global Interrupt Enable
//    GLB_INT_ENABLE = 1;
}
void interrupt ISR()
{
    if(IOC_FLAG == 1)
    {
        if(TUNE_BUTTON_IOC_FLAG == 1)
        {
//            //Clear the LCD
//            LCDClear();
//
//            LCDWriteStringXY(0, 0, "Thermometer set:");
            
            while(TUNE_BUTTON == 1)
            {
                tuneUpTemp++;
                if(tuneUpTemp > 150)
                {
                    tuneUpTemp = 0;
                }
                //Print it on the LCD
                LCDWriteIntXY(4, 1, tuneUpTemp, 3);
                
                __delay_ms(10);
                
//                //Print it on the LCD
//                LCDWriteIntXY(0, 1, tuneUpTemp, 3);
//
//                //Print the degree symbol and C
//                LCDWriteString("%0C");
                
            }
            tuneUpTempDir = 1;
            TUNE_BUTTON_IOC_FLAG = 0;
        }
        IOC_FLAG = 0;
    }
}
void main (void)
{
    //Initialize the LCD module
    LCDInit(LS_NONE);

    //Initialize the ADC module
    ADCInit();

    //Initialize Tune button
    TuneButtonInit();
    
    //Initialize Trigger out
    TriggerOutInit();
    
//    //Clear the LCD
//    LCDClear();

    TRIGGER_OPEN_OUT = 0;
    TRIGGER_CLOSE_OUT = 1;
    
    //Clear the LCD
    LCDClear();

    LCDWriteStringXY(0, 0, "Cur:");
    //Print the degree symbol and C
    LCDWriteStringXY(7, 0, "%0C"); 

    LCDWriteStringXY(10, 0, "Wa:");

    LCDWriteStringXY(0, 1, "Max:");
    //Print the degree symbol and C
    LCDWriteStringXY(7, 1, "%0C"); 

    LCDWriteStringXY(13, 0, "OFF");

    LCDWriteIntXY(4, 1, tuneUpTemp, 3);
    LCDWriteIntXY(4, 0, curTemp, 3);    
    while(1)
    {
        //Read the temperature using LM35
        curTemp = LM35ReadTemp();

        if((tuneUpTemp >= 5) && (curTemp >= tuneUpTemp))
        {
            LCDWriteStringXY(13, 0, "ON ");
            TRIGGER_OPEN_OUT = 1;
            TRIGGER_CLOSE_OUT = 0;
        }
        else
        {
            if(curTemp <= tuneUpTemp - 5)
            {
                LCDWriteStringXY(13, 0, "OFF");
                TRIGGER_OPEN_OUT = 0;
                TRIGGER_CLOSE_OUT = 1;
            }
        }
        while(TUNE_BUTTON == 1)
        {
            tuneUpTemp++;
            if(tuneUpTemp > 150)
            {
                tuneUpTemp = 0;
            }
            //Print it on the LCD
            LCDWriteIntXY(4, 1, tuneUpTemp, 3);

            __delay_ms(5);

//                //Print it on the LCD
//                LCDWriteIntXY(0, 1, tuneUpTemp, 3);
//
//                //Print the degree symbol and C
//                LCDWriteString("%0C");

        }

//        if(tuneUpTempDir == 1)
//        {
//            tuneUpTempDir = 0;
//        }
        
        //Print it on the LCD
        LCDWriteIntXY(4, 0, curTemp, 3);

      
//        //Wait 200ms before taking next reading
//        __delay_ms(20);
    }
}

