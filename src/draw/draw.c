#include <ncurses.h>

#include "../state.h"

#include "text.h"
#include "title.h"
#include "winsize.h"


int draw(game_state *state, int ch) {
    clear();
    draw_winsize();
    int ret = 0;
    switch (state->page) {
        case Title: {
            ret = draw_title_screen(state, ch);
            break;
        }
        default:
            return 1;
    }
    refresh();
    return ret;
}

void draw_loop(game_state *state) {
    int ch = 0;
    while ((ch = getch())) {
        if (draw(state, ch)) break;
    }
}
