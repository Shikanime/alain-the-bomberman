#pragma once

#include <stdbool.h>
#include "../game/bomb.h"
#include "../game/bomberman.h"
#include "../game/map.h"

bool place_bomb(t_map *map, t_bomb *bomb, int x, int y);
bool place_bomberman(t_map *map, t_bomberman *bomberman, int x, int y);
