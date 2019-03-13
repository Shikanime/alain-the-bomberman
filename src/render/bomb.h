#pragma once

#include <stdlib.h>
#include <SDL2/SDL.h>

#define FIXED_BOMB_WIDTH 20
#define FIXED_BOMB_HEIGHT 20

SDL_Texture *load_bomb(SDL_Renderer *renderer);
void        render_bomb(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y);
