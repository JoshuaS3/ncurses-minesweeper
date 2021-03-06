/* ncurses-minesweeper Copyright (c) 2020 Joshua 'joshuas3' Stockin
 * <https://joshstock.in>
 * <https://github.com/JoshuaS3/ncurses-minesweeper>
 *
 * This software is licensed and distributed under the terms of the MIT License.
 * See the MIT License in the LICENSE file of this project's root folder.
 *
 * This comment block and its contents, including this disclaimer, MUST be
 * preserved in all copies or distributions of this software's source.
 */

#include <ncurses.h>

#include "../state.h"
#include "pages.h"

int draw(game_state *state, int ch) {
    int ret = 0;

    // Map input
    if (ch == 'h' || ch == 'H') ch = KEY_LEFT;
    if (ch == 'j' || ch == 'J') ch = KEY_DOWN;
    if (ch == 'k' || ch == 'K') ch = KEY_UP;
    if (ch == 'l' || ch == 'L') ch = KEY_RIGHT;

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

    if (ch != -1) mvprintw(LINES - 1, 0, "%04i", ch); // print most recent character press

    if (LINES < 20 || COLS < 80) attron(COLOR_PAIR(3));
    mvprintw(LINES - 1, COLS - 7, "%03ix%03i", COLS, LINES); // print screen resolution
    if (LINES < 20 || COLS < 80) attroff(COLOR_PAIR(3));

    refresh();
    return ret;
}

void draw_loop(game_state *state) {
    int ch = 0;
    while ((ch = getch())) {
        if (draw(state, ch)) break; // break loop on non-zero return
    }
}
