#include <errno.h>
#include <stdio.h>
#include "./bomb.h"

int load_bomb(SDL_Renderer *renderer, t_ressource *ressource)
{
    ressource->bomb = load_image(renderer, "assets/bomb.png");
    if (ressource->bomberman == NULL) {
        return (-1);
    }
    return (0);
}

void            render_bomb(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y)
{
    SDL_Rect    rectangle = {x * FIXED_BOMB_WIDTH, y * FIXED_BOMB_HEIGHT,
                             FIXED_BOMB_WIDTH, FIXED_BOMB_HEIGHT};

    SDL_RenderCopy(renderer, texture, NULL, &rectangle);
}
