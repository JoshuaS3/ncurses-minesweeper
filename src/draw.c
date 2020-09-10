#include <ncurses.h>
#include "text.h"

int draw(int ch) {
    if (ch == 'q' || ch == 'Q') return 1; // exit condition
    clear();
    mvprintw(LINES-1, COLS-6, "%ix%i", COLS, LINES);
    refresh();
    return 0;
}

void draw_loop(void) {
    int ch;
    while ((ch = getch())) {
        if (draw(ch)) break;
    }
}
