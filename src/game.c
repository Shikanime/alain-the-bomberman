#include <stdlib.h>
#include <stdio.h>
#include "./game.h"
#include "./net.h"
#include "./action/placement.h"

t_game      *create_game(t_map *map, size_t player_x, size_t player_y)
{
    char    packet[20];
    t_game  *game = malloc(sizeof(t_game));

    if (game == NULL) {
        perror("Fail to allocate game");
        return (NULL);
    }
    game->state = GAME_RUN;
    game->map = map;
    game->player_x = player_x;
    game->player_y = player_y;
    place_bomberman(map, create_bomberman(), player_x, player_y);
    sprintf(packet, "spawn %02zu %02zu", player_x, player_y);
    send_event(game->server, packet);
    return game;
}

void destroy_game(t_game *game)
{
    if (game != NULL) {
        destroy_map(game->map);
        free(game);
    }
}
