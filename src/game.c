#include <stdlib.h>
#include <stdio.h>
#include "./game.h"
#include "./net.h"
#include "./system/bomberman.h"

t_game      *create_game(size_t width, size_t height)
{
    t_game  *game = malloc(sizeof(t_game));
    int     x = rand() % width;
    int     y = rand() % height;

    if (game == NULL) {
        perror("Fail to allocate game");
        return (NULL);
    }
    game->state = GAME_RUN;
    game->map = create_map(width, height);
    while (game->map->matrix[y][x].env != ENV_GROUND){
        y = rand() % height;
        x = rand() % width;
    }
    game->player = create_player(x, y);
    game->server = create_conn();
    return game;
}

void destroy_game(t_game *game)
{
    if (game != NULL) {
        destroy_map(game->map);
        destroy_conn(game->server);
        free(game);
    }
}

int         sync_player(t_game *game, const char *address, uint16_t port)
{
    char    packet[FIXED_PACKET_LENGHT];

    if (conn_client_mode(game->server, address, port) < 0) {
        return (-1);
    }
    place_bomberman(game->map, create_bomberman(), game->player->x, game->player->y);
    sprintf(packet, "spawn 1 %02d %02d", game->player->x, game->player->y);
    send_event(game->server, packet);
    return (1);
}
