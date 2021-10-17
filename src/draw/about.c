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

int draw_about_screen(game_state *state, int ch) {
    // input handling
    switch (ch) {
        case -1:
            return 0;
        case KEY_RESIZE:
            clear();
            break;
        case KEY_ENTER: {
            clear();
            state->page = Title;
            return draw_title_screen(state, 0);
            break;
        }
        case 0:
            break;
        default:
            beep();
    }

    // draw help screen
    int top = centery() - 3;
    if (top < 0) top = 0;

    attron(A_BOLD | COLOR_PAIR(2));
    mvaddstr(top, centerx(about_screen_title), about_screen_title);
    attroff(A_BOLD);

    mvaddstr(top + 2, centerx(copyright_line), copyright_line);
    mvaddstr(top + 3, centerx(about_website_source), about_website_source);
    mvaddstr(top + 4, centerx(about_website_home), about_website_home);

    attron(A_STANDOUT);
    mvaddstr(top + 6, centerx(about_screen_back), about_screen_back);
    attroff(A_STANDOUT | COLOR_PAIR(2));

    return 0;
}
