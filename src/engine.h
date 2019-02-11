#pragma once

#include <SDL2/SDL.h>

typedef struct      s_engine
{
    SDL_Window      *window;
}                   t_engine;

t_engine    *create_engine();
void        destroy_engine(t_engine *d);
