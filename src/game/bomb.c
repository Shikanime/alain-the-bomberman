#include <stdlib.h>
#include <stdio.h>
#include "./bomb.h"

t_bomb      *create_bomb(e_bomb_type type)
{
    t_bomb  *bomb = malloc(sizeof(t_bomb));

    if (bomb == NULL) {
        perror("Fail to allocate bomb");
        return (NULL);
    }
    bomb->type = type;
    return (bomb);
}

void destroy_bomb(t_bomb *bomb)
{
    if (bomb != NULL) {
        free(bomb);
        bomb = NULL;
    }
}
