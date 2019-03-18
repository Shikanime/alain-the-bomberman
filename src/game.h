#pragma once

#include <stdlib.h>
#include "./net/conn.h"
#include "./game/map.h"
#include "./game/bomberman.h"
#include "./game/player.h"

typedef enum {
    GAME_EXIT,
    GAME_INIT,
    GAME_RUN,
    GAME_PAUSE,
    GAME_SKIP,
    GAME_MENU,
    GAME_OVER
}   e_game_state;

typedef struct      s_game
{
    e_game_state    state;
    t_conn          *server;
    t_map           *map;
    t_player        *player;
}                   t_game;

t_game  *create_game(size_t width, size_t height);
void    destroy_game(t_game *game);
