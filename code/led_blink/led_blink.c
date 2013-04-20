// led_blink.c
// for NerdKits with ATmega168
// hevans@nerdkits.edu

#define F_CPU 14745600

#include <avr/io.h>
#include <inttypes.h>

#include "../libnerdkits/delay.h"
#include "../libnerdkits/lcd.h"

// PIN DEFINITIONS:
//
// PC4 -- LED anode

int main() {
  // LED as output
  DDRC |= (1<<PC4);
  
  // loop keeps looking forever
  while(1) {
    // turn on LED
    PORTC |= (1<<PC4);

    //delay for 500 milliseconds to let the light stay on
    delay_ms(500);

    // turn off LED
    PORTC &= ~(1<<PC4);

    //delay for 500 milliseconds to let the light stay off
    delay_ms(500);
   
  }
  
  return 0;
}
