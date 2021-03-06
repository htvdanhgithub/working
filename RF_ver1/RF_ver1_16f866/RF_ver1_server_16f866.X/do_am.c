#include <xc.h>
#include <pic16f886.h>
#include "adc_pic16.h"
#include "lm35_pic16.h"
#include "menu.h"
#include "packet.h"
#include "msg.h"
#include "debug.h"
#include "connection.h"
#include "reg_id.h"
#include "heart_beat.h"
#include "io_define.h"
#include "common.h"

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



//LM35 is connected to Port A bit 2

E_operation_mode mode = NORMAL;
E_operation_submode submode = NOTEDIT;

Msg_t msg;
Msg_t *pmsg = &msg;

void ConnInit()
{
    for(uint8_t i = 0; i < MAX_CLIENT_CONNECTION; i++)
    {
        client_conn[i].from         = SERVER_ID;
        client_conn[i].to           = 255;
        client_conn[i].msgid        = 0;
        client_conn[i].available    = NO;
    }
}

void IOInit()
{
    // 2. Individual pin configuration
    IO_INPUT(KICK_OFF_TRIGGER_PIN);
    ANSELHbits.ANS8 = 0;

    IO_INPUT(DATA_IN_TRIGGER_PIN);
    ANSELHbits.ANS12 = 0;
    
    INTCONbits.GIE = 1;
    INTCONbits.INTE = 1;
    INTCONbits.INTF = 0;
    OPTION_REGbits.INTEDG = 0;
    
    IO_INPUT(DATA_IN0_PIN);
    ANSELbits.ANS0 = 0;

    IO_INPUT(DATA_IN1_PIN);
    ANSELbits.ANS1 = 0;
    IO_INPUT(DATA_IN2_PIN);
    ANSELbits.ANS2 = 0;
    IO_INPUT(DATA_IN3_PIN);
    ANSELbits.ANS3 = 0;
    
    IO_OUTPUT(DATA_OUT_TRIGGER_PIN);
    ANSELHbits.ANS10 = 0;

    IO_OUTPUT(DATA_OUT0_PIN);
	
    IO_OUTPUT(DATA_OUT1_PIN);
    ANSELbits.ANS4 = 0;

    IO_OUTPUT(DATA_OUT2_PIN);

    IO_OUTPUT(DATA_OUT3_PIN);
    
    DATA_OUT_TRIGGER = 1;
    
    
    IO_INPUT(MENU_IN_PIN);
    ANSELHbits.ANS11 = 0;
    
    IO_INPUT(MENU_OUT_PIN);
    
    IO_INPUT(UP_PIN);
    ANSELHbits.ANS13 = 0;
    
    IO_INPUT(DOWN_PIN);

}
int count = 0;
void interrupt ISR()
{
    if(INTCONbits.INTF == 1)
    {
        RECEIVE_INPUT(DATA_IN3, DATA_IN2, DATA_IN1, DATA_IN0);
        INTCONbits.INTF = 0;
    }
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
    
    ConnInit();
    
    //Clear the LCD
    LCDClear();
    
    uint8_t ret = NO;
    uint8_t value = 0x99;
    uint8_t sendc = 0x78;
    uint8_t revc = 0;
    REG_ID_RQT_CMD_t rqt;
    REG_ID_RQT_CMD_t *prqt = &rqt;
    REG_ID_RSP_CMD_t rsp;
    REG_ID_RSP_CMD_t *prsp = &rsp;
    Connection_t *pconn = NULL;

    uint8_t start_index, end_index;
    while(1)
    {
   //     handle_received_cmds();
        if(KICK_OFF_TRIGGER == 0)
        {
            HEART_BEAT_RQT_CMD_t rqt;
            send_HEART_BEAT_RQT_CMD_and_wait(&client_conn[0], &rqt);
            
            if(get_msg(pmsg) == YES)
            {
                dump_msg(pmsg);
            }
//            debug_1(get_distance(9, 1));
//              get_msg_index(&start_index, &end_index);
//            RECEIVE_INPUT(DATA_IN3, DATA_IN2, DATA_IN1, DATA_IN0);
//            SEND_MSG_ACK(ret, pmsg, DATA_IN3, DATA_IN2, DATA_IN1, DATA_IN0, DATA_IN_TRIGGER,
//                                DATA_OUT3, DATA_OUT2, DATA_OUT1, DATA_OUT0, DATA_OUT_TRIGGER);
//            count++;
//            compose(pmsg, 11 + count, 22 + count, 33 + count, 44 + count, "abc", 3);
//            send_msg(pmsg);
//            dump_msg(pmsg);
////            while(ret == NO)
//            {
//                SEND_HALF_BYTE_ACK(ret, value, 1, DATA_IN3, DATA_IN2, DATA_IN1, DATA_IN0, DATA_IN_TRIGGER, 
//                                                   DATA_OUT3, DATA_OUT2, DATA_OUT1, DATA_OUT0, DATA_OUT_TRIGGER, SEND_HALF_BYTE_TIMEOUT);
//                __delay_ms(1);
//            }
//            DEBUG_LINE_CLEAR; DEBUG_STRING_X(0, "ret:"); DEBUG_INT(ret, 3);
//            for(uint8_t i = 1; i < 2; i++)
//            {
//                rqt.id = i;
//                pconn = (Connection_t *)&client_conn[i];
//                SERVER_REG_ID(pmsg, pconn, prqt, prsp, 
//                              DATA_IN3, DATA_IN2, DATA_IN1, DATA_IN0, DATA_IN_TRIGGER, 
//                              pmsg, DATA_OUT3, DATA_OUT2, DATA_OUT1, DATA_OUT0, DATA_OUT_TRIGGER);
//                
//            }
//            SEND_HALF_BYTE(sendc, 1, DATA_OUT3, DATA_OUT2, DATA_OUT1, DATA_OUT0, DATA_OUT_TRIGGER);
//            RECEIVE_HALF_BYTE(revc, 1, DATA_IN3, DATA_IN2, DATA_IN1, DATA_IN0, DATA_IN_TRIGGER);
//            SEND_MSG_ACK(ret, pmsg, DATA_IN3, DATA_IN2, DATA_IN1, DATA_IN0, DATA_IN_TRIGGER,
//                                DATA_OUT3, DATA_OUT2, DATA_OUT1, DATA_OUT0, DATA_OUT_TRIGGER);
////            DEBUG_LINE_CLEAR; DEBUG_STRING_X(0, "SND:"); DEBUG_INT(pmsg->crc, 3);
//            DEBUG_LINE_CLEAR; DEBUG_INT_X(0, count++, 3);
//            FLASH_DOWN(DATA_OUT_TRIGGER);
//              DEBUG_LINE_CLEAR; DEBUG_STRING_X(0, "Kick off:"); DEBUG_INT(DATA_OUT_TRIGGER, 3);
            __delay_ms(200);
        }
        else
        if(MENU_IN == 0)
        {
            if(mode == NORMAL)
            {
                DEBUG_STRING_CLEAR("MENU MODE");
                mode = MENU;
                ShowMenu();
            }
            else
            {
                DEBUG_STRING_CLEAR("EDIT MODE");
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
                    DEBUG_STRING_CLEAR("NOTEDIT MODE");
                    submode = NOTEDIT;
                    LCDSetStyle(LS_NONE);
                }
                else
                {
                    DEBUG_STRING_CLEAR("NORMAL MODE");
                    mode = NORMAL;
                    ClearMenu();
                }
            }

            __delay_ms(200);
        }
        else
        if(UP == 0)
        {
            DEBUG_STRING_CLEAR("UP");
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
            DEBUG_STRING_CLEAR("DOWN");
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

