#pragma once

typedef struct  s_bomb
{
    int         time;
}               t_bomb;

t_bomb  *create_bomb(int time);
void    destroy_bomb(t_bomb *bomb);
