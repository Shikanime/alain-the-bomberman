#pragma once

#include <stdlib.h>
#include <SDL2/SDL.h>

#define BOMB_PROVISIONNING 3000

typedef enum {
    BOMBERNMAN_WHITE,
    BOMBERNMAN_RED,
    BOMBERNMAN_BLUE,
    BOMBERNMAN_GREY
}   e_bomberman_skin;


typedef struct          s_bomberman
{
    e_bomberman_skin    skin;
    unsigned int        speed;
    Uint32              bomb_nb;
    size_t              bomb_capacity;
    Uint32              bomb_supply_time;
}                       t_bomberman;

t_bomberman *create_bomberman(e_bomberman_skin skin);
void        destroy_bomberman(t_bomberman *bomberman);
