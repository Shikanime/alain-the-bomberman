#include "./render.h"
#include "../texture.h"

// Configuration
const char  *BOMB_TEXTURE_PATH  = "assets/bomb.png";
const int   BOMB_BODY_WIDTH     = 40;
const int   BOMB_BODY_HEIGHT    = 40;

// Texture singleton
SDL_Texture *g_bomb_texture = NULL;

int init_bomb(SDL_Renderer *renderer)
{
	g_bomb_texture = load_texture(renderer, BOMB_TEXTURE_PATH);
	if (g_bomb_texture == NULL) {
		fprintf(stderr, "Failed to load texture image %s", BOMB_TEXTURE_PATH);
        return (-1);
	}
    return (0);
}

void render_bomb(SDL_Renderer *renderer, int x, int y)
{
    SDL_Rect body = {x,
                     y,
                     BOMB_BODY_WIDTH,
                     BOMB_BODY_HEIGHT};
    SDL_RenderCopy(renderer, g_bomb_texture, NULL, &body);
}
