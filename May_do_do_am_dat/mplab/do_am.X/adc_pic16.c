#include <xc.h>
#include <stdint.h>

#include "adc_pic16.h"


void ADCInit()
{
// 1. Port configuration
    ADC_LM35_TRIS = 1; // Input
    ANSELAbits.ANSA2 = 1;  // RA2: analog input
// 2. Channel selection
    ADCON0bits.CHS = 0b010;
// 3. ADC voltage reference selection
    ADCON1bits.ADPREF = 0b00; // VREF+ is connected to AVDD
// 4. ADC conversion clock source
    ADCON1bits.ADCS = 0b011; // FRC (clock supplied from a dedicated RC oscillator)
// 5. Interrupt control
// 6. Result formatting    
    ADCON1bits.ADFM=1;
// 7. Turn on ADC Module    
    ADCON0bits.ADON = 1;

///////////////////////    
//  ADCON1bits.ADFM=1;
//
//  //All 8 pins as analog inputs
//  //Vref+ = VDD
//  //Vref- = VSS
//  ADCON1bits.PCFG=0x00;
//
//  //ADC Clock = Fosc/64
//  ADCON0bits.ADCS=0b10;
//  ADCON1bits.ADCS2=1;
//
//  //Turn on ADC Module
//  ADCON0bits.ADON=1;
  
}
uint16_t ReadADC(uint8_t ch)
{
  if(ch>7) return 0;

  ADCON0bits.CHS=ch;

  //Wait for aquisition
  __delay_us(100);

  //Start Conversion
  ADCON0bits.GO=1;

  //Wait for the conversion to complete
  while(ADCON0bits.GO);

  return ((ADRESH<<8)|ADRESL);

}