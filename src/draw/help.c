/* ncurses-minesweeper Copyright (c) 2021 Joshua 'joshuas3' Stockin
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
#include "text.h"

const char *help_screen_title = "HELP";

const char *help_screen_info[13] = {"Minesweeper is a logic game where mines are hidden in a grid of     ",
                                    "squares. The object is to open all the safe squares in the shortest",
                                    "time possible.",
                                    "",
                                    "Use the <ENTER> key or <SPACE> to select menu items or open unopened",
                                    "squares. Use the arrow keys or <hjkl> to move around. Use <f> to",
                                    "toggle flags on squares. Use <ENTER> or <SPACE> on a numbered square",
                                    "if enough surrounding squares are flagged in order to open remaining",
                                    "surrounding squares. Use <r> to reset the board and <q> to quit.",
                                    "",
                                    "See the [OPTIONS] screen to change game settings.",
                                    "",
                                    "A minimum terminal resolution of 80x20 is recommended."};

const char *help_screen_back = "Back";

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
    int mid = centery();

    attron(A_BOLD | COLOR_PAIR(2));
    mvaddstr(mid - 8, centerx(help_screen_title), help_screen_title);
    attroff(A_BOLD);

    int x = centerx(help_screen_info[0]);
    int y = mid - 6;
    for (int i = 0; i < 13; i++) mvaddstr(y++, x, help_screen_info[i]);

    attron(A_STANDOUT);
    mvaddstr(mid + 8, centerx(help_screen_back), help_screen_back);
    attroff(A_STANDOUT | COLOR_PAIR(2));

    return 0;
}
