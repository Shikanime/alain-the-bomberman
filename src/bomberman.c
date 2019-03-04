#include <stdlib.h>
#include <stdio.h>
#include "./bomberman.h"

t_bomberman *create_bomberman(int healt)
{
    t_bomberman *bomberman = (t_bomberman*) malloc(sizeof(t_bomberman));

    if (!bomberman) {
        perror("Allocation failure");
        return (NULL);
    }
    bomberman->healt = healt;
    return bomberman;
}

void destroy_bomberman(t_bomberman *bomberman)
{
    if (bomberman != NULL) {
        free(bomberman);
    }
}
