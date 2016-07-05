#ifndef IO_DEFINE_H
#define	IO_DEFINE_H

#ifdef	__cplusplus
extern "C" {
#endif

#define KICK_OFF_TRIGGER_PORT      B
#define KICK_OFF_TRIGGER_POS       2
#define KICK_OFF_TRIGGER_PIN       PIN(KICK_OFF_TRIGGER_PORT, KICK_OFF_TRIGGER_POS)
#define KICK_OFF_TRIGGER           PORTBIT(KICK_OFF_TRIGGER_PIN)

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

#define DATA_OUT_TRIGGER_PORT      B
#define DATA_OUT_TRIGGER_POS       1
#define DATA_OUT_TRIGGER_PIN       PIN(DATA_OUT_TRIGGER_PORT, DATA_OUT_TRIGGER_POS)
#define DATA_OUT_TRIGGER           PORTBIT(DATA_OUT_TRIGGER_PIN)

#define DATA_OUT0_PORT      A
#define DATA_OUT0_POS       4
#define DATA_OUT0_PIN       PIN(DATA_OUT0_PORT, DATA_OUT0_POS)
#define DATA_OUT0           PORTBIT(DATA_OUT0_PIN)

#define DATA_OUT1_PORT      A
#define DATA_OUT1_POS       5
#define DATA_OUT1_PIN       PIN(DATA_OUT1_PORT, DATA_OUT1_POS)
#define DATA_OUT1           PORTBIT(DATA_OUT1_PIN)

#define DATA_OUT2_PORT      A
#define DATA_OUT2_POS       6
#define DATA_OUT2_PIN       PIN(DATA_OUT2_PORT, DATA_OUT2_POS)
#define DATA_OUT2           PORTBIT(DATA_OUT2_PIN)

#define DATA_OUT3_PORT      A
#define DATA_OUT3_POS       7
#define DATA_OUT3_PIN       PIN(DATA_OUT3_PORT, DATA_OUT3_POS)
#define DATA_OUT3           PORTBIT(DATA_OUT3_PIN)

#define DATA_IN_TRIGGER_PORT      B
#define DATA_IN_TRIGGER_POS       0
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
    
#ifdef	__cplusplus
}
#endif

#endif	/* IO_DEFINE_H */

