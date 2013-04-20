// tempsensor.c
// for NerdKits with ATmega168
// mrobbins@mit.edu

#define F_CPU 14745600

#include <stdio.h>
#include <math.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <inttypes.h>

#include "../libnerdkits/delay.h"
#include "../libnerdkits/lcd.h"
#include "../libnerdkits/uart.h"

// PIN DEFINITIONS:
//
// PC0 -- temperature sensor analog input

void adc_init() {


}

uint16_t adc_read() {


}

double sampleToFahrenheit(uint16_t sample) {


}

int main() {

  
  while(1) {
   


    for(i=0; i<100; i++) {


    }
    
    
    // write message to LCD
    
    // write message to serial port

  } 

  return 0;
}
