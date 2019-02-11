#pragma once

#include "../physic/position.h"
#include "../physic/solid.h"

typedef struct      s_button
{
    t_position      *position;
    t_rect          *body;
    const char      *text;
}                   t_button;

t_button    *create_button(int x, int y, size_t width, size_t height, const char *text);
void        destroy_button(t_button *button);
