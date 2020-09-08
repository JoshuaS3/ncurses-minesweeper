#include <stdio.h>
#include <ncurses.h>

int main(void) {
    initscr();
    noecho();
    clear();

    mvaddstr(0, 0, "Hello, World!");
    mvprintw(LINES-1, 0, "%d lines, %d rows", LINES, COLS);

    refresh();
    int c;
    while ((c = getch())) {
        move(LINES-2,0);
        clrtoeol();
        mvprintw(LINES-2, 0, "%i", c);
        if (c == 27 || c == 'q' || c == 'Q') { // 27 := <ESC>
            endwin();
            break;
        }
    }
    return 0;
}
