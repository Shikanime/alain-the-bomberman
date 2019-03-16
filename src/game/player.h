#pragma once

#include <stdlib.h>

typedef struct  s_player
{
    int         x;
    int         y;
}               t_player;

t_player    *create_player(int x, int y);
void        destroy_player(t_player *player);
