#pragma once

#include "../physic/solid.h"
#include "../physic/position.h"

#define BOMB_WIDTH 10
#define BOMB_HEIGHT 10

typedef struct  s_bomb
{
    t_position  *position;
    t_rect      *body;
}               t_bomb;

t_bomb  *create_bomb(int x, int y);
void    destroy_bomb(t_bomb *bomb);
