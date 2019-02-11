#pragma once

#include "../physic/position.h"
#include "../physic/solid.h"

typedef struct      s_hero
{
    t_position      *position;
    t_rect          *body;
    unsigned int    speed;
}                   t_hero;

t_hero  *create_hero(int x, int y);
void    destroy_hero(t_hero *hero);
