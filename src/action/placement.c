#include <stdio.h>
#include <stdbool.h>
#include "./placement.h"

void place_hero(t_env *env, t_hero *hero)
{
    env->heros = realloc(env->heros, sizeof(t_hero*) * ++env->hero_nb);
    env->heros[env->hero_nb - 1] = hero;
}

int        place_bomb(t_env *env, t_bomb *bomb)
{
    bool    available = true;

    for (size_t i = 0; i < env->bomb_nb; i++) {
        if (env->bombs[i]->position->x == bomb->position->x &&
            env->bombs[i]->position->y == bomb->position->y) {
            available = false;
        }
    }
    if (available) {
        env->bombs = realloc(env->bombs, sizeof(t_bomb*) * ++env->bomb_nb);
        env->bombs[env->bomb_nb - 1] = bomb;
        return (1);
    }
    return (-1);
}
