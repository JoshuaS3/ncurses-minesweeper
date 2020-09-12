#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#include "text.h"

int draw_winsize() {
    size_t buffer_size = snprintf(NULL, 0, "%ix%i", COLS, LINES);
    mvprintw(LINES - 1, COLS - buffer_size, "%ix%i", COLS, LINES);
    return 0;
}
