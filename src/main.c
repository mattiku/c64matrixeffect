/*
 * A simple Matrix text rain effect.
 *
 * Author: Matti Kuonanoja (2015)
 */

#include <c64.h>
#include <conio.h>
#include "streameffect.h"

void reset_screen_state(void);

int main(void) {
    stream_effect_init();
    
    while (!kbhit()) {
        stream_effect_update();
    }
    cgetc();
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