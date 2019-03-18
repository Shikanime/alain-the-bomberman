#include "./button.h"

void            render_button(SDL_Renderer *renderer, SDL_Texture *texture, size_t width, size_t height, int x, int y)
{
    SDL_Rect    rectangle = {x, y, (int)width, (int)height};

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &rectangle);
}
