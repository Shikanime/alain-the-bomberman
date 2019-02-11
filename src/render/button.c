#include "./button.h"

void render_button(SDL_Renderer *renderer, t_button *button)
{
    SDL_Rect rectangle = {button->position->x,
                          button->position->y,
                          (int)button->body->width,
                          (int)button->body->height};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &rectangle);
}
