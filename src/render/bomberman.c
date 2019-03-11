#include "./bomberman.h"

void            render_bomberman(SDL_Renderer *renderer, SDL_Texture *texture, size_t x, size_t y)
{
    (void) texture;

    SDL_Rect    rectangle = {x, y, 40, 40};

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderDrawRect(renderer, &rectangle);
}
