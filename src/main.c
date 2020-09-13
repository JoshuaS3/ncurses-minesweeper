#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#include "colors.h"
#include "draw/draw.h"
#include "state.h"

int main(void) {
    printf("ncurses-minesweeper Copyright (c) Joshua 'joshuas3' Stockin 2020\n");
    printf("<https://joshstock.in>\n");
    printf("<https://github.com/JoshuaS3/ncurses-minesweeper>\n");

    game_state *state = calloc(1, sizeof(game_state));
    state->page = Title;
    state->page_selection = 0;
    game_board *board = calloc(1, sizeof(game_board));
    state->board = board;
    state->board->width = 30;
    state->board->height = 16;
    state->board->mine_count = 99;

    initscr();
    noecho();
    cbreak();

    if (!has_colors()) {
        printf("Your terminal doesn't support color.\n");
        endwin();
        return 1;
    }
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
