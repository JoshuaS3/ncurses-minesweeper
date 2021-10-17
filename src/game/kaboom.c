/* ncurses-minesweeper Copyright (c) 2021 Joshua 'joshuas3' Stockin
 * <https://joshstock.in>
 * <https://git.joshstock.in/ncurses-minesweeper>
 *
 * This software is licensed and distributed under the terms of the MIT License.
 * See the MIT License in the LICENSE file of this project's root folder.
 *
 * This comment block and its contents, including this disclaimer, MUST be
 * preserved in all copies or distributions of this software's source.
 */

#include "../state.h"

void kaboom(game_board *board) {
    board->status = Kaboom;
    for (int i = 0; i < board->width * board->height; i++) {
        if (board->cells[i].is_bomb) board->cells[i].opened = 1;
    }
}
