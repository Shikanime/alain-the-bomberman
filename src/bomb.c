#include <stdlib.h>
#include <stdio.h>
#include "./bomb.h"

t_bomb *create_bomb(int time)
{
    t_bomb *bomb = (t_bomb*) malloc(sizeof(t_bomb));

    if (!bomb) {
        perror("Allocation failure");
        return (NULL);
    }
    bomb->time = time;
    return bomb;
}

void destroy_bomb(t_bomb *bomb)
{
    if (bomb != NULL) {
        free(bomb);
    }
}
