#include <stdlib.h>
#include <time.h>

#include "../state.h"

int16_t *nearby_cells(uint16_t s, uint8_t w, uint8_t h) {
    int16_t *cells = malloc(sizeof(int16_t) * 9);
    cells[0] = s - w - 1;
    cells[1] = s - w;
    cells[2] = s - w + 1;
    cells[3] = s - 1;
    cells[4] = s;
    cells[5] = s + 1;
    cells[6] = s + w - 1;
    cells[7] = s + w;
    cells[8] = s + w + 1;
    if (s % w == 0) { // left edge
        cells[0] = s;
        cells[3] = s;
        cells[6] = s;
    }
    if ((s + 1) % w == 0) { // right edge
        cells[2] = s;
        cells[5] = s;
        cells[8] = s;
    }
    if (s < w) { // top edge
        cells[0] = s;
        cells[1] = s;
        cells[2] = s;
    }
    if (s > w * (h - 1)) { // bottom edge
        cells[6] = s;
        cells[7] = s;
        cells[8] = s;
    }
    return cells;
}

void new_game(game_board *board) {
    // generate board
    board->mines_left = board->mine_count;
    board->cells = calloc(board->width * board->height, sizeof(game_board_cell));

    // open start
    uint16_t s = board->current_cell;

    int16_t *open_start_cells = nearby_cells(s, board->width, board->height);

    for (int cell = 0; cell < 9; cell++) {
        board->cells[open_start_cells[cell]].is_bomb = 0;
        board->cells[open_start_cells[cell]].opened = 1;
    }

    free(open_start_cells);

    // generate mines
    int mines_generated = 0;
    uint16_t end = board->width * board->height;

    srand(time(0));

    while (mines_generated < board->mine_count) {
        int n = rand() % end;
        if (!board->cells[n].is_bomb && !board->cells[n].opened) {
            board->cells[n].is_bomb = 1;
            mines_generated++;
        }
    }

    // get surrounding mine counts
    for (int i = 0; i < end; i++) {
        if (board->cells[i].is_bomb) continue;
        int16_t *close_cells = nearby_cells(i, board->width, board->height);
        for (int j = 0; j < 9; j++) {
            int16_t close_cell = close_cells[j];
            if (close_cell != i && board->cells[close_cell].is_bomb) board->cells[i].surrounding_bomb_count++;
        }
        free(close_cells);
    }
}

void game(game_state *state, int ch) {
    if (ch == 0) { // create new game
        new_game(state->board);
    }
}
