// dip_arithmetic.c
// for NerdKits with ATmega168
// hevans@mit.edu

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
// PC0 -- DIP SWITCH DP1
// PC1 -- DIP SWITCH DP2
// PC2 -- DIP SWITCH DP3
// PC3 -- DIP SWITCH DP4
// PC4 -- DIP SWITCH DP5
// PC5 -- DIP SWITCH DP6
//
// NOTE: (switches connects to GND when closed, otherwise
// the pin is internally pulled up through a pull-up resistor to VCC)

int main() {
  // start up the LCD
  lcd_init();
  lcd_home();

  // Set the 6 pins to input mode - Two 3 bit numbers  
  DDRC &= ~(1<<PC0); // set PC0 as input

	  
  // turn on the internal resistors for the pins
  PORTC |= (1<<PC0); // turn on internal pull up resistor for PA0

  

  // declare the variables to represent each bit, of our two 3 bit numbers
  uint8_t a1;

  
  while(1) {
  
          // (PINC & (1<<PC0)) returns 8 bit number, 0's except position PA0 which is
          // the bit we want
          // shift it back by PA0 to put the bit we want in the 0th position.

	  a1 = (PINC & (1<<PC0)) >> PC0;


	  
     	  lcd_home();

	  
  }
  return 0;
}
