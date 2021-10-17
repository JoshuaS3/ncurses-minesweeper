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

#ifndef DRAW_PAGES_H
#define DRAW_PAGES_H

#include "../state.h"

int draw_title_screen(game_state *state, int ch);
int draw_game(game_state *state, int ch);
int draw_options_screen(game_state *state, int ch);
int draw_help_screen(game_state *state, int ch);
int draw_about_screen(game_state *state, int ch);

#endif
