#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "../ressource.h"

int load_button(t_ressource *ressource);
void render_button(SDL_Renderer *renderer, TTF_Font *font, const char *text, size_t width, size_t height, int x, int y, bool light);
