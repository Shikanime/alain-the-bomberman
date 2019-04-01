#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include "./bomb.h"
#include "./bomberman.h"

typedef enum {
    JOIN_GAME,
    CREATE_GAME
}   e_nav_navigation;

typedef struct  s_nav
{
    int         cursor;
    bool        valided;
    size_t      size;
}               t_nav;

t_nav   *create_nav();
void    destroy_nav(t_nav *nav);
