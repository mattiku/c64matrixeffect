/*
 * Author: Matti Kuonanoja (2015)
 */

#ifndef TEXT_SCREEN
#define TEXT_SCREEN

void write_char(char x, char y, char c);
void clear_char(char x, char y);
void set_color(char x, char y, char color);

void enable_upper_charset(char enable);

#endif // TEXT_SCREEN