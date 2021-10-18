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

#ifndef STATE_H
#define STATE_H

#include <stdint.h>
#include <time.h>

typedef enum DrawPage { Title, Game, Options, Help, About } DrawPage;
typedef enum GameStatus { Waiting, Playing, Done, Kaboom } GameStatus;

typedef struct game_board_cell {
    uint8_t is_bomb : 1;
    uint8_t flagged : 1;
    uint8_t opened : 1;
    uint8_t surrounding_bomb_count : 3; // maximum possible is 8, only need 3 bits
} game_board_cell;

typedef struct game_board {
    uint8_t width;
    uint8_t height;
    uint16_t current_cell; // (x,y) | x = current_cell % width, y = current_cell / width
    uint8_t mine_count;
    uint8_t mines_left;
    uint64_t time;
    GameStatus status;
    game_board_cell *cells; // heap allocated, size = width * height, position in array determines position on board
} game_board;

typedef struct game_state {
    DrawPage page;
    DrawPage last_page;
    uint8_t page_selection; // character/token that determines what part of the screen (button/input) is selected
    game_board *board;
} game_state;

#endif
