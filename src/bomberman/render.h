#pragma once

#include <SDL2/SDL.h>
#include "../bomberman.h"

int     init_bomberman(SDL_Renderer *renderer);
void    render_bomberman(SDL_Renderer *renderer, int x, int y);
