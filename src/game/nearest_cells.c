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
#include "kaboom.h"

int16_t *list_nearby_cells(game_board *board, uint16_t cell) {
    int16_t *cells = (int16_t *)calloc(9, sizeof(int16_t));
    if (cells == NULL) abort();
    uint8_t board_width = board->width;
    uint8_t board_height = board->height;
    cells[0] = cell - board_width - 1;
    cells[1] = cell - board_width;
    cells[2] = cell - board_width + 1;
    cells[3] = cell - 1;
    cells[4] = cell;
    cells[5] = cell + 1;
    cells[6] = cell + board_width - 1;
    cells[7] = cell + board_width;
    cells[8] = cell + board_width + 1;
    if (cell % board_width == 0) { // left edge
        cells[0] = cell;
        cells[3] = cell;
        cells[6] = cell;
    }
    if ((cell + 1) % board_width == 0) { // right edge
        cells[2] = cell;
        cells[5] = cell;
        cells[8] = cell;
    }
    if (cell < board_width) { // top edge
        cells[0] = cell;
        cells[1] = cell;
        cells[2] = cell;
    }
    if (cell >= board_width * (board_height - 1)) { // bottom edge
        cells[6] = cell;
        cells[7] = cell;
        cells[8] = cell;
    }
    return cells;
}

void recursively_open_nearby_cells(game_board *board, uint16_t cell) {
    int16_t *nearby = list_nearby_cells(board, cell);
    for (int i = 0; i < 9; i++) {
        uint16_t c = nearby[i];
        game_board_cell *x = &board->cells[c];
        if (c != cell && !x->opened && !x->flagged) {
            // open unopened cell
            x->opened = 1;
            if (!x->is_bomb && x->surrounding_bomb_count == 0)
                // recursive open if not bomb, 0 surrounding bombs, AND not flagged
                recursively_open_nearby_cells(board, c);
            else if (x->is_bomb) {
                kaboom(board);
                break;
            }
        }
    }
    free(nearby);
}
