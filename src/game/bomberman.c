#include <stdlib.h>
#include "./bomberman.h"

t_bomberman     *create_bomberman()
{
    t_bomberman *bomberman = malloc(sizeof(t_bomberman));

    if (bomberman == NULL) {
        perror("Fail to allocate bomberman");
        return (NULL);
    }
    bomberman->speed = 40;
    return (bomberman);
}

void destroy_bomberman(t_bomberman *bomberman)
{
    if (bomberman != NULL) {
        free(bomberman);
    }
}
