/*
 * Author: Matti Kuonanoja (2015)
 */

#include <time.h>
#include <conio.h>
#include "fps.h"

#define SAMPLE_COUNT 32

static unsigned char sample_counter = 0;

static unsigned int current_fps = 0;

unsigned int get_fps(char show) {
    static unsigned long time_passed;
    static unsigned long previous_system_clock;
    static unsigned long system_clock = 0;

    sample_counter++;
    if (sample_counter < SAMPLE_COUNT)
        return current_fps;
    sample_counter = 0;

    system_clock = clock();
    time_passed = system_clock - previous_system_clock;
    previous_system_clock = system_clock;
    current_fps = (CLOCKS_PER_SEC * SAMPLE_COUNT) / time_passed;

    if (show) {
        gotoxy(0,0);
        textcolor(COLOR_WHITE);
        cprintf("fps [%4i]    ",current_fps);
    }

    return current_fps;
}