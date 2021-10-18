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
#include "text.h"

int draw_help_screen(game_state *state, int ch) {
    // input handling
    switch (ch) {
        case -1:
            return 0;
        case KEY_RESIZE:
            clear();
            break;
        case 10:
        case ' ':
        case KEY_ENTER: {
            clear();
            state->page = state->last_page;
            if (state->page == Title)
                return draw_title_screen(state, 0);
            else if (state->page == Game)
                return draw_game(state, -2);
            break;
        }
        case 0:
            break;
        default:
            beep();
    }

    // draw help screen
    int top = centery() - (HELP_SCREEN_INFO_LEN / 2) - 3;
    if (top < 0) top = 0;

    attron(A_BOLD | COLOR_PAIR(2));
    mvaddstr(top, centerx(help_screen_title), help_screen_title);
    attroff(A_BOLD);

    int x = centerx(help_screen_info[0]);
    int y = top + 2;
    for (int i = 0; i < HELP_SCREEN_INFO_LEN; i++) mvaddstr(y++, x, help_screen_info[i]);

    attron(A_STANDOUT);
    mvaddstr(top + 3 + HELP_SCREEN_INFO_LEN, centerx(help_screen_back), help_screen_back);
    attroff(A_STANDOUT | COLOR_PAIR(2));

    return 0;
}
