/*
 * Author: Matti Kuonanoja (2015)
 */

#include <peekpoke.h>
#include "textscreen.h"

#define SCREEN_WIDTH 40

static const unsigned int CHARACTER_MEMORY_ADDRESS = 55296u;
static const unsigned int CHARACTER_MEMORY = 1024u;
static const char CLEAR_CHAR = 0x20;

static char column_x = 0;
static unsigned int column_top_char_ptr = 0;
static unsigned int column_top_color_ptr = 0;

static const unsigned int y_offsets[] = {0, 40, 80, 120, 160, 200, 240, 280, 320, 360, 400, 440, 480, 520, 560, 600, 640, 680, 720, 760, 800, 840, 880, 920, 960};

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

void set_column(char x) {
    column_x = x;
    column_top_char_ptr = CHARACTER_MEMORY + column_x;
    column_top_color_ptr = CHARACTER_MEMORY_ADDRESS + column_x;
}

void write_column_char(char y, char c) {
    POKE(column_top_char_ptr + y_offsets[y], c);
}

void clear_column_char(char y) {
    POKE(column_top_char_ptr + y_offsets[y], CLEAR_CHAR);
}

void set_column_color(char y, char color) {
    POKE(column_top_color_ptr + y_offsets[y], color);
}