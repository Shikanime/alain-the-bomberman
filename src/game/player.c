#include <stdio.h>
#include "./player.h"

t_player        *create_player(int x, int y)
{
    t_player    *player = malloc(sizeof(t_player));

    if (player == NULL) {
        perror("Fail to allocate player");
        return (NULL);
    }
    player->x = x;
    player->y = y;
    return (player);
}

void destroy_player(t_player *player)
{
    if (player != NULL) {
        free(player);
    }
}
