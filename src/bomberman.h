#pragma once

typedef struct  s_bomberman
{
    int         healt;
}               t_bomberman;

t_bomberman *create_bomberman(int healt);
void        destroy_bomberman(t_bomberman *bomberman);
