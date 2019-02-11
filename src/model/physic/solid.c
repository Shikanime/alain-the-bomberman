#include <stdlib.h>
#include <stdio.h>
#include "./solid.h"

t_rect      *create_rect(size_t width, size_t height)
{
    t_rect  *rect = malloc(sizeof(t_rect));

    if (rect) {
        rect->width = width;
        rect->height = height;
    } else {
        perror("Fail to create rect");
    }
    return (rect);
}

void destroy_rect(t_rect *rect)
{
    if (rect) {
        free(rect);
    }
}
