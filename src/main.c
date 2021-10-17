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
#include <stdio.h>
#include <stdlib.h>

#include "colors.h"
#include "draw/draw.h"
#include "game/reset.h"
#include "state.h"

int main(void) {
    initscr();
    if (!has_colors()) {
        endwin();
        printf("Your terminal doesn't support color.\n");
        return 1;
    }

    game_state *state = calloc(1, sizeof(game_state));
    state->page = Title;
    state->page_selection = 0;
    game_board *board = calloc(1, sizeof(game_board));
    state->board = board;
    board->status = Waiting;
    board->width = 30;
    board->height = 16;
    board->mine_count = 99;
    board->mines_left = 99;
    board->current_cell = board->width / 2;
    board->cells = NULL;
    reset_board(board);

    timeout(30);
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    init_colorpairs();
    curs_set(0);

    draw(state, 0);   // draw initial window
    draw_loop(state); // enter control input loop

    endwin();

    free(board->cells);
    free(board);
    free(state);

    return 0;
}
