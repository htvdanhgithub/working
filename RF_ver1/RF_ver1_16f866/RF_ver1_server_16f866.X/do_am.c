#include <xc.h>
#include <pic16f886.h>
#include "lcd_hd44780_pic16.h"
#include "adc_pic16.h"
#include "lm35_pic16.h"
#include "menu.h"
#include "packet.h"
#include "msg.h"

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

#define DATA_IN0_PORT      A
#define DATA_IN0_POS       0
#define DATA_IN0_PIN       PIN(DATA_IN0_PORT, DATA_IN0_POS)
#define DATA_IN0           PORTBIT(DATA_IN0_PIN)

#define DATA_IN1_PORT      A
#define DATA_IN1_POS       1
#define DATA_IN1_PIN       PIN(DATA_IN1_PORT, DATA_IN1_POS)
#define DATA_IN1           PORTBIT(DATA_IN1_PIN)

#define DATA_IN2_PORT      A
#define DATA_IN2_POS       2
#define DATA_IN2_PIN       PIN(DATA_IN2_PORT, DATA_IN2_POS)
#define DATA_IN2           PORTBIT(DATA_IN2_PIN)

#define DATA_IN3_PORT      A
#define DATA_IN3_POS       3
#define DATA_IN3_PIN       PIN(DATA_IN3_PORT, DATA_IN3_POS)
#define DATA_IN3           PORTBIT(DATA_IN3_PIN)

#define DATA_OUT_TRIGGER_PORT      A
#define DATA_OUT_TRIGGER_POS       7
#define DATA_OUT_TRIGGER_PIN       PIN(DATA_OUT_TRIGGER_PORT, DATA_OUT_TRIGGER_POS)
#define DATA_OUT_TRIGGER           PORTBIT(DATA_OUT_TRIGGER_PIN)

#define DATA_OUT0_PORT      B
#define DATA_OUT0_POS       0
#define DATA_OUT0_PIN       PIN(DATA_OUT0_PORT, DATA_OUT0_POS)
#define DATA_OUT0           PORTBIT(DATA_OUT0_PIN)

#define DATA_OUT1_PORT      B
#define DATA_OUT1_POS       1
#define DATA_OUT1_PIN       PIN(DATA_OUT1_PORT, DATA_OUT1_POS)
#define DATA_OUT1           PORTBIT(DATA_OUT1_PIN)

#define DATA_OUT2_PORT      B
#define DATA_OUT2_POS       2
#define DATA_OUT2_PIN       PIN(DATA_OUT2_PORT, DATA_OUT2_POS)
#define DATA_OUT2           PORTBIT(DATA_OUT2_PIN)

#define DATA_OUT3_PORT      B
#define DATA_OUT3_POS       3
#define DATA_OUT3_PIN       PIN(DATA_OUT3_PORT, DATA_OUT3_POS)
#define DATA_OUT3           PORTBIT(DATA_OUT3_PIN)

#define DATA_IN_TRIGGER_PORT      A
#define DATA_IN_TRIGGER_POS       6
#define DATA_IN_TRIGGER_PIN       PIN(DATA_IN_TRIGGER_PORT, DATA_IN_TRIGGER_POS)
#define DATA_IN_TRIGGER           PORTBIT(DATA_IN_TRIGGER_PIN)

#define MENU_IN_PORT      B
#define MENU_IN_POS       4
#define MENU_IN_PIN       PIN(MENU_IN_PORT, MENU_IN_POS)
#define MENU_IN           PORTBIT(MENU_IN_PIN)

#define MENU_OUT_PORT      B
#define MENU_OUT_POS       6
#define MENU_OUT_PIN       PIN(MENU_OUT_PORT, MENU_OUT_POS)
#define MENU_OUT           PORTBIT(MENU_OUT_PIN)

#define UP_PORT      B
#define UP_POS       5
#define UP_PIN       PIN(UP_PORT, UP_POS)
#define UP           PORTBIT(UP_PIN)

#define DOWN_PORT      B
#define DOWN_POS       7
#define DOWN_PIN       PIN(DOWN_PORT, DOWN_POS)
#define DOWN           PORTBIT(DOWN_PIN)

E_operation_mode mode = NORMAL;
E_operation_submode submode = NOTEDIT;

Msg_t msg;

