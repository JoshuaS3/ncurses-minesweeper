/* ncurses-minesweeper Copyright (c) 2021 Joshua 'joshuas3' Stockin
 * <https://joshstock.in>
 * <https://git.joshstock.in/ncurses-minesweeper>
 *
 * This software is licensed and distributed under the terms of the MIT License.
 * See the MIT License in the LICENSE file of this project's root folder.
 *
 * This comment block and its contents, including this disclaimer, MUST be
 * preserved in all copies or distributions of this software's source.
 */

#include <ncurses.h>

#include "../state.h"
#include "../strings.h"
#include "pages.h"

int draw(game_state *state, int ch) {
    int ret = 0;

    // Map input
    if (ch == 'h' || ch == 'H') ch = KEY_LEFT;
    if (ch == 'j' || ch == 'J') ch = KEY_DOWN;
    if (ch == 'k' || ch == 'K') ch = KEY_UP;
    if (ch == 'l' || ch == 'L') ch = KEY_RIGHT;
    if (ch == 'q' || ch == 'Q') ch = 27;
    if (ch == 10 || ch == ' ')  ch = KEY_ENTER;

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
        case About: {
            ret = draw_about_screen(state, ch);
            break;
        }
        default:
            return 1;
    }

    if (ch != -1) mvprintw(LINES - 1, 0, "%04i", ch); // print most recent character press

    if (LINES < (state->board->height + 1) || LINES < 17 || COLS/2 < (state->board->width) || COLS < 20) attron(COLOR_PAIR(3));
    mvprintw(LINES - 1, COLS - 6, "%03ix%02i", COLS/2, LINES); // print screen resolution
    if (LINES < (state->board->height + 1) || LINES < 17 || COLS/2 < (state->board->width) || COLS < 20) attroff(COLOR_PAIR(3));

    refresh();
    return ret;
}

void draw_loop(game_state *state) {
    int ch = 0;
    while ((ch = getch())) {
        if (draw(state, ch)) break; // break loop on non-zero return
    }
}
