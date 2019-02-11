#include "./bomb.h"

void render_bomb(SDL_Renderer *renderer, t_bomb *bomb)
{
    SDL_Rect rectangle = {bomb->position->x,
                          bomb->position->y,
                          (int)bomb->body->width,
                          (int)bomb->body->height};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &rectangle);
}
