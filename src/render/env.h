#pragma once

#include <stdlib.h>
#include <SDL2/SDL.h>

#define FIXED_ENV_WIDTH 20
#define FIXED_ENV_HEIGHT 20

SDL_Texture *load_map(SDL_Renderer *renderer);
void        render_ground(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y);
void        render_wall(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y);
