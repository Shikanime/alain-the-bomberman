#include <stdlib.h>
#include <stdio.h>
#include "./solid.h"

t_rect      *create_rect(size_t width, size_t height)
{
    t_rect  *rect = malloc(sizeof(t_rect));

    if (!rect) {
        perror("Fail to allocate rect");
        return (NULL);
    }
    rect->width = width;
    rect->height = height;
    return (rect);
}

void destroy_rect(t_rect *rect)
{
    if (rect) {
        free(rect);
    }
}
