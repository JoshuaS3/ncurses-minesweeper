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

#ifndef GAME_CONSTRAIN_MOVEMENT_H
#define GAME_CONSTRAIN_MOVEMENT_H

#include "../state.h"

void constrain_up(game_board *board);
void constrain_down(game_board *board);
void constrain_left(game_board *board);
void constrain_right(game_board *board);

#endif
