#pragma once

#include <stdbool.h>
#include "../game/map.h"
#include "../game/bomb.h"

bool bomb_have_been_plant(t_map *map, t_bomb *bomb, int x, int y);
bool bomb_explosion(t_map *map, t_bomb *bomb, int x, int y);
