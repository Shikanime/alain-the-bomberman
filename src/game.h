#pragma once

#include "./net.h"
#include "./game/env.h"
#include "./model/entity/hero.h"

typedef enum {
    GAME_FLOW_EXIT,
    GAME_FLOW_RUN,
    GAME_FLOW_MENU,
    GAME_FLOW_SKIP
}   e_game_flow;

typedef struct  s_game
{
    t_socket    *client;
    t_hero      *player;
    t_env       *env;
}               t_game;

t_game  *create_game();
void    destroy_game(t_game *game);
