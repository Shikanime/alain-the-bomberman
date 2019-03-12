#pragma once

#include <stdbool.h>
#include "../game/map.h"
#include "../game/bomb.h"

bool place_bomb(t_map *map, t_bomb *bomb, int x, int y);
