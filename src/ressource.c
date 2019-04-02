#include <SDL2/SDL_image.h>
#include "./ressource.h"
#include "./render/bomb.h"
#include "./render/bomberman.h"
#include "./render/button.h"
#include "./render/env.h"

t_ressource     *create_ressource(SDL_Renderer *renderer)
{
    t_ressource *ressource = malloc(sizeof(t_ressource));

    if (!ressource) {
        destroy_ressource(ressource);
        return (NULL);
    }
    load_bomb(renderer, ressource);
    load_bomberman(renderer, ressource);
    load_env(renderer, ressource);
    load_button(ressource);
    return (ressource);
}

void destroy_ressource(t_ressource *ressource)
{
  if (ressource) {
    free(ressource);
  }
}

SDL_Texture *load_image(SDL_Renderer *renderer, const char *path)
{
    SDL_Surface *img = NULL;
    SDL_Texture *texture = NULL;

    img = IMG_Load(path);
    if (!img) {
        return NULL;
    }
    texture = SDL_CreateTextureFromSurface(renderer, img);
    if (!texture) {
        return NULL;
    }
    SDL_FreeSurface(img);
    return texture;
}
