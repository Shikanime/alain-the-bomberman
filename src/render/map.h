#pragma once

#include <stdlib.h>
#include <SDL2/SDL.h>

SDL_Texture *load_map(SDL_Renderer *renderer);
void        render_ground(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y);
