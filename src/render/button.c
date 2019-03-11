#include "./button.h"

void            render_button(SDL_Renderer *renderer, SDL_Texture *texture, size_t x, size_t y)
{
    (void) texture;

    SDL_Rect    rectangle = {x, y, 200, 200};

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &rectangle);
}
