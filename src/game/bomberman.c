#include <stdlib.h>
#include <stdio.h>
#include "./bomberman.h"

t_bomberman     *create_bomberman(e_bomberman_skin skin)
{
    t_bomberman *bomberman = malloc(sizeof(t_bomberman));

    if (bomberman == NULL) {
        perror("Fail to allocate bomberman");
        return (NULL);
    }
    bomberman->skin = skin;
    bomberman->speed = 20;
    bomberman->bomb_nb = 5;
    bomberman->bomb_capacity = 10;
    bomberman->bomb_supply_time = SDL_GetTicks();
    return (bomberman);
}

void destroy_bomberman(t_bomberman *bomberman)
{
    if (bomberman != NULL) {
        free(bomberman);
    }
}
