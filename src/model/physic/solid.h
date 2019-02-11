#pragma once

#include <stdlib.h>

typedef struct  s_rect
{
    size_t     width;
    size_t     height;
}               t_rect;

t_rect  *create_rect(size_t width, size_t height);
void    destroy_rect(t_rect *rect);
