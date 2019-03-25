#pragma once

#include <stdlib.h>
#include <SDL2/SDL.h>

#define FIXED_ENV_WIDTH 20
#define FIXED_ENV_HEIGHT 20

int load_env(SDL_Renderer *renderer, t_ressource *ressource);
void render_env(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y);
