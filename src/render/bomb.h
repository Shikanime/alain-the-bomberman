#pragma once

#include <SDL2/SDL.h>
#include "../model/entity/bomb.h"

SDL_Texture *load_bomb(SDL_Renderer *renderer);
void        render_bomb(SDL_Renderer *renderer, SDL_Texture *texture, t_bomb *bomb);
