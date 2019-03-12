#pragma once

#include <stdlib.h>

typedef enum {
    BOMB_BASIC_TYPE
}   e_bomb_type;

typedef struct  s_bomb
{
    e_bomb_type type;
}               t_bomb;

t_bomb  *create_bomb(e_bomb_type type);
void    destroy_bomb(t_bomb *bomb);
