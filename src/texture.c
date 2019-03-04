#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "./texture.h"

SDL_Texture *load_texture(SDL_Renderer *renderer, const char *path)
{
	//The final texture
	SDL_Texture *optimized_texture = NULL;
	//Load image at specified path
	SDL_Surface *image_surface = NULL;

    image_surface = IMG_Load(path);
	if (image_surface == NULL) {
		fprintf(stderr, "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
        return (NULL);
	}
    //Create texture from surface pixels
    optimized_texture = SDL_CreateTextureFromSurface(renderer, image_surface);
    if (optimized_texture == NULL) {
        fprintf(stderr, "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError() );
        return (NULL);
    }
    //Get rid of old loaded surface
    SDL_FreeSurface(image_surface);
	return optimized_texture;
}
