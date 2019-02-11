#pragma once

typedef struct  s_position
{
    int         x;
    int         y;
}               t_position;

t_position  *create_position(int x, int y);
void        destroy_position(t_position *position);
