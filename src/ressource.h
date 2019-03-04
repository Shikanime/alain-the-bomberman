#pragma once

#include <SDL2/SDL.h>

typedef struct  s_ressource
{
  SDL_Texture   *bomb;
}               t_ressource;

t_ressource *create_ressource();
void        destroy_ressource(t_ressource *ressource);
