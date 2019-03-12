#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <errno.h>
#include <stdio.h>
#include "./bomb.h"

SDL_Texture   *load_map(SDL_Renderer *renderer)
{
    SDL_Surface *img = NULL;
    SDL_Texture *texture = NULL;

    img = IMG_Load("assets/bomb.png");
    if (!img) {
        fprintf(stderr, "Image fail to load: %s", strerror(errno));
    }
    texture = SDL_CreateTextureFromSurface(renderer, img);
    if (!texture) {
        fprintf(stderr, "Image fail to load: %s", strerror(errno));
    }
    SDL_FreeSurface(img);
    return texture;
}

void            render_ground(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y)
{
    SDL_Rect    rectangle = {x, y, 20, 20};

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &rectangle);
}
