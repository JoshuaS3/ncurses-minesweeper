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

// TODO: rewrite this POS

#include <ncurses.h>

#include "../state.h"
#include "../strings.h"
#include "pages.h"
#include "text.h"

int digit_input(int line, int col) {
    // input of two digits for int
    move(line, col);
    clrtoeol();

    char in1, in2;
    uint8_t n = 0;

    // digit one (tens)
    attron(A_UNDERLINE);
    mvaddch(line, col, ' ');
    while ((in1 = getch())) {
        if (in1 >= '0' && in1 <= '9') {
            n = 10 * (in1 - '0');
            break;
        } else if (in1 > 0) // invalid input, beep
            beep();
    }
    attroff(A_UNDERLINE);
    mvaddch(line, col, in1);

    // digit two (ones)
    attron(A_UNDERLINE);
    mvaddch(line, col + 1, ' ');
    while ((in2 = getch())) {
        if (in2 >= '0' && in2 <= '9') {
            n += in2 - '0';
            break;
        } else if (in2 > 0) // invalid input, beep
            beep();
    }
    attroff(A_UNDERLINE);

    return n;
}

int draw_options_screen(game_state *state, int ch) {
    switch (ch) {
        case -1:
            return 0;
        case KEY_DOWN: {
            if (state->page_selection < 3)
                state->page_selection++;
            else
                beep();
            break;
        }
        case KEY_UP: {
            if (state->page_selection > 0)
                state->page_selection--;
            else
                beep();
            break;
        }
        case KEY_RESIZE:
            clear();
            break;
        case ' ':
        case 10:
        case KEY_ENTER: {
            if (state->page_selection == 3) {
                clear();
                state->page = Title;
                state->page_selection = 1;
                return draw_title_screen(state, 0);
            }
            break;
        }
        case 0:
            break;
        default:
            beep();
    }

    int y = centery();

    attron(A_BOLD | COLOR_PAIR(1));
    mvaddstr(y - 3, centerx(options_screen_title), options_screen_title);
    attroff(A_BOLD);

    int x = (int)(COLS / 2);
    mvaddstr(y - 1, x - 10, options_screen_width);
    mvaddstr(y, x - 10, options_screen_height);
    mvaddstr(y + 1, x - 10, options_screen_minecount);

    if (state->page_selection == 0) attron(A_STANDOUT);
    mvprintw(y - 1, x + 4, "%02d", state->board->width);
    if (state->page_selection == 0) attroff(A_STANDOUT);

    if (state->page_selection == 1) attron(A_STANDOUT);
    mvprintw(y, x + 4, "%02d", state->board->height);
    if (state->page_selection == 1) attroff(A_STANDOUT);

    if (state->page_selection == 2) attron(A_STANDOUT);
    mvprintw(y + 1, x + 4, "%02d", state->board->mine_count);
    if (state->page_selection == 2) attroff(A_STANDOUT);

    if (state->page_selection == 3) attron(A_STANDOUT);
    mvaddstr(y + 3, centerx(options_screen_back), options_screen_back);
    if (state->page_selection == 3) attroff(A_STANDOUT);

    if (ch == ' ' || ch == 10 || ch == KEY_ENTER) {
        int in = 0;
        switch (state->page_selection) {
            case 0: {
                while ((in = digit_input(y - 1, x + 4))) {
                    if (state->board->mine_count < in * state->board->height - 8)
                        break;
                    else
                        beep();
                }
                state->board->width = in;
                attron(A_STANDOUT);
                mvprintw(y - 1, x + 4, "%02d", state->board->width);
                attroff(A_STANDOUT);
                break;
            }
            case 1: {
                while ((in = digit_input(y, x + 4))) {
                    if (state->board->mine_count < state->board->width * in - 8)
                        break;
                    else
                        beep();
                }
                state->board->height = in;
                attron(A_STANDOUT);
                mvprintw(y, x + 4, "%02d", state->board->height);
                attroff(A_STANDOUT);
                break;
            }
            case 2: {
                while ((in = digit_input(y + 1, x + 4))) {
                    if (in < state->board->width * state->board->height - 8)
                        break;
                    else
                        beep();
                }
                state->board->mine_count = in;
                state->board->mines_left = in;
                attron(A_STANDOUT);
                mvprintw(y + 1, x + 4, "%02d", state->board->mine_count);
                attroff(A_STANDOUT);
                break;
            }
        }
        state->board->current_cell = state->board->width / 2;
    }

    attroff(COLOR_PAIR(1));

    return 0;
}
