// trafficlight.c
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
// PC0 -- temperature sensor analog input
// PC1 -- side1 RED
// PC2 -- side1 YEL
// PC3 -- side1 GRN
// PC5 -- "walk" button (pulled to ground when pressed)
// PB1 -- side2 RED
// PB2 -- side2 YEL
// PB3 -- side2 GRN
//
// Note: all six LEDs have their positive terminal (anode, the longer lead)
// connected to the microcontroller port specified, and the negative terminal
// (cathode, the shorter lead) into ground.
// Also notice that there's a small bite of the LED plastic on one side,
// indicating the cathode.

void adc_init() {
  // set analog to digital converter
  // for external reference (5v), single ended input ADC0
  ADMUX = 0;

  // set analog to digital converter
  // to be enabled, with a clock prescale of 1/128
  // so that the ADC clock runs at 115.2kHz.
  ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);

  // fire a conversion just to get the ADC warmed up
  ADCSRA |= (1<<ADSC);
}

uint16_t adc_read() {
  // read from ADC, waiting for conversion to finish
  // (assumes someone else asked for a conversion.)
  // wait for it to be cleared
  while(ADCSRA & (1<<ADSC)) {
    // do nothing... just hold your breath.
  }
  // bit is cleared, so we have a result.

  // read from the ADCL/ADCH registers, and combine the result
  // Note: ADCL must be read first (datasheet pp. 259)
  uint16_t result = ADCL;
  uint16_t temp = ADCH;
  result = result + (temp<<8);

  // set ADSC bit to get the *next* conversion started
  ADCSRA |= (1<<ADSC);
  
  return result;
}

double sampleToFahrenheit(uint16_t sample) {
  // conversion ratio in DEGREES/STEP:
  // (5000 mV / 1024 steps) * (1 degree / 10mV)
  //	^^^^^^^^^^^		 ^^^^^^^^^^
  //     from ADC		  from LM34
  return sample * (5000.0 / 1024.0 / 10.0);  
}

void set_lights(uint8_t lights) {
  // the bits of lights tells us which LEDs to turn on:
  // 	Bit#	Light
  //	7	
  //	6	side2 GRN
  //	5	side2 YEL
  //	4	side2 RED
  //	3
  //	2	side1 GRN
  //	1	side1 YEL
  //	0	side1 RED

  // set side1:
  PORTC &= ~(0x07 << PC1);
  PORTC |= (lights & 0x07) << PC1;
  
  // set side2
  PORTB &= ~(0x07 << PB1);
  PORTB |= ((lights >> 4) & (0x07)) << PB1;
}


int main() {
  // enable the LED pins as outputs
  DDRC |= 0x07 << PC1;
  DDRB |= 0x07 << PB1;

  // enable internal pullup resistor on PC5 (the button)
  PORTC |= (1<<PC5);

  // start up the LCD
  lcd_init();
  FILE lcd_stream = FDEV_SETUP_STREAM(lcd_putchar, 0, _FDEV_SETUP_WRITE);
  lcd_home();

  // start up the Analog to Digital Converter
  adc_init();  

#define STATE_1G	0
#define STATE_1Y	1
#define STATE_2G	2
#define STATE_2Y	3
#define STATE_WALK	4	
  // the state machine:
  //	State#	Description	Timeout	Target
  //	0	side1 GRN	800	1
  //	1	side1 YEL	200	2
  //	2	side2 GRN	600	3
  //	3	side3 YEL	200	4 (if walk) or 0
  //	4	WALK (RED/RED)	500	0

  // some state variables
  uint8_t state = STATE_1G;	// state number!
  uint16_t timeout=800;	// timeout, in centiseconds
  uint8_t walk=0;		// walk pressed?
  lcd_home();
  lcd_write_string(PSTR("Side 1 has GREEN. "));
  set_lights(0x14);

  // loop forever!
  while(1) {
    // check the walk button
    if((PINC & (1<<PC5)) == 0)
      walk = 1;
  
    // second line: timeout 
    lcd_line_two();
    lcd_write_int16_centi(timeout); // 4
    lcd_write_string(PSTR("seconds  "));
    // third line: temperature
    lcd_line_three();
    fprintf_P(&lcd_stream, PSTR("%.2f"), sampleToFahrenheit(adc_read())); // 5
    lcd_write_data(0xdf); 
    lcd_write_data('F');
    // fourth line: walk request
    lcd_line_four();
    if(walk) {
      lcd_write_string(PSTR("WALK requested... "));
    } else {
      lcd_write_string(PSTR("                  "));
    }

    // state transitions
    if(timeout == 0) {
      lcd_home();
      switch(state) {
        case STATE_1G:
          state = STATE_1Y;
          lcd_write_string(PSTR("Side 1 has YELLOW."));
          set_lights(0x12);
          timeout = 200;
          break;
        case STATE_1Y:
          state = STATE_2G;
          lcd_write_string(PSTR("Side 2 has GREEN. "));
          set_lights(0x41);
          timeout = 600;
          break;
        case STATE_2G:
          state = STATE_2Y;
          lcd_write_string(PSTR("Side 2 has YELLOW."));
          set_lights(0x21);
          timeout = 200;
          break;
        case STATE_2Y:
          if(walk) {
            state = STATE_WALK;
            lcd_write_string(PSTR("Cars stopped. WALK"));
            set_lights(0x11);
            timeout = 500;
            walk = 0;
          } else {
            state = STATE_1G;
            lcd_write_string(PSTR("Side 1 has GREEN. "));            
            set_lights(0x14);
            timeout = 800;
          }
          break;
        case STATE_WALK:
          state = STATE_1G;
          lcd_write_string(PSTR("Side 1 has GREEN. "));
          set_lights(0x14);
          timeout = 800;
          break;
      }
    }

    // delay a bit and decrement timeout
    delay_ms(95);
    timeout = timeout - 10;
  }
  
  return 0;
}
