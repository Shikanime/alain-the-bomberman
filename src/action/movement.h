#pragma once

#include <stdbool.h>
#include "../game/bomberman.h"
#include "../game/map.h"

bool move_bomberman_up(t_map *map, size_t x, size_t y);
bool move_bomberman_down(t_map *map, size_t x, size_t y);
bool move_bomberman_left(t_map *map, size_t x, size_t y);
bool move_bomberman_right(t_map *map, size_t x, size_t y);
