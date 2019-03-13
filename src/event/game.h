#pragma once

#include <SDL2/SDL.h>
#include "../game.h"

void handle_game_inputs(SDL_Event *event, t_game *game);
void handle_game_internal_events(t_game *game);
void handle_game_server_events(t_game *game, char *packet);
