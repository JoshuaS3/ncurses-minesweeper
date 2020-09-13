#include <stdlib.h>
#include <time.h>

#include <ncurses.h>

#include "../state.h"
#include "nearest_cells.h"

void new_game(game_board *board) {
    // create board
    board->status = Playing;
    board->mines_left = board->mine_count;
    if (board->cells) free(board->cells);
    board->cells = (game_board_cell *)calloc(board->width * board->height, sizeof(game_board_cell));
    if (board->cells == NULL) abort();

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

    srand(time(0));

    while (mines_generated < board->mine_count) {
        int n = rand() % (end - 1);
        game_board_cell *x = &board->cells[n];
        if (!x->is_bomb && !x->opened) {
            x->is_bomb = 1;
            mines_generated++;
        }
    }

    // get surrounding mine counts
    for (int i = 0; i < end; i++) {
        if (board->cells[i].is_bomb) continue;
        int16_t *close_cells = list_nearby_cells(board, i);
        for (int j = 0; j < 9; j++) {
            int16_t close_cell = close_cells[j];
            if (close_cell != i && board->cells[close_cell].is_bomb) board->cells[i].surrounding_bomb_count++;
        }
        free(close_cells);
    }

    // recursively open start
    for (int cell = 0; cell < 9; cell++) {
        if (board->cells[open_start_cells[cell]].surrounding_bomb_count == 0)
            recursively_open_nearby_cells(board, open_start_cells[cell]);
    }
    free(open_start_cells);
}

void game(game_state *state, int ch) {
    game_board *board = state->board;
    if (ch == 0) { // create new game
        new_game(board);
    }
    if (board->status == Kaboom) {
        beep();
        return;
    }
    if (ch == 'j' || ch == 'J') {
        if (board->current_cell < board->width * (board->height - 1))
            board->current_cell += board->width;
        else
            beep();
    } else if (ch == 'k' || ch == 'K') {
        if (board->current_cell >= board->width)
            board->current_cell -= board->width;
        else
            beep();
    } else if (ch == 'h' || ch == 'H') {
        if (board->current_cell % board->width > 0)
            board->current_cell -= 1;
        else
            beep();
    } else if (ch == 'l' || ch == 'L') {
        if ((board->current_cell + 1) % board->width > 0)
            board->current_cell += 1;
        else
            beep();
    } else if (ch == 'f' || ch == 'F') {
        game_board_cell *cell = &board->cells[board->current_cell];
        if (!cell->opened) {
            cell->flagged = !cell->flagged;
            board->mines_left -= cell->flagged * 2 - 1;
        }
    } else if (ch == 10 || ch == ' ') {
        game_board_cell *cell = &board->cells[board->current_cell];
        if (!cell->flagged) {
            if (!cell->opened) {
                cell->opened = 1;
                if (cell->is_bomb) {
                    board->status = Kaboom;
                    for (int i = 0; i < board->width * board->height; i++) {
                        if (board->cells[i].is_bomb) { board->cells[i].opened = 1; }
                    }
                } else if (!cell->surrounding_bomb_count)
                    recursively_open_nearby_cells(board, board->current_cell);
            } else {
                int16_t *close_cells = list_nearby_cells(board, board->current_cell);
                int flag_count = 0;
                for (int i = 0; i < 9; i++) {
                    int16_t close_cell = close_cells[i];
                    if (close_cell != board->current_cell && board->cells[close_cell].flagged) flag_count++;
                }
                free(close_cells);
                if (flag_count == cell->surrounding_bomb_count) {
                    recursively_open_nearby_cells(board, board->current_cell);
                }
            }
        }
    }
}
