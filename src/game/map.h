#pragma once

#include <stdlib.h>
#include "./bomb.h"
#include "./bomberman.h"

typedef enum {
    ENV_GROUND,
    ENV_WALL,
    ENV_FIRE
}   e_env_type;

typedef struct  s_cell
{
    t_bomberman *bomberman;
    t_bomb      *bomb;
    e_env_type  env;
}               t_cell;

typedef struct  s_map
{
    size_t      width;
    size_t      height;
    t_cell      **matrix;
}               t_map;

t_map   *create_map(size_t width, size_t height);
void    destroy_map(t_map *map);
