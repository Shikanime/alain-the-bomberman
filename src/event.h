#pragma once

#include <SDL2/SDL.h>
#include "./game.h"

void sub_events(t_game *game);
void sub_inputs(e_game_flow *state, t_game *game);
