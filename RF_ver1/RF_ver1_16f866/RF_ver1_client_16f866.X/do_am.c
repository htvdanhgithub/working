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

void ConnInit()
{
    server_conn.from         = LoadMenuItem(0);
    server_conn.to           = SERVER_ID;
    server_conn.msgid        = 0;
    server_conn.available    = NO;
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
    
    uint8_t count = 0;
    uint8_t ret;
    uint8_t value;
    
    dump_conn(&server_conn);
    while(1)
    {
//        if(server_conn.available == NO)
//        {
//            REG_ID_RQT_CMD_t rqt;
//            rqt.id = server_conn.from;
//            send_REG_ID_RQT_CMD_and_wait(&server_conn, &rqt);
//        }
        handle_received_cmds();
//        if(KICK_OFF_TRIGGER == 0)
//        {
//            while(server_conn.available == NO)
//            {
//                REG_ID_RQT_CMD_t rqt;
//                rqt.id = server_conn.from;
//                send_REG_ID_RQT_CMD_and_wait(&server_conn, &rqt);
//                __delay_ms(200);
//            }
//        }
//            if(get_msg(pmsg_rcv) == YES)
//            {
//                dump_msg(pmsg_rcv);
//            }
//        RECEIVE_HALF_BYTE(revc, 1, DATA_IN3, DATA_IN2, DATA_IN1, DATA_IN0, DATA_IN_TRIGGER);
//        SEND_HALF_BYTE(revc, 1, DATA_OUT3, DATA_OUT2, DATA_OUT1, DATA_OUT0, DATA_OUT_TRIGGER);

//            CLIENT_REG_ID(pmsg, &server_conn, DATA_IN3, DATA_IN2, DATA_IN1, DATA_IN0, DATA_IN_TRIGGER, 
//                          pmsg, DATA_OUT3, DATA_OUT2, DATA_OUT1, DATA_OUT0, DATA_OUT_TRIGGER);        
//          RECEIVE_MSG(pmsg, DATA_IN3, DATA_IN2, DATA_IN1, DATA_IN0, DATA_IN_TRIGGER);
//          DEBUG_LINE_CLEAR; DEBUG_STRING_X(0, "RCV:"); DEBUG_INT(crc_verify(pmsg), 3);

//        if(reveive_finished() == YES)
        {
//            RECEIVE_MSG_ACK(pmsg, DATA_IN3, DATA_IN2, DATA_IN1, DATA_IN0, DATA_IN_TRIGGER, 
//                                  DATA_OUT3, DATA_OUT2, DATA_OUT1, DATA_OUT0, DATA_OUT_TRIGGER);
//            RECEIVE_MSG(pmsg, DATA_IN3, DATA_IN2, DATA_IN1, DATA_IN0, DATA_IN_TRIGGER);
//            count++;
//            DEBUG_LINE_CLEAR; DEBUG_STRING_X(0, "RCV:"); DEBUG_INT(index, 3);
//              dump_msg(pmsg_rcv);
//            DEBUG_LINE_CLEAR; DEBUG_STRING_X(0, "RCV:"); DEBUG_INT(count, 3);

//            RECEIVE_HALF_BYTE_ACK(ret, value, 1, DATA_IN3, DATA_IN2, DATA_IN1, DATA_IN0, DATA_IN_TRIGGER, 
//                                               DATA_OUT3, DATA_OUT2, DATA_OUT1, DATA_OUT0, DATA_OUT_TRIGGER);
//            DEBUG_LINE_CLEAR; DEBUG_STRING_X(0, "ret:"); DEBUG_INT(value, 3);
            
//            CLIENT_REG_ID(pmsg, &server_conn, DATA_IN3, DATA_IN2, DATA_IN1, DATA_IN0, DATA_IN_TRIGGER, 
//                          pmsg, DATA_OUT3, DATA_OUT2, DATA_OUT1, DATA_OUT0, DATA_OUT_TRIGGER);        
        }
//        else
//        {
//            if(MENU_IN == 0)
//            {
//                if(mode == NORMAL)
//                {
//                    DEBUG_STRING_CLEAR("MENU MODE");
//                    mode = MENU;
//                    ShowMenu();
//                }
//                else
//                {
//                    DEBUG_STRING_CLEAR("EDIT MODE");
//                    submode = EDIT;
//                    ShowMenu();
//                    LCDSetStyle(LS_BLINK);
//                }
//
//                __delay_ms(200);
//            }
//            else if(MENU_OUT == 0)
//            {
//                if(mode == MENU)
//                {
//                    if(submode == EDIT)
//                    {
//                        DEBUG_STRING_CLEAR("NOTEDIT MODE");
//                        submode = NOTEDIT;
//                        LCDSetStyle(LS_NONE);
//                    }
//                    else
//                    {
//                        DEBUG_STRING_CLEAR("NORMAL MODE");
//                        mode = NORMAL;
//                        ClearMenu();
//                    }
//                }
//
//                __delay_ms(200);
//            }
//            else if(UP == 0)
//            {
//                DEBUG_STRING_CLEAR("UP");
//                if(mode == MENU)
//                {
//                    if(submode == EDIT)
//                    {
//                        ValueInc();
//                    }            
//                    else
//                    {
//                        MenuUp();
//                    }
//                    ShowMenu();                
//                }
//                __delay_ms(200);
//            }
//            else if(DOWN == 0)
//            {
//                DEBUG_STRING_CLEAR("DOWN");
//                if(mode == MENU)
//                {
//                    if(submode == EDIT)
//                    {
//                        ValueDec();
//                    }            
//                    else
//                    {
//                        MenuDown();
//                    }
//                    ShowMenu();
//                }
//                __delay_ms(200);
//            }
//        }
    }
}

