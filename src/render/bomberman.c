#include "./bomberman.h"

void            render_bomberman(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y)
{
    SDL_Rect    rectangle = {x * FIXED_BOMBERMAN_WIDTH, y * FIXED_BOMBERMAN_HEIGHT,
                             FIXED_BOMBERMAN_WIDTH, FIXED_BOMBERMAN_HEIGHT};

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(renderer, &rectangle);
}
