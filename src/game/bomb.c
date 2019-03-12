#include <stdlib.h>
#include <stdio.h>
#include "./bomb.h"

t_bomb      *create_bomb(e_bomb_type type, Uint32 drop_time)
{
    t_bomb  *bomb = malloc(sizeof(t_bomb));

    if (bomb == NULL) {
        perror("Fail to allocate bomb");
        return (NULL);
    }
    bomb->type = type;
    bomb->drop_time = drop_time;
    return (bomb);
}

void destroy_bomb(t_bomb *bomb)
{
    if (bomb != NULL) {
        free(bomb);
    }
}
