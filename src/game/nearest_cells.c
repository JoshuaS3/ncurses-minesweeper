#include <stdlib.h>

#include "../state.h"

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
        if (c != cell && !x->opened) {
            x->opened = 1;
            if (x->surrounding_bomb_count == 0 && !x->is_bomb && !x->flagged) recursively_open_nearby_cells(board, c);
        }
    }
    free(nearby);
}
