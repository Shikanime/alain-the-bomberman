#pragma once

#include <stdlib.h>

typedef enum {
    BOMBERNMAN_WHITE,
    BOMBERNMAN_RED,
    BOMBERNMAN_BLUE,
    BOMBERNMAN_GREY
}   e_bomberman_skin;


typedef struct          s_bomberman
{
    e_bomberman_skin    skin;
    unsigned int        speed;
}                       t_bomberman;

t_bomberman *create_bomberman(e_bomberman_skin skin);
void        destroy_bomberman(t_bomberman *bomberman);
