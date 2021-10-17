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
#include <stdlib.h>

#include "../state.h"
#include "kaboom.h"
#include "nearest_cells.h"
#include "new.h"

void open_cell(game_board *board) {
    if (board->status == Waiting) {        // game hasn't been started
        begin_game(board);                 // start new game at this position (generates new board)
    } else if (board->status == Playing) { // in play
        game_board_cell *cell = &board->cells[board->current_cell];
        if (!cell->flagged) { // not flagged
            if (!cell->opened) {
                cell->opened = 1;
                if (cell->is_bomb) {
                    kaboom(board);
                } else if (!cell->surrounding_bomb_count) // not a bomb
                    // no surrounding bombs -> open all surrounding cells
                    recursively_open_nearby_cells(board, board->current_cell);
            } else { // cell is already opened. check if # of surrounding flags == cell #
                // count surrounding flags
                int16_t *close_cells = list_nearby_cells(board, board->current_cell);
                int flag_count = 0;
                for (int i = 0; i < 9; i++) {
                    int16_t close_cell = close_cells[i];
                    if (close_cell != board->current_cell && board->cells[close_cell].flagged) flag_count++;
                }
                free(close_cells);
                // if # of surrounding flags == cell #, recursively open others
                if (flag_count == cell->surrounding_bomb_count) {
                    recursively_open_nearby_cells(board, board->current_cell);
                }
            }
        }
    } else
        beep();
}
