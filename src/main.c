#include <stdio.h>
#include <ncurses.h>
#include "main.h"
#include "draw.h"

int main(void) {
    initscr();
    //noecho();
    cbreak();
    clear();

    draw(0);      // draw initial window
    draw_loop(); // enter control input loop

    endwin();
    return 0;
}
