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

#include "../game/game.h"
#include "../game/reset.h"
#include "../state.h"
#include "../time.h"
#include "../strings.h"
#include "pages.h"
#include "text.h"

static int elapsed = 0;
void render_topbar(int top, int left, int right, game_board *board) {
    if (board->status == Waiting) {
        elapsed = 0;
    } else if (board->status == Playing) {
        elapsed = 1 + (time_us() - board->time) / 1000000;
    }
    attron(A_BOLD);
    if (elapsed < 999)
        mvprintw(top, right - 4, "%03d", elapsed);
    else
        mvaddstr(top, right - 4, "999");
    mvprintw(top, left, "%03d", board->mines_left);
    attroff(A_BOLD);
    int center = (int)(COLS / 2 - 1);
    switch (board->status) {
        case Waiting:
        case Playing:
            mvaddstr(top, center, "._.");
            break;
        case Done:
            mvaddstr(top, center, "^-^");
            break;
        case Kaboom:
            mvaddstr(top, center, "x_x");
            break;
    }
}

int draw_game(game_state *state, int ch) {
    game_board *board = state->board;
    int board_top = centery() - board->height/2 - 1;
    if (board_top < 0) board_top = 0;
    int bound_left = (int)(COLS / 2) - board->width;
    int bound_right = (int)(COLS / 2) + board->width;
    render_topbar(board_top, bound_left, bound_right, board);

    // handle input
    switch (ch) {
        case -1: {
            return 0;
        }
        case KEY_RESIZE: {
            clear();
            break;
        }
        case 27: {
            clear();
            reset_board(state->board);
            state->page = Title;
            state->page_selection = 0;
            return draw_title_screen(state, 0);
        }
    }

    game(state, ch); // pass input to game controller

    // draw board
    attron(A_BOLD);
    for (int cell = 0; cell < board->width * board->height; cell++) {
        int x = bound_left + cell % board->width * 2;
        int y = board_top + 1 + cell / board->width;
        if (board->current_cell == cell) attron(A_STANDOUT); // highlight selected cell
        game_board_cell *this_cell = &board->cells[cell];
        if (!this_cell->flagged) {
            if (!this_cell->opened) { // unopened unflagged, grey territory
                attroff(A_BOLD);
                mvaddch(y, x, '~');
                attron(A_BOLD);
            } else {                      // opened but unflagged
                if (this_cell->is_bomb) { // bomb opened
                    attron(COLOR_PAIR(5));
                    mvaddch(y, x, 'X');
                    attroff(COLOR_PAIR(5));
                } else if (this_cell->surrounding_bomb_count) { // surrounding bomb-count label
                    int count = this_cell->surrounding_bomb_count;
                    attron(COLOR_PAIR(count));
                    mvaddch(y, x, '0' + count);
                    attroff(COLOR_PAIR(count));
                } else { // no surrounding bombs, open area
                    mvaddch(y, x, ' ');
                }
            }
        } else { // flagged cell
            attron(A_STANDOUT);
            if (board->status != Kaboom)
                mvaddch(y, x, 'X');
            else {
                if (!board->cells[cell].is_bomb) { // highlight false positives when done
                    attron(COLOR_PAIR(5));
                    mvaddch(y, x, 'X');
                    attroff(COLOR_PAIR(5));
                } else
                    mvaddch(y, x, 'X');
            }
            attroff(A_STANDOUT);
        }
        if (board->current_cell == cell) attroff(A_STANDOUT); // un-highlight selected cell
    }
    attroff(A_BOLD);
    return 0;
}
