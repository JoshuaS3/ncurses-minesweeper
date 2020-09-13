#include <ncurses.h>

#include "../game/game.h"
#include "../state.h"
#include "pages.h"
#include "text.h"

int draw_game(game_state *state, int ch) {
    if (ch == 'q' || ch == 'Q') {
        state->page = Title;
        state->page_selection = 0;
        return draw_title_screen(state, 0);
    }
    game(state, ch);
    game_board *board = state->board;
    for (int cell = 0; cell < board->width * board->height; cell++) {
        int x = (int)(COLS / 2) - board->width + cell % board->width * 2;
        int y = 1 + cell / board->width;
        if (board->cells[cell].is_bomb) {
            attron(A_BOLD);
            mvaddch(y, x, 'X');
            attroff(A_BOLD);
        } else if (board->cells[cell].surrounding_bomb_count) {
            attron(COLOR_PAIR(board->cells[cell].surrounding_bomb_count));
            mvaddch(y, x, '0' + board->cells[cell].surrounding_bomb_count);
            attroff(COLOR_PAIR(board->cells[cell].surrounding_bomb_count));
        }
    }
    return 0;
}
