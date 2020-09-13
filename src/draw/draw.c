#include <ncurses.h>

#include "../state.h"

#include "pages.h"
#include "text.h"
#include "winsize.h"


int draw(game_state *state, int ch) {
    clear();
    int ret = 0;
    switch (state->page) {
        case Title: {
            ret = draw_title_screen(state, ch);
            break;
        }
        case Game: {
            ret = draw_game(state, ch);
            break;
        }
        case Options: {
            ret = draw_options_screen(state, ch);
            break;
        }
        case Help: {
            ret = draw_help_screen(state, ch);
            break;
        }
        default:
            return 1;
    }
    draw_winsize();
    refresh();
    return ret;
}

void draw_loop(game_state *state) {
    int ch = 0;
    while ((ch = getch())) {
        if (draw(state, ch)) break;
    }
}
