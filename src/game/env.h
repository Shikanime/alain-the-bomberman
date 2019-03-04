#pragma once

#include "../model/entity/hero.h"
#include "../model/entity/bomb.h"

typedef struct  s_env
{
    t_rect      sz;
    t_hero      **heros;
    size_t      hero_nb;
    t_bomb      **bombs;
    size_t      bomb_nb;
}               t_env;

t_env   *create_env();
void    destroy_env(t_env *env);
