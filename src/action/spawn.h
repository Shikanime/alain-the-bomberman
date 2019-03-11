#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include "../game/bomb.h"
#include "../game/bomberman.h"
#include "../game/map.h"

bool spawn_bomberman(t_map *map, t_bomberman *bomberman, int x, int y);
