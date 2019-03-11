#pragma once

typedef struct      s_bomberman
{
    size_t          width;
    size_t          height;
    unsigned int    speed;
}                   t_bomberman;

t_bomberman *create_bomberman();
void        destroy_bomberman(t_bomberman *bomberman);
