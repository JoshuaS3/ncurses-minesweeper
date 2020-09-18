/* ncurses-minesweeper Copyright (c) 2020 Joshua 'joshuas3' Stockin
 * <https://joshstock.in>
 * <https://github.com/JoshuaS3/lognestmonster>
 *
 * This software is licensed and distributed under the terms of the MIT License.
 * See the MIT License in the LICENSE file of this project's root folder.
 *
 * This comment block and its contents, including this disclaimer, MUST be
 * preserved in all copies or distributions of this software's source.
 */

#include <ncurses.h>

#include "../state.h"
#include "constrain_movement.h"
#include "done.h"
#include "flag.h"
#include "nearest_cells.h"
#include "new.h"
#include "open.h"
#include "reset.h"


void game(game_state *state, int ch) {
    game_board *board = state->board;
    switch (ch) {
        case 'r':
        case 'R': {
            reset_board(board);
            break;
        }
        case 'j':
        case 'J': {
            constrain_down(board);
            break;
        }
        case 'k':
        case 'K': {
            constrain_up(board);
            break;
        }
        case 'h':
        case 'H': {
            constrain_left(board);
            break;
        }
        case 'l':
        case 'L': {
            constrain_right(board);
            break;
        }
        case 'f':
        case 'F': {
            flag_current_cell(board);
            break;
        }
        case 10:
        case ' ': {
            open_cell(board);
            check_done(board);
            break;
        }
    }
}
