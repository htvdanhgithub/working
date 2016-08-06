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

#define ALERT_PORT      A
#define ALERT_POS       0
#define ALERT_PIN       PIN(ALERT_PORT, ALERT_POS)
#define ALERT           PORTBIT(ALERT_PIN)
#define ALERT_AN_PORT      A
#define ALERT_AN_POS       0
#define ALERT_AN_PIN       PIN(ALERT_PORT, ALERT_POS)

#define LED_A_OUT_PORT      C
#define LED_A_OUT_POS       1
#define LED_A_OUT_PIN       PIN(LED_A_OUT_PORT, LED_A_OUT_POS)
#define LED_A_OUT           PORTBIT(LED_A_OUT_PIN)
#define LED_A_AN_PORT      C
#define LED_A_AN_POS       1
#define LED_A_AN_PIN       PIN(LED_A_AN_PORT, LED_A_AN_POS)

#define LED_B_OUT_PORT      C
#define LED_B_OUT_POS       0
#define LED_B_OUT_PIN       PIN(LED_B_OUT_PORT, LED_B_OUT_POS)
#define LED_B_OUT           PORTBIT(LED_B_OUT_PIN)
#define LED_B_AN_PORT      C
#define LED_B_AN_POS       0
#define LED_B_AN_PIN       PIN(LED_B_AN_PORT, LED_B_AN_POS)

#define LED_C_OUT_PORT      A
#define LED_C_OUT_POS       4
#define LED_C_OUT_PIN       PIN(LED_C_OUT_PORT, LED_C_OUT_POS)
#define LED_C_OUT           PORTBIT(LED_C_OUT_PIN)
#define LED_C_AN_PORT      A
#define LED_C_AN_POS       4
#define LED_C_AN_PIN       PIN(LED_C_AN_PORT, LED_C_AN_POS)

#define DATA_IN0_PORT      C
#define DATA_IN0_POS       2
#define DATA_IN0_PIN       PIN(DATA_IN0_PORT, DATA_IN0_POS)
#define DATA_IN0           PORTBIT(DATA_IN0_PIN)
#define DATA_IN0_AN_PORT      C
#define DATA_IN0_AN_POS       2
#define DATA_IN0_AN_PIN       PIN(DATA_IN0_AN_PORT, DATA_IN0_AN_POS)

#define DATA_IN1_PORT      C
#define DATA_IN1_POS       3
#define DATA_IN1_PIN       PIN(DATA_IN1_PORT, DATA_IN1_POS)
#define DATA_IN1           PORTBIT(DATA_IN1_PIN)
#define DATA_IN1_AN_PORT      C
#define DATA_IN1_AN_POS       3
#define DATA_IN1_AN_PIN       PIN(DATA_IN1_AN_PORT, DATA_IN1_AN_POS)

#define DATA_IN2_PORT      C
#define DATA_IN2_POS       4
#define DATA_IN2_PIN       PIN(DATA_IN2_PORT, DATA_IN2_POS)
#define DATA_IN2           PORTBIT(DATA_IN2_PIN)
#define DATA_IN2_AN_PORT      C
#define DATA_IN2_AN_POS       4
#define DATA_IN2_AN_PIN       PIN(DATA_IN2_AN_PORT, DATA_IN2_AN_POS)

#define DATA_IN3_PORT      C
#define DATA_IN3_POS       5
#define DATA_IN3_PIN       PIN(DATA_IN3_PORT, DATA_IN3_POS)
#define DATA_IN3           PORTBIT(DATA_IN3_PIN)
#define DATA_IN3_AN_PORT      C
#define DATA_IN3_AN_POS       5
#define DATA_IN3_AN_PIN       PIN(DATA_IN3_AN_PORT, DATA_IN3_AN_POS)
    
#ifdef	__cplusplus
}
#endif

#endif	/* IO_DEFINE_H */

