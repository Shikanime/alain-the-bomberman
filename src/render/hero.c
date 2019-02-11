#include "./hero.h"

void            render_hero(SDL_Renderer *renderer, t_hero *hero)
{
    SDL_Rect    rectangle = {hero->position->x,
                             hero->position->y,
                             (int)hero->body->width,
                             (int)hero->body->height};
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderDrawRect(renderer, &rectangle);
}
