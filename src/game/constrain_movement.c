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

void constrain_up(game_board *board) {
    if (board->current_cell >= board->width)
        board->current_cell -= board->width;
    else
        beep();
}

void constrain_down(game_board *board) {
    if (board->current_cell < board->width * (board->height - 1))
        board->current_cell += board->width;
    else
        beep();
}

void constrain_left(game_board *board) {
    if (board->current_cell % board->width > 0)
        board->current_cell--;
    else
        beep();
}

void constrain_right(game_board *board) {
    if ((board->current_cell + 1) % board->width > 0)
        board->current_cell++;
    else
        beep();
}
