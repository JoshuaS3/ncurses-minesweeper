#ifndef GAME_NEAREST_CELLS_H
#define GAME_NEAREST_CELLS_H

#include <stdint.h>
#include "../state.h"

int16_t *list_nearby_cells(game_board *board, uint16_t cell);
void recursively_open_nearby_cells(game_board *board, uint16_t cell);

#endif
