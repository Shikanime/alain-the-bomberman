#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "./env.h"

int8_t init_env_heros(t_env *env);
int8_t init_env_bombs(t_env *env);

t_env       *create_env()
{
    t_env   *env = malloc(sizeof(t_env));

    if (!env) {
        perror("Fail to create env");
        return (NULL);
    }
    if (init_env_heros(env) < 0) {
        destroy_env(env);
        return (NULL);
    }
    if (init_env_bombs(env) < 0) {
        destroy_env(env);
        return (NULL);
    }
    env->sz.width = 640;
    env->sz.height = 480;
    return (env);
}

int8_t init_env_heros(t_env *env)
{
    env->heros = calloc(0, sizeof(t_hero*));
    if (!env->heros) {
        perror("Fail to create env hero list");
        return (-1);
    }
    env->hero_nb = 0;
    return (0);
}

int8_t init_env_bombs(t_env *env)
{
    env->bombs = calloc(0, sizeof(t_bomb*));
    if (!env->bombs) {
        perror("Fail to create env bomb list");
        return (-1);
    }
    env->bomb_nb = 0;
    return (0);
}

void destroy_env(t_env *env)
{
    if (env) {
        if (env->heros) {
            for (size_t i = 0; i < env->hero_nb; i++) {
                free(env->heros[i]);
            }
        }
        if (env->bombs) {
            for (size_t i = 0; i < env->bomb_nb; i++) {
                free(env->bombs[i]);
            }
        }
        free(env);
    }
}
