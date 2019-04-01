#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <errno.h>
#include <stdio.h>
#include "../game/map.h"
#include "./bomb.h"
#include "./env.h"

int load_env(SDL_Renderer *renderer, t_ressource *ressource)
{
    ressource->env = calloc(3, sizeof(SDL_Texture*));
    ressource->env[ENV_GROUND] = load_image(renderer, "assets/dirt.png");
    if (ressource->env[ENV_GROUND] == NULL) {
        return (-1);
    }
    ressource->env[ENV_WALL] = load_image(renderer, "assets/wall.png");
    if (ressource->env[ENV_WALL] == NULL) {
        return (-1);
    }
    ressource->env[ENV_FIRE] = load_image(renderer, "assets/fire.png");
    if (ressource->env[ENV_FIRE] == NULL) {
        return (-1);
    }
    return (0);
}

void            render_env(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y)
{
    SDL_Rect    rectangle = {x * FIXED_ENV_WIDTH, y * FIXED_ENV_HEIGHT,
                             FIXED_ENV_WIDTH, FIXED_ENV_HEIGHT};

    SDL_RenderCopy(renderer, texture, NULL, &rectangle);
}
