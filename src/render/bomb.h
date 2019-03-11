#pragma once

#include <stdlib.h>
#include <SDL2/SDL.h>

SDL_Texture *load_bomb(SDL_Renderer *renderer);
void        render_bomb(SDL_Renderer *renderer, SDL_Texture *texture, size_t x, size_t y);
