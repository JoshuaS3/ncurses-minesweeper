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

#include <stdlib.h>

#include "../state.h"
#include "../time.h"
#include "nearest_cells.h"

void begin_game(game_board *board) {
    // open start
    uint16_t s = board->current_cell;

    int16_t *open_start_cells = list_nearby_cells(board, s);

    for (int cell = 0; cell < 9; cell++) {
        board->cells[open_start_cells[cell]].opened = 1;
        board->cells[open_start_cells[cell]].is_bomb = 0;
    }

    // generate mines
    int mines_generated = 0;
    uint16_t end = board->width * board->height;

    srand(time_us());

    while (mines_generated < board->mine_count) {
        int n = rand() % end;
        game_board_cell *x = &board->cells[n];
        if (!x->is_bomb && !x->opened) {
            x->is_bomb = 1;
            mines_generated++;
        }
    }

    // get and label surrounding mine counts
    for (int i = 0; i < end; i++) {
        if (board->cells[i].is_bomb) continue;
        int16_t *close_cells = list_nearby_cells(board, i);
        for (int j = 0; j < 9; j++) {
            int16_t close_cell = close_cells[j];
            if (close_cell != i && board->cells[close_cell].is_bomb) board->cells[i].surrounding_bomb_count++;
        }
        free(close_cells);
    }

    // recursively open start area
    for (int cell = 0; cell < 9; cell++) {
        if (board->cells[open_start_cells[cell]].surrounding_bomb_count == 0)
            recursively_open_nearby_cells(board, open_start_cells[cell]);
    }
    free(open_start_cells);

    // start timer
    board->time = time_us();

    board->status = Playing;
}
