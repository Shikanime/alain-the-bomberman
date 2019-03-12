#pragma once

#include "../game/map.h"

int compute_bomberman_up_move(t_map *map, int y);
int compute_bomberman_down_move(t_map *map, int y);
int compute_bomberman_left_move(t_map *map, int x);
int compute_bomberman_right_move(t_map *map, int x);
