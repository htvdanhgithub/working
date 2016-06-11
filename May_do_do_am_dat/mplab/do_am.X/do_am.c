#include <xc.h>
#include <pic16f1823.h>
#include "lcd_hd44780_pic16.h"
#include "adc_pic16.h"
#include "lm35_pic16.h"

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#define IOC_ENABLE      INTCONbits.IOCIE
#define IOC_FLAG        INTCONbits.IOCIF
#define PER_INT_ENABLE  INTCONbits.PEIE
#define GLB_INT_ENABLE  INTCONbits.GIE

//LM35 is connected to Port A bit 2

#define TUNE_BUTTON_PORT      A
#define TUNE_BUTTON_POS       5
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


typedef struct {
        unsigned FOSC0                   :1;
        unsigned FOSC1                   :1;
        unsigned FOSC2                   :1;
        unsigned WDTE0                   :1;
        unsigned WDTE1                   :1;
        unsigned PWRTE                   :1;
        unsigned MCLRE                   :1;
        unsigned CP                      :1;
        unsigned CPD                     :1;
        unsigned BOREN0                  :1;
        unsigned BOREN1                  :1;
        unsigned CLKOUTEN                :1;
        unsigned IESO                    :1;
        unsigned FCMEN                   :1;
    } CONFIG1bits_t;
    
extern volatile CONFIG1bits_t CONFIG1bits @ 0x8007;


int tuneTemp = 0;
int curTemp = 0;
char tuneTempDir = 1;

void TriggerOutInit()
{
    // 1. Individual pin configuration
    IO_OUTPUT(TRIGGER_DOWN_OUT_PIN);
//    IO_OUTPUT(TRIGGER_UP_OUT_PIN);
    // 2. Digital I/O
    ANSELBIT(TRIGGER_DOWN_OUT_PIN) = 0;
//    ANSELBIT(TRIGGER_UP_OUT_PIN) = 0;
    
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

    // 3. Rising and falling edge detection
    TUNE_BUTTON_RAISING_EDGE = 1;
    // 4. Individual pin interrupt flags    
    IOC_FLAG = 0;
    TUNE_BUTTON_IOC_FLAG = 0;
    
    // 5 Peripheral interrupt
    PER_INT_ENABLE = 1;
    // 6. Global Interrupt Enable
    GLB_INT_ENABLE = 1;
}
void interrupt ISR()
{
    if(IOC_FLAG == 1)
    {
        if(TUNE_BUTTON_IOC_FLAG == 1)
        {
            //Clear the LCD
            LCDClear();

            LCDWriteStringXY(0, 0, "Thermometer set:");
            
            while(TUNE_BUTTON == 1)
            {
                tuneTemp++;
                if(tuneTemp > 150)
                {
                    tuneTemp = 0;
                }
                __delay_ms(50);
                
                //Print it on the LCD
                LCDWriteIntXY(0, 1, tuneTemp, 3);

                //Print the degree symbol and C
                LCDWriteString("%0C");
                
            }
            tuneTempDir = 1;
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
    
    //Clear the LCD
    LCDClear();

    while(1)
    {
//    TRIGGER_UP_OUT = 1;
        //Read the temperature using LM35
        curTemp = LM35ReadTemp();

        if(curTemp >= tuneTemp)
        {
            TRIGGER_DOWN_OUT = 1;
        }
        else
        {
            TRIGGER_DOWN_OUT = 0;
        }

        if(tuneTempDir == 1)
        {
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
}

