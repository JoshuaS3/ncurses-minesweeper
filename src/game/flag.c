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

void flag_current_cell(game_board *board) {
    if (board->status == Playing && board->mines_left > 0) {
        game_board_cell *cell = &board->cells[board->current_cell];
        if (!cell->opened) {
            board->mines_left += cell->flagged * 2 - 1;
            cell->flagged = !cell->flagged;
        }
    } else
        beep();
}
