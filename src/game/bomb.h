#pragma once

#include <stdlib.h>
#include <SDL2/SDL.h>

#define BOMB_BASIC_TIME 2000
#define BLAST_TIME 500

typedef enum {
    BOMB_BASIC_TYPE
}   e_bomb_type;

typedef struct  s_bomb
{
    e_bomb_type type;
    Uint32      drop_time;
}               t_bomb;

t_bomb  *create_bomb(e_bomb_type type, Uint32 drop_time);
void    destroy_bomb(t_bomb *bomb);
