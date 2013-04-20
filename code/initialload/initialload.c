// initialload.c
// for NerdKits with ATmega168
// mrobbins@mit.edu

#define F_CPU 14745600

#include <stdio.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <inttypes.h>

#include "../libnerdkits/delay.h"
#include "../libnerdkits/lcd.h"

// PIN DEFINITIONS:
//
// PC4 -- LED anode

int main() {
  // LED as output
  DDRC |= (1<<PC4);
  
  // turn on LED
  PORTC |= (1<<PC4);

  // fire up the LCD
  lcd_init();
  lcd_home();

  // print message to screen
  //			 20 columns wide:
  //                     01234567890123456789
  lcd_line_one();
  lcd_write_string(PSTR("  Congratulations!  "));
  lcd_line_two();
  lcd_write_string(PSTR("********************"));
  lcd_line_three();
  lcd_write_string(PSTR("  Your USB NerdKit  "));
  lcd_line_four();
  lcd_write_string(PSTR("      is alive!     "));
                
  // turn off that LED
  PORTC &= ~(1<<PC4);

  // busy loop
  while(1) {
    // do nothing
  }
  
  return 0;
}
