#include <errno.h>
#include "../game/bomberman.h"
#include "./bomberman.h"

int load_bomberman(SDL_Renderer *renderer, t_ressource *ressource)
{
    ressource->bomberman = calloc(4, sizeof(SDL_Texture*));
    ressource->bomberman[BOMBERNMAN_WHITE] = load_image(renderer, "assets/bomberman_white.png");
    if (ressource->bomberman[BOMBERNMAN_WHITE] == NULL) {
        return (-1);
    }
    ressource->bomberman[BOMBERNMAN_RED] = load_image(renderer, "assets/bomberman_red.png");
    if (ressource->bomberman[BOMBERNMAN_RED] == NULL) {
        return (-1);
    }
    ressource->bomberman[BOMBERNMAN_GREY] = load_image(renderer, "assets/bomberman_grey.png");
    if (ressource->bomberman[BOMBERNMAN_GREY] == NULL) {
        return (-1);
    }
    ressource->bomberman[BOMBERNMAN_BLUE] = load_image(renderer, "assets/bomberman_blue.png");
    if (ressource->bomberman[BOMBERNMAN_BLUE] == NULL) {
        return (-1);
    }
    return (0);
}

void            render_bomberman(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y)
{
    SDL_Rect    rectangle = {x * FIXED_BOMBERMAN_WIDTH, y * FIXED_BOMBERMAN_HEIGHT,
                             FIXED_BOMBERMAN_WIDTH, FIXED_BOMBERMAN_HEIGHT};

    SDL_RenderCopy(renderer, texture, NULL, &rectangle);
}
