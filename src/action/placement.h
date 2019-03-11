#pragma once

#include <stdbool.h>
#include "../game/bomb.h"
#include "../game/bomberman.h"
#include "../game/map.h"

bool place_bomb(t_map *map, t_bomb *bomb, size_t x, size_t y);
bool place_bomberman(t_map *map, t_bomberman *bomberman, size_t x, size_t y);
