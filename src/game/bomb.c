#include <stdlib.h>
#include <stdio.h>
#include "./bomb.h"

t_bomb      *create_bomb()
{
    t_bomb  *bomb = malloc(sizeof(t_bomb));

    if (bomb == NULL) {
        perror("Fail to allocate bomb");
        return (NULL);
    }
    return (bomb);
}

void destroy_bomb(t_bomb *bomb)
{
    if (bomb != NULL) {
        free(bomb);
        bomb = NULL;
    }
}
