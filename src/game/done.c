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

#include <ncurses.h>

#include "../state.h"

void check_done(game_board *board) {
    for (int i = 0; i < board->width * board->height; i++) {
        game_board_cell *cell = &board->cells[i];
        if (!cell->opened && !cell->is_bomb) {
            return; // missed good cell(s), not done!
        }
    }
    board->status = Done; // no missing good cells, done
    flash();
}
