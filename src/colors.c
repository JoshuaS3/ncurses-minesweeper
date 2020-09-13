#include <ncurses.h>

int init_colorpairs(void) {
    start_color();
    use_default_colors();
    init_pair(1, COLOR_BLUE, -1);
    init_pair(2, COLOR_GREEN, -1);
    init_pair(3, COLOR_RED, -1);
    init_pair(4, COLOR_MAGENTA, -1);
    init_pair(5, COLOR_RED, -1);
    init_pair(6, COLOR_CYAN, -1);
    init_pair(7, COLOR_BLACK, -1);
    init_pair(8, COLOR_MAGENTA, -1);
    return 0;
}
