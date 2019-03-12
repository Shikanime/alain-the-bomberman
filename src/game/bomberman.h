#pragma once

#include <stdlib.h>

typedef enum {
    BOMBERNMAN_BASIC
}   e_bomberman_skin;


typedef struct          s_bomberman
{
    e_bomberman_skin    skin;
    unsigned int        speed;
}                       t_bomberman;

t_bomberman *create_bomberman();
void        destroy_bomberman(t_bomberman *bomberman);
