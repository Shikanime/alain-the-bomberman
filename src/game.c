#include <stdlib.h>
#include <stdio.h>
#include "./game.h"
#include "./net.h"
#include "./action/placement.h"

t_game      *create_game()
{
    t_game  *game = malloc(sizeof(t_game));

    if (game == NULL) {
        perror("Fail to allocate game");
        return (NULL);
    }
    game->state = GAME_RUN;
    game->map = create_map(16, 12);
    game->player = create_player(16, 12);
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

int         sync_player(t_game *game, char *address, uint16_t port)
{
    char    packet[20];

    if (conn_client_mode(game->server, address, port) < 0) {
        return (-1);
    }
    place_bomberman(game->map, create_bomberman(), game->player->x, game->player->y);
    sprintf(packet, "spawn %02d %02d", game->player->x, game->player->y);
    send_event(game->server, packet);
    return (1);
}
