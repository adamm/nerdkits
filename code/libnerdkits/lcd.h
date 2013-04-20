#ifndef __LCD_H
#define __LCD_H

void lcd_set_type_data();
void lcd_set_type_command();
void lcd_write_nibble(char c);
void lcd_write_byte(char c);
void lcd_clear_and_home();
void lcd_home();
void lcd_write_data(char c);
void lcd_write_int16(int16_t in);
void lcd_write_int16_centi(int16_t in);
void lcd_write_string(const char *x);
void lcd_line_one();
void lcd_line_two();
void lcd_line_three();
void lcd_line_four();
void lcd_goto_position(uint8_t row, uint8_t col);
void lcd_init();

#include <stdio.h>
int lcd_putchar(char x, FILE *stream);

#endif
