#pragma once

#include <SDL2/SDL.h>
#include "../game/game.h"

void handle_game_inputs(SDL_Event *event, t_game *game);
void handle_game_broadcasts(t_conn *s, int fd, char *packet);
