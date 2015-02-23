/*
 * A simple Matrix text rain effect.
 *
 * Author: Matti Kuonanoja (2015)
 */

#include <c64.h>
#include <conio.h>
#include "streameffect.h"
#include "fps.h"

void reset_screen_state(void);

int main(void) {
    char key;
    char show_fps = 0;
    char quit = 0;

    stream_effect_init();

    while (!quit) {
        stream_effect_update();
        get_fps(show_fps);
        if (kbhit()){
            key = cgetc();
            if (key == 32)
                show_fps = !show_fps;
            else
                quit = 1;
        }
    }
    reset_screen_state();

    return 0;
}

void reset_screen_state(void) {
    bgcolor(COLOR_BLUE);
    bordercolor(COLOR_LIGHTBLUE);
    textcolor(COLOR_LIGHTBLUE);
    clrscr();
    gotoxy(0, 0);
    cursor(1);
}