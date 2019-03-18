#include <stdlib.h>
#include <stdio.h>
#include "./game.h"
#include "./net.h"
#include "./system/bomberman.h"

t_game      *create_game(size_t width, size_t height)
{
    t_game  *game = malloc(sizeof(t_game));

    if (game == NULL) {
        perror("Fail to allocate game");
        return (NULL);
    }
    game->state = GAME_INIT;
    game->map = create_map(width, height);
    game->player = create_player(width / 2, height / 2);
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
