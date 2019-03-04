#pragma once

#include <SDL2/SDL.h>
#include "../bomb.h"

int     init_bomb(SDL_Renderer *renderer);
void    render_bomb(SDL_Renderer *renderer, int x, int y);
