#include <ncurses.h>

#include "../game/game.h"
#include "../state.h"
#include "pages.h"
#include "text.h"

int draw_game(game_state *state, int ch) {
    if (ch == 'q' || ch == 'Q') {
        state->board->status = Playing;
        state->page = Title;
        state->page_selection = 0;
        return draw_title_screen(state, 0);
    } else if (ch == 'r' || ch == 'R')
        ch = 0;
    game(state, ch);
    game_board *board = state->board;
    mvprintw(0, 20, "MINES LEFT: %d", board->mines_left);
    switch (board->status) {
        case Playing:
            mvaddstr(0, centerx("o_o"), "o_o");
            break;
        case Done:
            mvaddstr(0, centerx("^_^"), "^_^");
            break;
        case Kaboom:
            mvaddstr(0, centerx("x_x"), "x_x");
            break;
    }
    attron(A_BOLD);
    for (int cell = 0; cell < board->width * board->height; cell++) {
        if (board->current_cell == cell) attron(A_STANDOUT);
        int x = (int)(COLS / 2) - board->width + cell % board->width * 2;
        int y = 1 + cell / board->width;
        if (board->current_cell == cell) attron(A_STANDOUT);
        if (board->cells[cell].flagged) {
            if (board->status == Playing)
                mvaddch(y, x, 'F');
            else {
                if (!board->cells[cell].is_bomb) {
                    attron(A_STANDOUT | COLOR_PAIR(5));
                    mvaddch(y, x, 'F');
                    attroff(A_STANDOUT | COLOR_PAIR(5));
                } else
                    mvaddch(y, x, 'F');
            }
        } else {
            if (board->cells[cell].opened) {
                if (board->cells[cell].is_bomb) {
                    attron(A_BOLD | COLOR_PAIR(5));
                    mvaddch(y, x, 'X');
                    attroff(A_BOLD | COLOR_PAIR(5));
                } else if (board->cells[cell].surrounding_bomb_count) {
                    attron(COLOR_PAIR(board->cells[cell].surrounding_bomb_count));
                    mvaddch(y, x, '0' + board->cells[cell].surrounding_bomb_count);
                    attroff(COLOR_PAIR(board->cells[cell].surrounding_bomb_count));
                } else {
                    mvaddch(y, x, ' ');
                }
            } else {
                attroff(A_BOLD);
                mvaddch(y, x, '~');
                attron(A_BOLD);
            }
        }
        if (board->current_cell == cell) attroff(A_STANDOUT);
    }
    attroff(A_BOLD);
    return 0;
}
