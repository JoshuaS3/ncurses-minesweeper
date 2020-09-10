#include <ncurses.h>
#include <string.h>

int centerx(char* txt) {
    size_t ln = strlen(txt);
    int x = (int)(COLS/2) - (int)(ln/2);
    return x;
}

int centery() {
    int y = (int)(LINES/2);
    return y;
}

void flushright(int line, char* txt) {
    size_t ln = strlen(txt);
    int x = COLS - 1 - ln;
    mvprintw(line, x, txt);
    move(0,0);
}
