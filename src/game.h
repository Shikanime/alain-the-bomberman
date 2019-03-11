#pragma once

#include <stdlib.h>
#include "./net/conn.h"
#include "./game/map.h"
#include "./game/bomberman.h"

typedef enum {
    GAME_EXIT,
    GAME_RUN,
    GAME_PAUSE,
    GAME_SKIP
}   e_game_state;

typedef struct      s_game
{
    e_game_state    state;
    t_conn        *server;
    t_map           *map;
    size_t          player_x;
    size_t          player_y;
}                   t_game;

t_game  *create_game(t_map *map, size_t player_x, size_t player_y);
void    destroy_game(t_game *game);
