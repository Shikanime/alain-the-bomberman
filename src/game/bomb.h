#pragma once

typedef struct  s_bomb
{
    size_t      width;
    size_t      height;
}               t_bomb;

t_bomb  *create_bomb();
void    destroy_bomb(t_bomb *bomb);
