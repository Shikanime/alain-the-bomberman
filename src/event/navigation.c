#include "./navigation.h"

void handle_navigation_events(t_game *game)
{
    if (game->state == GAME_OVER) {
        game->state = GAME_EXIT;
    }
}
