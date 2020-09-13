#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#include "draw/draw.h"
#include "state.h"

int main(void) {
    printf("ncurses-minesweeper Copyright (c) Joshua 'joshuas3' Stockin 2020\n");
    printf("<https://joshstock.in>\n");
    printf("<https://github.com/JoshuaS3/ncurses-minesweeper>\n\n");

    printf("Initializing game state\n");
    game_state *state = calloc(1, sizeof(game_state));
    state->page = Title;
    state->page_selection = 0;
    game_board *board = calloc(1, sizeof(game_board));
    state->board = board;
    state->board->width = 30;
    state->board->height = 16;
    state->board->mine_count = 99;

    printf("Initializing ncurses\n");

    initscr();
    noecho();
    cbreak();
    curs_set(0);

    draw(state, 0);   // draw initial window
    draw_loop(state); // enter control input loop

    endwin();

    return 0;
}
