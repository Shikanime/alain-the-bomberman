#pragma once

#include <stdlib.h>

typedef struct  s_player
{
    int         x;
    int         y;
}               t_player;

t_player    *create_player(size_t width, size_t height);
void        destroy_player(t_player *player);
