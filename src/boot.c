#include "./boot.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <time.h>

const Uint32 SDL_CONFIG = SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER;

int init_subsystem()
{
    if (SDL_Init(SDL_CONFIG) < 0) {
        fprintf(stderr, "Could not initialize sdl2: %s\n", SDL_GetError());
        return (-1);
    }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        fprintf(stderr, "Could not initialize sdl2_image: %s\n", IMG_GetError());
        return (-1);
    }
    srand((unsigned int)time(NULL));
    return (1);
}

void quit_subsystem()
{
    SDL_Quit();
    IMG_Quit();
}
