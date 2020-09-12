#include <ncurses.h>
#include <string.h>

int centerx(const char* txt) {
    size_t ln = strlen(txt);
    int x = (int)(COLS / 2 - ln / 2);
    return x;
}

int centery() {
    int y = (LINES / 2);
    return y;
}
