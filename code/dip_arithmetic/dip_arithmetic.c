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
  DDRC &= ~(1<<PC1); // set PC1 as input
  DDRC &= ~(1<<PC2); // set PC2 as input
  DDRC &= ~(1<<PC3); // set PC3 as input
  DDRC &= ~(1<<PC4); // set PC4 as input
  DDRC &= ~(1<<PC5); // set PC5 as input
	  
  // turn on the internal resistors for the pins

  PORTC |= (1<<PC0); // turn on internal pull up resistor for PC0
  PORTC |= (1<<PC1); // turn on internal pull up resistor for PC1
  PORTC |= (1<<PC2); // turn on internal pull up resistor for PC2
  PORTC |= (1<<PC3); // turn on internal pull up resistor for PC3
  PORTC |= (1<<PC4); // turn on internal pull up resistor for PC6
  PORTC |= (1<<PC5); // turn on internal pull up resistor for PC7
  

  // declare the variables to represent each bit, of our two 3 bit numbers
  uint8_t a1;
  uint8_t a2;
  uint8_t a3;

  uint8_t b1;
  uint8_t b2;
  uint8_t b3;
  
  while(1) {
  
          // (PINC & (1<<PC0)) returns 8 bit number, 0's except position PC0 which is
          // the bit we want
          // shift it back by PC0 to put the bit we want in the 0th position.

	  a1 = (PINC & (1<<PC0)) >> PC0;
	  a2 = (PINC & (1<<PC1)) >> PC1;
	  a3 = (PINC & (1<<PC2)) >> PC2;
	  
	  b1 = (PINC & (1<<PC3)) >> PC3;
	  b2 = (PINC & (1<<PC4)) >> PC4;
	  b3 = (PINC & (1<<PC5)) >> PC5;
	  
     	  lcd_home();
	  lcd_write_string(PSTR("Adding: "));
	  lcd_write_int16((a1<<2) + (a2<<1) + a3);
	  lcd_write_data('+');
	  lcd_write_int16((b1<<2) + (b2<<1) + b3);
	  lcd_write_string(PSTR("        "));
	  
	  lcd_line_two();
	  lcd_write_string(PSTR("Equals: "));
	  lcd_write_int16(  ((a1<<2) + (a2<<1) + a3)  +  ((b1<<2) + (b2<<1) + b3) );
	  lcd_write_string(PSTR("        "));
	  
	  //delay_ms(500);
	  
  }
  return 0;
}
