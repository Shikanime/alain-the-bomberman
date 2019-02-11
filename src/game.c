#include <stdlib.h>
#include <unistd.h>
#include "./game.h"
#include "./net.h"
#include "./model/entity/hero.h"
#include "./model/entity/env.h"

t_game      *create_game(const char *address, uint16_t port)
{
    t_game  *game = malloc(sizeof(t_game));

    if (game) {
        game->client = create_client_socket(address, port);
        if (!game->client) {
            destroy_game(game);
            return (game);
        }
        game->player = create_hero(0, 0);
        if (!game->player) {
            destroy_game(game);
            return (game);
        }
        game->env = create_env();
        if (!game->env) {
            destroy_game(game);
            return (game);
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
