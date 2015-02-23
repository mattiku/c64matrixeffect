/*
 * Author: Matti Kuonanoja (2015)
 */

#include <peekpoke.h>
#include "textscreen.h"

#define SCREEN_WIDTH 40

const unsigned int CHARACTER_MEMORY_ADDRESS = 55296u;
const unsigned int CHARACTER_MEMORY = 1024u;
const char CLEAR_CHAR = 0x20;

void write_char(char x, char y, char c) {
    POKE(CHARACTER_MEMORY + x + y * SCREEN_WIDTH, c);
}

void clear_char(char x, char y) {
    POKE (CHARACTER_MEMORY + x + y * SCREEN_WIDTH, CLEAR_CHAR);
}

void set_color(char x, char y, char color) {
    POKE(CHARACTER_MEMORY_ADDRESS + x + y * SCREEN_WIDTH, color);
}

void enable_upper_charset(char enable) {
    if (enable)
        POKE(53272u, 21);
    else
        POKE(53272u, 23);
}