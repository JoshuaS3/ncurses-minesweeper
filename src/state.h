#ifndef STATE_H
#define STATE_H

#include "stdint.h"

typedef enum DrawPage { Title } DrawPage;
typedef enum GameStatus { Playing, Done, Kaboom } GameStatus;

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
    GameStatus status;
    game_board_cell *cells; // heap allocated, size = width * height, position in array determines position on board
} game_board;

typedef struct game_state {
    DrawPage page;
    uint8_t page_selection; // character/token that determines what part of the screen (button/input) is selected
    game_board *board;
} game_state;

#endif
