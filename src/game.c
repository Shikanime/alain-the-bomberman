#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "./game.h"
#include "./net.h"
#include "./model/entity/hero.h"
#include "./action/placement.h"
#include "./game/env.h"

t_game      *create_game()
{
    t_game  *game = malloc(sizeof(t_game));

    if (game) {
        game->client = create_socket();
        if (!game->client) {
            destroy_game(game);
            return (NULL);
        }
        game->player = create_hero(40, 40);
        if (!game->player) {
            destroy_game(game);
            return (NULL);
        }
        game->env = create_env();
        if (!game->env) {
            destroy_game(game);
            return (NULL);
        }
    }
    return (game);
}

void destroy_game(t_game *game)
{
    if (!game) {
        if (game->env) {
            destroy_env(game->env);
        }
        if (game->client) {
            destroy_socket(game->client);
        }
        free(game);
    }
}

int         init_game(t_game *game)
{
    char    packet[MESSAGE_LENGTH];

    place_hero(game->env, game->player);
    sprintf(packet, "spawn %02d %02d", game->player->position->x, game->player->position->y);
    send_event(game->client, packet);
    return (0);
}
