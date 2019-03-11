#pragma once

#include <stdbool.h>
#include "../game/map.h"
#include "../game/player.h"

bool move_bomberman_up(t_map *map, t_player *player);
bool move_bomberman_down(t_map *map, t_player *player);
bool move_bomberman_left(t_map *map, t_player *player);
bool move_bomberman_right(t_map *map, t_player *player);
