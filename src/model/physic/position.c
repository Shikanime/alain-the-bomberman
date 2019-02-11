#include <stdlib.h>
#include <stdio.h>
#include "./position.h"

t_position      *create_position(int x, int y)
{
    t_position  *pos = malloc(sizeof(t_position));

    if (pos) {
        pos->x = x;
        pos->y = y;
    } else {
        perror("Fail to create position");
    }
    return (pos);
}

void destroy_position(t_position *pos)
{
    if (pos) {
        free(pos);
    }
}
