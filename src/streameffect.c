/*
 * Author: Matti Kuonanoja (2015)
 */

#include <c64.h>
#include <conio.h>
#include <stdlib.h>
#include "streameffect.h"
#include "backgroundimage.h"
#include "textscreen.h"

#define SCREEN_WIDTH 40
#define SCREEN_HEIGHT 25

struct stream {
    char column;
    char row;
    char delay;
    char length;
    signed char wait_counter;
    char placeholder[3]; //  8 byte element size can be looped faster in arrays
};

static char column_user_counts[SCREEN_WIDTH];

static struct stream streams[STREAM_COUNT];

void reset_stream(struct stream *stream);
void update_stream(struct stream *stream);
void update_stream_graphics(struct stream *stream);

void stream_effect_init(void) {
    char x;

    bgcolor(COLOR_BLACK);
    bordercolor(COLOR_BLACK);
    clrscr();
    enable_upper_charset(1);
    
    for (x = 0; x < SCREEN_WIDTH; ++x) {
        column_user_counts[x] = 0;
    }

    for (x = 0; x < STREAM_COUNT; ++x) {
        streams[x].column = 0;
        reset_stream(&streams[x]);
    }
}

void stream_effect_update(void) {
    static int x;
    struct stream* ptr = streams;
    for (x = 0; x < STREAM_COUNT; ++x) {
        update_stream(ptr);
        ptr++;
    }
}

char get_pseudo_random_byte(char min, char max) {
    return (rand() % (max - min + 1)) + min;
}

char search_free_column() {
    char column;
    char column_found = 0;
    char try_counter = 0;

    while (!column_found) {
        column = get_pseudo_random_byte(0, SCREEN_WIDTH - 1);
        if (column_user_counts[column] == 0) {
            column_found = 1;
        } else {
            ++try_counter;
            if (try_counter >= MAX_EMPTY_COLUMN_SEARCH_TRIES) {
                column_found = 1;
            } 
        }            
    }
    return column;
}

void reset_stream(struct stream *stream) {
    char next_column;
    
    if (column_user_counts[stream->column] > 0)
        --column_user_counts[stream->column];
    next_column = search_free_column();
    column_user_counts[next_column]++;
    
    stream->column = next_column; 
    stream->row = 0;
    stream->delay = get_pseudo_random_byte(STREAM_DELAY_MIN, STREAM_DELAY_MAX);
    stream->wait_counter = stream->delay;
    stream->length = stream->delay + get_pseudo_random_byte(STREAM_LENGTH_MIN, STREAM_LENGTH_MAX);
    if (stream->length > STREAM_LENGTH_MAX) {
        stream->length = STREAM_LENGTH_MAX;
    }
}

void update_stream(struct stream *stream) {
    if (stream->wait_counter > 0) {
        --stream->wait_counter;
        return;
    }
    stream->wait_counter = stream->delay;
    ++stream->row;
    update_stream_graphics(stream);
}

void update_stream_graphics(struct stream *stream) {
    signed char row = stream->row;
    signed char head_painter = row - 1;
    signed char body_painter = head_painter - HEAD_LENGTH;
    signed char tail_painter = body_painter - BODY_LENGTH;
    signed char tail_eraser = row - stream->length;

    if (tail_eraser >= SCREEN_HEIGHT) {
        reset_stream(stream);
        return;
    }

    set_column(stream->column);

    if (row < SCREEN_HEIGHT) {
        set_column_color(row, COLOR_WHITE);
        write_column_char(row, get_pseudo_random_byte(CHARSET_START, CHARSET_END));        
    }

    if (head_painter <= tail_eraser) {
        head_painter = -1;
    }
    
    if (body_painter <= tail_eraser) {
        body_painter = -1;
    }

    if (tail_painter <= tail_eraser) {
        tail_painter = -1;
    }

    if (head_painter >= 0 && head_painter < SCREEN_HEIGHT) {
        set_column_color(head_painter, COLOR_CYAN);
    }

    if (body_painter >= 0 && body_painter < SCREEN_HEIGHT) {
        set_column_color(body_painter, COLOR_LIGHTGREEN);
    }

    if (tail_painter >= 0 && tail_painter < SCREEN_HEIGHT) {
        set_column_color(tail_painter, COLOR_GREEN);
    }

    if (tail_eraser >= 0 && tail_eraser < SCREEN_HEIGHT) {
        if (is_background_pixel_on(stream->column, tail_eraser)) {
            set_column_color(tail_eraser, get_pseudo_random_byte(0, 1) != 0 ? COLOR_BLUE : COLOR_LIGHTBLUE);
            write_column_char(tail_eraser, 46);
        } else {
            clear_column_char(tail_eraser);
        }
    }
}