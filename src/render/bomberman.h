#pragma once

#include <stdlib.h>
#include <SDL2/SDL.h>

#define FIXED_BOMBERMAN_WIDTH 20
#define FIXED_BOMBERMAN_HEIGHT 20

void render_bomberman(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y);
