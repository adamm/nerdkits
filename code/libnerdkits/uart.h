#ifndef __UART_H
#define __UART_H

#include <inttypes.h>
#include <stdio.h>

FILE mystream;

void uart_init();
void uart_write(char x);
uint8_t uart_char_is_waiting();
char uart_read();

int uart_putchar(char x, FILE *stream);
int uart_getchar(FILE *stream);

#endif
