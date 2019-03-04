#include <stdlib.h>
#include <stdio.h>
#include "./bomb.h"

t_bomb      *create_bomb(int x, int y)
{
    t_bomb  *bomb = malloc(sizeof(t_bomb));

    if (!bomb) {
        perror("Fail to create bomb");
        return (NULL);
    }
    bomb->position = create_position(x, y);
    if (!bomb->position) {
        destroy_bomb(bomb);
        return (NULL);
    }
    bomb->body = create_rect(BOMB_WIDTH ,BOMB_HEIGHT);
    if (!bomb->body) {
        destroy_bomb(bomb);
        return (NULL);
    }
    return (bomb);
}

void destroy_bomb(t_bomb *bomb)
{
    if (bomb) {
        if (bomb->position) {
            destroy_position(bomb->position);
        }
        if (bomb->body) {
            destroy_rect(bomb->body);
        }
        free(bomb);
    }
}
