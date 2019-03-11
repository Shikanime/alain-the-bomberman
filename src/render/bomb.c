#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <errno.h>
#include <stdio.h>
#include "./bomb.h"

SDL_Texture   *load_bomb(SDL_Renderer *renderer)
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

void        render_bomb(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y)
{
  SDL_Rect  dest = {x, y, 40, 40};

  SDL_RenderCopy(renderer, texture, NULL, &dest);
  SDL_RenderDrawRect(renderer, &dest);
}
