#pragma once

#include <stdlib.h>

typedef struct      s_button
{
    size_t          width;
    size_t          height;
    int             x;
    int             y;
    const char      *text;
}                   t_button;

t_button    *create_button(int x, int y, size_t width, size_t height, const char *text);
void        destroy_button(t_button *button);
