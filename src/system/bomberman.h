#pragma once

#include <stdbool.h>
#include "../game/map.h"
#include "../game/bomb.h"
#include "../game/bomberman.h"

bool allahu_akbar(t_map *map, t_bomb *bomb, int x, int y);
bool place_bomberman(t_map *map, t_bomberman *bomberman, int x, int y);
bool move_bomberman(t_map *map, int d_x, int d_y, int s_x, int s_y);
bool spawn_bomberman(t_map *map, t_bomberman *bomberman, int x, int y);
