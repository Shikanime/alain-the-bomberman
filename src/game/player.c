#include <stdio.h>
#include "./player.h"

t_player        *create_player(size_t width, size_t height)
{
    t_player    *player = malloc(sizeof(t_player));

    if (player == NULL) {
        perror("Fail to allocate player");
        return (NULL);
    }
    player->x = rand() % width;
    player->y = rand() % height;
    return (player);
}

void destroy_player(t_player *player)
{
    if (player != NULL) {
        free(player);
        player = NULL;
    }
}
