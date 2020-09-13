#ifndef DRAW_PAGES_H
#define DRAW_PAGES_H

#include "../state.h"

int draw_title_screen(game_state *state, int ch);
int draw_options_screen(game_state *state, int ch);
int draw_help_screen(game_state *state, int ch);

#endif
