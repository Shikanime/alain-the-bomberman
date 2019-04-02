#include <SDL2/SDL_ttf.h>
#include "./button.h"

int load_button(t_ressource *ressource)
{
    ressource->font = TTF_OpenFont("assets/abel-regular.ttf", 62);
    if (ressource->font == NULL) {
        return (-1);
    }
    return (0);
}

void            render_button(SDL_Renderer *renderer, TTF_Font *font, const char *text, size_t width, size_t height, int x, int y, bool light)
{
    SDL_Rect    rectangle = {x, y, (int)width, (int)height};
    SDL_Color   white = {255, 255, 255, 0};

    if (light) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderDrawRect(renderer, &rectangle);
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderCopy(renderer, SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Solid(font, text, white)), NULL, &rectangle);
}
