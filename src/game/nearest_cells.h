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

#ifndef GAME_NEAREST_CELLS_H
#define GAME_NEAREST_CELLS_H

#include <stdint.h>
#include "../state.h"

int16_t *list_nearby_cells(game_board *board, uint16_t cell);
void recursively_open_nearby_cells(game_board *board, uint16_t cell);

#endif
