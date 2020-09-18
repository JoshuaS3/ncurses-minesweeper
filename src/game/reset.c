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

#include <stdlib.h>
#include <time.h>

#include "../state.h"

void reset_board(game_board *board) {
    board->status = Waiting;
    board->mines_left = board->mine_count;
    board->time = time(NULL);
    for (int i = 0; i < board->width * board->height; i++) {
        game_board_cell *cell = &board->cells[i];
        cell->is_bomb = 0;
        cell->flagged = 0;
        cell->opened = 0;
        cell->surrounding_bomb_count = 0;
    }
}
