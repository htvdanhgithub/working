#ifndef IO_DEFINE_H
#define	IO_DEFINE_H

#ifdef	__cplusplus
extern "C" {
#endif

#define KICK_OFF_TRIGGER_PORT      A
#define KICK_OFF_TRIGGER_POS       2
#define KICK_OFF_TRIGGER_PIN       PIN(KICK_OFF_TRIGGER_PORT, KICK_OFF_TRIGGER_POS)
#define KICK_OFF_TRIGGER           PORTBIT(KICK_OFF_TRIGGER_PIN)
#define KICK_OFF_TRIGGER_AN_PORT      A
#define KICK_OFF_TRIGGER_AN_POS       2
#define KICK_OFF_TRIGGER_AN_PIN       PIN(KICK_OFF_TRIGGER_PORT, KICK_OFF_TRIGGER_POS)

#define DATA_OUT_TRIGGER_PORT      A
#define DATA_OUT_TRIGGER_POS       0
#define DATA_OUT_TRIGGER_PIN       PIN(DATA_OUT_TRIGGER_PORT, DATA_OUT_TRIGGER_POS)
#define DATA_OUT_TRIGGER           PORTBIT(DATA_OUT_TRIGGER_PIN)
#define DATA_OUT_TRIGGER_AN_PORT      A
#define DATA_OUT_TRIGGER_AN_POS       0
#define DATA_OUT_TRIGGER_AN_PIN       PIN(DATA_OUT_TRIGGER_PORT, DATA_OUT_TRIGGER_POS)

#define DATA_OUT0_PORT      C
#define DATA_OUT0_POS       2
#define DATA_OUT0_PIN       PIN(DATA_OUT0_PORT, DATA_OUT0_POS)
#define DATA_OUT0           PORTBIT(DATA_OUT0_PIN)
#define DATA_OUT0_AN_PORT      C
#define DATA_OUT0_AN_POS       2
#define DATA_OUT0_AN_PIN       PIN(DATA_OUT0_AN_PORT, DATA_OUT0_AN_POS)

#define DATA_OUT1_PORT      C
#define DATA_OUT1_POS       3
#define DATA_OUT1_PIN       PIN(DATA_OUT1_PORT, DATA_OUT1_POS)
#define DATA_OUT1           PORTBIT(DATA_OUT1_PIN)
#define DATA_OUT1_AN_PORT      C
#define DATA_OUT1_AN_POS       3
#define DATA_OUT1_AN_PIN       PIN(DATA_OUT1_AN_PORT, DATA_OUT1_AN_POS)

#define DATA_OUT2_PORT      C
#define DATA_OUT2_POS       4
#define DATA_OUT2_PIN       PIN(DATA_OUT2_PORT, DATA_OUT2_POS)
#define DATA_OUT2           PORTBIT(DATA_OUT2_PIN)
#define DATA_OUT2_AN_PORT      C
#define DATA_OUT2_AN_POS       4
#define DATA_OUT2_AN_PIN       PIN(DATA_OUT2_AN_PORT, DATA_OUT2_AN_POS)

#define DATA_OUT3_PORT      C
#define DATA_OUT3_POS       5
#define DATA_OUT3_PIN       PIN(DATA_OUT3_PORT, DATA_OUT3_POS)
#define DATA_OUT3           PORTBIT(DATA_OUT3_PIN)
#define DATA_OUT3_AN_PORT      C
#define DATA_OUT3_AN_POS       5
#define DATA_OUT3_AN_PIN       PIN(DATA_OUT3_AN_PORT, DATA_OUT3_AN_POS)
    
#ifdef	__cplusplus
}
#endif

#endif	/* IO_DEFINE_H */
