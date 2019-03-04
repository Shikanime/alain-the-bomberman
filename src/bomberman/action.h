#pragma once

#include <stdbool.h>
#include "../game.h"
#include "../bomberman.h"

bool bomberman_move_up(t_game *game, int x, int y);
bool bomberman_move_down(t_game *game, int x, int y);
bool bomberman_move_right(t_game *game, int x, int y);
bool bomberman_move_left(t_game *game, int x, int y);
