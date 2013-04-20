#ifndef __DELAY_H
#define __DELAY_H

#include <inttypes.h>

#ifndef NOP
#define NOP __asm__ __volatile__ ("nop")
#endif

void delay_us(uint16_t us);
void delay_ms(uint16_t ms);

#endif