void IOInit()
{
    // 2. Individual pin configuration
    IO_INPUT(DATA_IN_TRIGGER_PIN);
//    ANSELHbits.ANS11 = 0;
    
    IO_INPUT(DATA_IN0_PIN);
    ANSELbits.ANS0 = 0;

    IO_INPUT(DATA_IN1_PIN);
    ANSELbits.ANS1 = 0;
    IO_INPUT(DATA_IN2_PIN);
    ANSELbits.ANS2 = 0;
    IO_INPUT(DATA_IN3_PIN);
    ANSELbits.ANS3 = 0;
    
    IO_OUTPUT(DATA_OUT_TRIGGER_PIN);

    IO_OUTPUT(DATA_OUT0_PIN);
    ANSELHbits.ANS12 = 0;
	
    IO_OUTPUT(DATA_OUT1_PIN);
    ANSELHbits.ANS10 = 0;

    IO_OUTPUT(DATA_OUT2_PIN);
    ANSELHbits.ANS8 = 0;

    IO_OUTPUT(DATA_OUT3_PIN);
    ANSELHbits.ANS9 = 0;
    
    DATA_OUT_TRIGGER = 1;
    
    
    IO_INPUT(MENU_IN_PIN);
    ANSELHbits.ANS11 = 0;
    
    IO_INPUT(MENU_OUT_PIN);
    
    IO_INPUT(UP_PIN);
    ANSELHbits.ANS13 = 0;
    
    IO_INPUT(DOWN_PIN);

    //    ANSELHbits.ANS11 = 0;

//    OPTION_REGbits.INTEDG = 1;
//    INTCONbits.PEIE = 1;
    // 5 Peripheral interrupt

    // 1. Interrupt-on-Change enable (Master Switch)
//    IOCB_ENABLE;
//    INTB_ENABLE;
//    INT_ENABLE;
    
    // 3. Rising and falling edge detection
//    DATA_IN_TRIGGER_RAISING_EDGE = 1;
    // 4. Individual pin interrupt flags    
//    INTB_FLAG = 0;
//    DATA_IN_TRIGGER_IOC_FLAG = 0;
    
    // 6. Global Interrupt Enable
//    GLB_INT_ENABLE = 1;
}
void interrupt ISR()
{
}
void main (void)
{
    //Initialize the LCD module
    LCDInit(LS_NONE);

    //Initialize the ADC module
    ADCInit();

    //Initialize Tune button
    IOInit();
    
    MenuInit();
//    
//    //Initialize Trigger out
//    TriggerOutInit();
    
    //Clear the LCD
    LCDClear();

    while(1)
    {
        if(DATA_IN_TRIGGER == 0)
        {
            SEND_MSG(&msg, DATA_OUT3, DATA_OUT2, DATA_OUT1, DATA_OUT0, DATA_OUT_TRIGGER);
            __delay_ms(200);
        }
        else
        if(MENU_IN == 0)
        {
            if(mode == NORMAL)
            {
                DEBUG("MENU MODE");
                mode = MENU;
                ShowMenu();
            }
            else
            {
                DEBUG("EDIT MODE");
                submode = EDIT;
                ShowMenu();
                LCDSetStyle(LS_BLINK);
            }

            __delay_ms(200);
        }
        else
        if(MENU_OUT == 0)
        {
            if(mode == MENU)
            {
                if(submode == EDIT)
                {
                    DEBUG("NOTEDIT MODE");
                    submode = NOTEDIT;
                    LCDSetStyle(LS_NONE);
                }
                else
                {
                    DEBUG("NORMAL MODE");
                    mode = NORMAL;
                    ClearMenu();
                }
            }

            __delay_ms(200);
        }
        else
        if(UP == 0)
        {
            DEBUG("UP");
            if(mode == MENU)
            {
                if(submode == EDIT)
                {
                    ValueInc();
                }            
                else
                {
                    MenuUp();
                }
                ShowMenu();                
            }
            __delay_ms(200);
        }
        else
        if(DOWN == 0)
        {
            DEBUG("DOWN");
            if(mode == MENU)
            {
                if(submode == EDIT)
                {
                    ValueDec();
                }            
                else
                {
                    MenuDown();
                }
                ShowMenu();
            }
            __delay_ms(200);
        }
            
    }
}

