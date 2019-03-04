#include "./render.h"
#include "../texture.h"

// Configuration
const char  *BOMBERMAN_TEXTURE_PATH  = "assets/bomberman.png";
const int   BOMBERMAN_BODY_WIDTH     = 40;
const int   BOMBERMAN_BODY_HEIGHT    = 40;

// Texture singleton
SDL_Texture *g_bomberman_texture = NULL;

int init_bomberman(SDL_Renderer *renderer)
{
	g_bomberman_texture = load_texture(renderer, BOMBERMAN_TEXTURE_PATH);
	if (g_bomberman_texture == NULL) {
		fprintf(stderr, "Failed to load texture image %s", BOMBERMAN_TEXTURE_PATH);
        return (-1);
	}
    return (0);
}

void render_bomberman(SDL_Renderer *renderer, int x, int y)
{
    SDL_Rect body = {x,
                     y,
                     BOMBERMAN_BODY_WIDTH,
                     BOMBERMAN_BODY_HEIGHT};
    SDL_RenderCopy(renderer, g_bomberman_texture, NULL, &body);
}
