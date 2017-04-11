#define DEBUG
#define V_DEBUG true

#include "Logger.h"

#define PIN_PUMP     8

#define DELAY_3HOURS      10800000  // 3*3600*1000
#define DELAY_3MUNITES    180000    // 3*60*1000

void PinSet(uint8_t pin, uint8_t value)
{
  LOG(V_DEBUG, "INFO: PinSet (%d, %d)\r\n", pin, value);  
  digitalWrite(pin, value);
}

void setup() {
#ifdef DEBUG  
  Serial.begin(9600);
#endif  
  LOG(V_DEBUG, "System starts...\r\n");  

  // put your setup code here, to run once:
  PinSet(PIN_PUMP, HIGH);
  delay(DELAY_3MUNITES);
  PinSet(PIN_PUMP, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(DELAY_3HOURS);
  PinSet(PIN_PUMP, HIGH);
  delay(DELAY_3MUNITES);
  PinSet(PIN_PUMP, LOW);

}
