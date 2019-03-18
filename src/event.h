#pragma once

#include "./game.h"
#include "./game/map.h"

void sub_navigation_events(t_game *game);
void sub_input_events(t_game *game);
void sub_internal_events(t_game *game);
void sub_sever_events(t_game *game);
void sub_client_events(t_conn *s, t_map *map);
