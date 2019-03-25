#pragma once

#include <SDL2/SDL.h>

typedef struct  s_ressource
{
  SDL_Texture   *bomb;
  SDL_Texture   **bomberman;
}               t_ressource;

t_ressource *create_ressource();
void        destroy_ressource(t_ressource *ressource);
SDL_Texture *load_image(SDL_Renderer *renderer, const char *path);
